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
	: CGridViewDlg(IDD_GRID_VIEW, rDoc.m_oDB[CFCMDB::BALSHEET], NUM_COLUMNS, Columns)
	, m_oDB(rDoc.m_oDB)
{
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

		// Add to the list view and select it.
		int iLVItem = AddRow(oRow);
		m_lvGrid.Select(iLVItem);

		// Update totals.
		CBalSheet& oTable = static_cast<CBalSheet&>(m_oTable);

		oTable.UpdateTotalsRow();
		UpdateRow(m_lvGrid.ItemCount()-1);

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
	// Get the current selection.
	int   iLVItem = m_lvGrid.SelectionMark();
	CRow& oRow    = Row(iLVItem);

	// Cannot edit the TOTALS row.
	if (oRow[CBalSheet::ID].GetInt() == 1)
	{
		NotifyMsg("You cannot edit the 'TOTALS' item.");
		return;
	}

	CBalShtItemDlg Dlg(m_oDB, oRow, true);

	if (Dlg.RunModal(*this) == IDOK)
	{
		Dlg.UpdateSubsTable();

		// Update the list view.
		UpdateRow(iLVItem);

		// Update totals.
		CBalSheet& oTable = static_cast<CBalSheet&>(m_oTable);

		oTable.UpdateTotalsRow();
		UpdateRow(m_lvGrid.ItemCount()-1);

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
	// Get the current selection.
	int   iLVItem = m_lvGrid.SelectionMark();
	CRow& oRow    = Row(iLVItem);

	ASSERT(&oRow != NULL);

	// Cannot delete the TOTALS row.
	if (oRow[CBalSheet::ID].GetInt() == 1)
	{
		NotifyMsg("You cannot delete the 'TOTALS' item.");
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
	UpdateRow(m_lvGrid.ItemCount()-1);

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
		// Don't show date for "TOTALS" row.
		if (oRow[CBalSheet::ID].GetInt() == 1)
			return "";

		return App.FormatDate(oRow, nField);
	}

	return CGridViewDlg::GetCellData(nColumn, oRow, nField);
}
