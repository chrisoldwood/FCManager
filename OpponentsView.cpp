/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		OPPONENTSVIEW.CPP
** COMPONENT:	The Application.
** DESCRIPTION:	COpponentsView class definition.
**
*******************************************************************************
*/

#include "AppHeaders.hpp"
#include "OpponentDlg.hpp"

// The list view columns.
GridColumn COpponentsView::Columns[NUM_COLUMNS] =
{
	{ "Name",      150, LVCFMT_LEFT, COpponents::CLUB_NAME       },
	{ "Ground",    100, LVCFMT_LEFT, COpponents::GROUND          },
	{ "Secretary", 150, LVCFMT_LEFT, 0                           },
	{ "Phone #1",  150, LVCFMT_LEFT, COpponents::STANDARD_PHONE  },
	{ "Phone #2",  150, LVCFMT_LEFT, COpponents::ALTERNATE_PHONE },
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

COpponentsView::COpponentsView(CFCMDoc& rDoc)
	: CGridViewDlg(IDD_GRID_VIEW, rDoc.m_oDB[CFCMDB::OPPONENTS], NUM_COLUMNS, Columns)
{
}

/******************************************************************************
** Method:		OnAdd()
**
** Description:	Allows the user to add a new opponent.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void COpponentsView::OnAdd()
{
	// Allocate a row for the member.
	CRow& oRow = m_oTable.CreateRow();

	COpponentDlg Dlg(oRow, false);

	if (Dlg.RunModal(*this) == IDOK)
	{
		// Add to the table.
		m_oTable.InsertRow(oRow);

		// Add to the list view and select it.
		int iLVItem = AddRow(oRow);
		m_lvGrid.Select(iLVItem);

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
** Description:	Allows the user to edit the currently selected opponent.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void COpponentsView::OnEdit()
{
	// Get the current selection.
	int   iLVItem = m_lvGrid.SelectionMark();
	CRow& oRow    = Row(iLVItem);

	COpponentDlg Dlg(oRow, true);

	if (Dlg.RunModal(*this) == IDOK)
	{
		// Update the list view.
		UpdateRow(iLVItem);

		App.m_AppCmds.UpdateUI();
	}
}

/******************************************************************************
** Method:		OnDelete()
**
** Description:	Allows the user to delete the currently selected opponent, after
**				confirmaing first.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void COpponentsView::OnDelete()
{
	// Get the current selection.
	int   iLVItem = m_lvGrid.SelectionMark();
	CRow& oRow    = Row(iLVItem);

	ASSERT(&oRow != NULL);

	CString strName = oRow[COpponents::CLUB_NAME].GetString();

	// Get user to confirm action.
	if (QueryMsg("Delete the opponent: %s?",  strName) != IDYES)
		return;

	// Remove from the list view and collection.
	DeleteRow(iLVItem);
	m_oTable.DeleteRow(oRow);

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

void COpponentsView::OnPrint()
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

CString COpponentsView::GetCellData(int nColumn, CRow& oRow, int nField)
{
	// Compose full name if name column.
	if (nColumn == SECRETARY)
	{
		return App.MakeFullName(oRow, COpponents::FORENAME, COpponents::SURNAME, true);
	}

	return CGridViewDlg::GetCellData(nColumn, oRow, nField);
}
