/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		BALSHEETVIEW.CPP
** COMPONENT:	The Application.
** DESCRIPTION:	CBalSheetView class definition.
**
*******************************************************************************
*/

#include "AppHeaders.hpp"
#include "BalShtItemDlg.hpp"
#include "ExpenseTypesDlg.hpp"

// The list view columns.
GridColumn CBalSheetView::Columns[NUM_COLUMNS] =
{
	{ "Item",     150, LVCFMT_LEFT,  CBalSheet::NAME         },
	{ "Date",     100, LVCFMT_LEFT,  CBalSheet::DATE         },
	{ "£ Credit",  75, LVCFMT_RIGHT, CBalSheet::CREDIT_TOTAL },
	{ "£ Debit",   75, LVCFMT_RIGHT, CBalSheet::DEBIT_TOTAL  },
	{ "£ Balance", 75, LVCFMT_RIGHT, CBalSheet::BALANCE      }
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

CBalSheetView::CBalSheetView(CFCMDoc& rDoc)
	: CGridViewDlg(IDD_GRID_VIEW, rDoc.m_oDB, rDoc.m_oDB.m_oBalSheet, NUM_COLUMNS, Columns)
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

void CBalSheetView::OnUIUpdate()
{
	bool bRows = (m_oTable.RowCount() > 1);

	App.m_AppWnd.m_Menu.EnableCmd(ID_OPTIONS_ADD,       true);
	App.m_AppWnd.m_Menu.EnableCmd(ID_OPTIONS_EDIT,      bRows);
	App.m_AppWnd.m_Menu.EnableCmd(ID_OPTIONS_DELETE,    bRows);
	App.m_AppWnd.m_Menu.EnableCmd(ID_OPTIONS_DELETEALL, bRows);
	App.m_AppWnd.m_Menu.EnableCmd(ID_OPTIONS_PRINT,     bRows);
	App.m_AppWnd.m_Menu.EnableCmd(ID_OPTIONS_IMPORT,    false);
	App.m_AppWnd.m_Menu.EnableCmd(ID_OPTIONS_EXPORT,    false);

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
** Description:	Allows the user to add a new item.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CBalSheetView::OnAdd()
{
	// Allocate a row for the item.
	CRow& oRow = m_oTable.CreateRow();

	CBalShtItemDlg Dlg(m_oDB, oRow, false);

	if (Dlg.RunModal(*this) == IDOK)
	{
		// Add to the table.
		m_oTable.InsertRow(oRow);
		Dlg.UpdateSubsTable();
		Dlg.UpdateExpsTable();

		// Add to the list view and select it.
		int iLVItem = AddRow(oRow, true);
		m_lvGrid.Select(iLVItem);

		// Update totals.
		CBalSheet& oTable = static_cast<CBalSheet&>(m_oTable);

		oTable.UpdateTotalsRow();
		UpdateRow(m_lvGrid.ItemCount()-1, false);

		TRefArray<CRow> aoModified;

		// Update members balances.
		m_oDB.m_oMembers.UpdateBalances(m_oDB.m_oSubs, aoModified);
		App.View()->m_ViewsMgr.m_oMembersView.RefreshRows(aoModified);

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
** Description:	Allows the user to edit the currently selected item.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CBalSheetView::OnEdit()
{
	// Ignore if no selection.
	if (!m_lvGrid.IsSelection())
		return;

	// Get the current selection.
	int   iLVItem = m_lvGrid.Selection();
	CRow& oRow    = Row(iLVItem);

	// Cannot edit the TOTAL row.
	if (oRow[CBalSheet::ID].GetInt() == 1)
	{
		NotifyMsg("You cannot edit the 'TOTAL' item.");
		return;
	}

	CBalShtItemDlg Dlg(m_oDB, oRow, true);

	if (Dlg.RunModal(*this) == IDOK)
	{
		Dlg.UpdateSubsTable();
		Dlg.UpdateExpsTable();

		// Update the list view.
		UpdateRow(iLVItem, true);

		// Update totals.
		CBalSheet& oTable = static_cast<CBalSheet&>(m_oTable);

		oTable.UpdateTotalsRow();
		UpdateRow(m_lvGrid.ItemCount()-1, false);

		TRefArray<CRow> aoModified;

		// Update members balances.
		m_oDB.m_oMembers.UpdateBalances(m_oDB.m_oSubs, aoModified);
		App.View()->m_ViewsMgr.m_oMembersView.RefreshRows(aoModified);

		App.m_AppCmds.UpdateUI();
	}
}

/******************************************************************************
** Method:		OnDelete()
**
** Description:	Allows the user to delete the currently selected item, after
**				confirmaing first.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CBalSheetView::OnDelete()
{
	// Ignore if no selection.
	if (!m_lvGrid.IsSelection())
		return;

	// Get the current selection.
	int   iLVItem = m_lvGrid.Selection();
	CRow& oRow    = Row(iLVItem);

	ASSERT(&oRow != NULL);

	// Cannot delete the TOTAL row.
	if (oRow[CBalSheet::ID].GetInt() == 1)
	{
		NotifyMsg("You cannot delete the 'TOTAL' item.");
		return;
	}

	CString strName = oRow[CBalSheet::NAME];

	// Get user to confirm action.
	if (QueryMsg("Delete the item: %s?",  strName) != IDYES)
		return;

	// Remove from the list view and collection.
	DeleteRow(iLVItem);
	m_oTable.DeleteRow(oRow);

	// Update totals.
	CBalSheet& oTable = static_cast<CBalSheet&>(m_oTable);

	oTable.UpdateTotalsRow();
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

void CBalSheetView::OnDeleteAll()
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
** Description:	Print the list of members.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CBalSheetView::OnPrint()
{
	enum { NUM_PRT_COLUMNS = 5 };

	GridColumn aColumns[NUM_PRT_COLUMNS] =
	{
		{ "Item",     150, LVCFMT_LEFT,  CBalSheet::NAME,         true },
		{ "Date",     100, LVCFMT_LEFT,  CBalSheet::DATE,         true },
		{ "£ Credit",  75, LVCFMT_RIGHT, CBalSheet::CREDIT_TOTAL, true },
		{ "£ Debit",   75, LVCFMT_RIGHT, CBalSheet::DEBIT_TOTAL,  true },
		{ "£ Balance", 75, LVCFMT_RIGHT, CBalSheet::BALANCE,      true }
	};

	PrintView("Balance Sheet", NUM_PRT_COLUMNS, aColumns);
}

/******************************************************************************
** Method:		OnMiscCmd1()
**
** Description:	Maintain the expense types.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CBalSheetView::OnMiscCmd1()
{
	// Get the stat types and those currently in use.
	CExpenseTypes& oTypes = m_oDB.m_oExpenseTypes;
	CExpenses&     oExps  = m_oDB.m_oExpenses;
	CValueSet      oUsed  = oExps.SelectAll().Distinct(CExpenses::TYPE_ID);

	CExpenseTypesDlg Dlg(oTypes, oUsed);

	Dlg.RunModal(*this);
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

CString CBalSheetView::GetCellData(int nColumn, CRow& oRow, int nField)
{
	// Format money values.
	if (nColumn == BALANCE)
	{
		return App.FormatMoney(oRow, nField);
	}
	else if (nColumn == CREDIT)
	{
		// Ignore if not applicable.
		if (oRow[CBalSheet::CREDIT_TYPE] == CBalSheet::NONE)
			return "";

		return App.FormatMoney(oRow, nField);
	}
	else if (nColumn == DEBIT)
	{
		// Ignore if not applicable.
		if (oRow[CBalSheet::DEBIT_TYPE] == CBalSheet::NONE)
			return "";

		return App.FormatMoney(oRow, nField);
	}
	// Format dates.
	else if (nColumn == DATE)
	{
		// Don't show date for "TOTAL" row.
		if (oRow[CBalSheet::ID].GetInt() == 1)
			return "";

		return App.FormatDate(oRow, nField);
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
** Returns:		As strcmp.
**
*******************************************************************************
*/

int CBalSheetView::CompareRows(CRow& oRow1, CRow& oRow2)
{
	time_t tValue1 = oRow1[CBalSheet::DATE];
	time_t tValue2 = oRow2[CBalSheet::DATE];

	return (tValue1 - tValue2);
}
