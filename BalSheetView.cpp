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
#include <stdio.h>

// The list view columns.
GridColumn CBalSheetView::Columns[NUM_COLUMNS] =
{
	{ "Item",     150, LVCFMT_LEFT,  CBalSheet::NAME   },
	{ "Date",     100, LVCFMT_LEFT,  CBalSheet::DATE   },
	{ "£ Credit",  75, LVCFMT_RIGHT, CBalSheet::CREDIT },
	{ "£ Debit",   75, LVCFMT_RIGHT, CBalSheet::DEBIT  },
	{ "£ Balance", 75, LVCFMT_RIGHT, CBalSheet::TOTAL  }
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
{
}

/******************************************************************************
** Method:		OnAdd()
**
** Description:	Allows the user to add a new member.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CBalSheetView::OnAdd()
{
	// Allocate a row for the referee.
	CRow& oRow = m_oTable.CreateRow();

	CBalShtItemDlg Dlg(oRow, false);

	if (Dlg.RunModal(*this) == IDOK)
	{
		// Add to the table.
		m_oTable.InsertRow(oRow);

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
** Description:	Allows the user to edit the currently selected member.
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

	// Cannot delete the TOTALS row.
	if (oRow[CBalSheet::ID].GetInt() == 1)
	{
		NotifyMsg("You cannot edit the 'TOTALS' item.");
		return;
	}

	CBalShtItemDlg Dlg(oRow, true);

	if (Dlg.RunModal(*this) == IDOK)
	{
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
** Description:	Allows the user to delete the currently selected member, after
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
	if ( (nColumn == CREDIT) || (nColumn == DEBIT) || (nColumn == BALANCE) )
	{
		double dValue = oRow[nField].GetInt() / 100.0;
		char   szValue[10];

		sprintf(szValue, "%.2f", dValue);

		return szValue;
	}
	// Format dates.
	else if (nColumn == DATE)
	{
		// Only show date if not "TOTALS" row.
		if (oRow[CBalSheet::ID].GetInt() != 1)
			return oRow[nField].GetDate().ToString();
		else
			return "";
	}

	return CGridViewDlg::GetCellData(nColumn, oRow, nField);
}
