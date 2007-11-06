/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		ACCOUNTSVIEW.CPP
** COMPONENT:	The Application.
** DESCRIPTION:	CAccountsView class definition.
**
*******************************************************************************
*/

#include "Common.hpp"
#include "AccountsView.hpp"
#include "AccountDlg.hpp"
#include "FCMApp.hpp"

// The list view columns.
GridColumn CAccountsView::Columns[NUM_COLUMNS] =
{
	{ "Name",      150, LVCFMT_LEFT, CAccounts::NAME    },
	{ "£ Balance",  75, LVCFMT_LEFT, CAccounts::BALANCE }
};

/******************************************************************************
** Method:		Constructor.
**
** Description:	.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

CAccountsView::CAccountsView(CFCMDoc& rDoc)
	: CGridViewDlg(IDD_GRID_VIEW, rDoc.m_oDB, rDoc.m_oDB.m_oAccounts, NUM_COLUMNS, Columns)
{
}

/******************************************************************************
** Method:		OnUIUpdate()
**
** Description:	Updates the UI for the options menu.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CAccountsView::OnUIUpdate()
{
	bool bRows = (m_oTable.RowCount() > 1);

	App.m_AppWnd.m_Menu.EnableCmd(ID_OPTIONS_ADD,       true);
	App.m_AppWnd.m_Menu.EnableCmd(ID_OPTIONS_EDIT,      bRows);
	App.m_AppWnd.m_Menu.EnableCmd(ID_OPTIONS_DELETE,    bRows);
	App.m_AppWnd.m_Menu.EnableCmd(ID_OPTIONS_DELETEALL, bRows);
	App.m_AppWnd.m_Menu.EnableCmd(ID_OPTIONS_PRINT,     bRows);

	App.m_AppWnd.m_ToolBar.m_AddBtn.Enable(true);
	App.m_AppWnd.m_ToolBar.m_EditBtn.Enable(bRows);
	App.m_AppWnd.m_ToolBar.m_DeleteBtn.Enable(bRows);
	App.m_AppWnd.m_ToolBar.m_PrintBtn.Enable(bRows);
	App.m_AppWnd.m_ToolBar.m_ImportBtn.Enable(false);
	App.m_AppWnd.m_ToolBar.m_ExportBtn.Enable(false);
}

/******************************************************************************
** Method:		OnAdd()
**
** Description:	Allows the user to add a new account.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CAccountsView::OnAdd()
{
	// Allocate a row for the item.
	CRow& oRow = m_oTable.CreateRow();

	CAccountDlg Dlg(m_oDB, oRow, false);

	if (Dlg.RunModal(*this) == IDOK)
	{
		// Add to the table.
		m_oTable.InsertRow(oRow);
		Dlg.UpdateTransTable();

		// Add to the list view and select it.
		int iLVItem = AddRow(oRow, true);
		m_lvGrid.Select(iLVItem);

		// Update totals.
		CAccounts& oTable = static_cast<CAccounts&>(m_oTable);

		oTable.UpdateTotalRow();
		UpdateRow(m_lvGrid.ItemCount()-1, false);

		App.m_AppCmds.UpdateUI();
	}
	else
	{
		delete &oRow;
	}
}

/******************************************************************************
** Method:		OnEdit()
**
** Description:	Allows the user to edit the currently selected account.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CAccountsView::OnEdit()
{
	// Ignore if no selection.
	if (!m_lvGrid.IsSelection())
		return;

	// Get the current selection.
	int   iLVItem = m_lvGrid.Selection();
	CRow& oRow    = Row(iLVItem);

	// Cannot edit the TOTAL row.
	if (oRow[CAccounts::ID].GetInt() == 1)
	{
		NotifyMsg("You cannot edit the 'TOTAL' item.");
		return;
	}

	CAccountDlg Dlg(m_oDB, oRow, true);

	if (Dlg.RunModal(*this) == IDOK)
	{
		Dlg.UpdateTransTable();

		// Update the list view.
		UpdateRow(iLVItem, true);

		// Update totals.
		CAccounts& oTable = static_cast<CAccounts&>(m_oTable);

		oTable.UpdateTotalRow();
		UpdateRow(m_lvGrid.ItemCount()-1, false);

		App.m_AppCmds.UpdateUI();
	}
}

/******************************************************************************
** Method:		OnDelete()
**
** Description:	Allows the user to delete the currently selected account.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CAccountsView::OnDelete()
{
	// Ignore if no selection.
	if (!m_lvGrid.IsSelection())
		return;

	// Get the current selection.
	int   iLVItem = m_lvGrid.Selection();
	CRow& oRow    = Row(iLVItem);

	ASSERT(&oRow != NULL);

	// Cannot delete the TOTAL row.
	if (oRow[CAccounts::ID].GetInt() == 1)
	{
		NotifyMsg("You cannot delete the 'TOTAL' item.");
		return;
	}

	CString strName = oRow[CAccounts::NAME];

	// Get user to confirm action.
	if (QueryMsg("Delete the account: %s?",  strName) != IDYES)
		return;

	// Remove from the list view and collection.
	DeleteRow(iLVItem);
	m_oTable.DeleteRow(oRow);

	// Update totals.
	CAccounts& oTable = static_cast<CAccounts&>(m_oTable);

	oTable.UpdateTotalRow();
	UpdateRow(m_lvGrid.ItemCount()-1, false);

	App.m_AppCmds.UpdateUI();
}

/******************************************************************************
** Method:		OnDeleteAll()
**
** Description:	Allows the user to delete all items, after confirmaing first.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CAccountsView::OnDeleteAll()
{
	ASSERT_FALSE();

	// Get user to confirm action.
	if (QueryMsg("Delete ALL items?") != IDYES)
		return;

	// Remove from the list view and collection.
	DeleteAllRows();
	m_oTable.Truncate();

	// Update totals.
	CBalSheet& oTable = static_cast<CBalSheet&>(m_oTable);

	oTable.UpdateTotalsRow();
	UpdateRow(m_lvGrid.ItemCount()-1, false);

	App.m_AppCmds.UpdateUI();
}

/******************************************************************************
** Method:		OnPrint()
**
** Description:	Print the list of accounts.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CAccountsView::OnPrint()
{
	enum { NUM_PRT_COLUMNS = 2 };

	GridColumn aColumns[NUM_PRT_COLUMNS] =
	{
		{ "Name",      150, LVCFMT_LEFT, CAccounts::NAME,    true },
		{ "£ Balance",  75, LVCFMT_LEFT, CAccounts::BALANCE, true }
	};

	PrintView("Accounts", NUM_PRT_COLUMNS, aColumns);
}

/******************************************************************************
** Method:		GetCellData()
**
** Description:	Gets the value for a cell.
**
** Parameters:	nColumn		The grid column.
**				oRow		The table row.
**				nField		The table row field.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

CString CAccountsView::GetCellData(int nColumn, CRow& oRow, int nField)
{
	// Compose full name if name column.
	if (nColumn == BALANCE)
	{
		return App.FormatMoney(oRow, nField);
	}

	return CGridViewDlg::GetCellData(nColumn, oRow, nField);
}

/******************************************************************************
** Method:		CompareRows()
**
** Description:	Compare the two rows.
**
** Parameters:	oRow1			Row 1.
**				oRow2			Row 2.
**
** Returns:		As stricmp.
**
*******************************************************************************
*/

int CAccountsView::CompareRows(CRow& oRow1, CRow& oRow2)
{
	const char* pszValue1 = oRow1[CAccounts::NAME];
	const char* pszValue2 = oRow2[CAccounts::NAME];

	return stricmp(pszValue1, pszValue2);
}
