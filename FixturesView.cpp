/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		FIXTURESVIEW.CPP
** COMPONENT:	The Application.
** DESCRIPTION:	CFixturesView class definition.
**
*******************************************************************************
*/

#include "AppHeaders.hpp"
#include "FixtureDlg.hpp"

// The list view columns.
GridColumn CFixturesView::Columns[NUM_COLUMNS] =
{
	{ "Date",       75, LVCFMT_LEFT, CFixtures::DATE      },
	{ "Type",       75, LVCFMT_LEFT, CFixtures::TYPE      },
	{ "Home Team", 150, LVCFMT_LEFT, CFixtures::HOME_TEAM },
	{ "Result",     75, LVCFMT_LEFT, CFixtures::RESULT    },
	{ "Away Team", 150, LVCFMT_LEFT, CFixtures::AWAY_TEAM },
	{ "Referee",   125, LVCFMT_LEFT, CFixtures::REFEREE   },
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

CFixturesView::CFixturesView(CFCMDoc& rDoc)
	: CGridViewDlg(IDD_GRID_VIEW, rDoc.m_oDB[CFCMDB::FIXTURES], NUM_COLUMNS, Columns)
{
}

/******************************************************************************
** Method:		OnAdd()
**
** Description:	Allows the user to add a new fixture.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CFixturesView::OnAdd()
{
	// Allocate a row for the fixture.
	CRow& oRow = m_oTable.CreateRow();

	CFixtureDlg Dlg(oRow, false);

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
** Description:	Allows the user to edit the currently selected fixture.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CFixturesView::OnEdit()
{
	// Get the current selection.
	int   iLVItem = m_lvGrid.SelectionMark();
	CRow& oRow    = Row(iLVItem);

	CFixtureDlg Dlg(oRow, true);

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
** Description:	Allows the user to delete the currently selected fixture.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CFixturesView::OnDelete()
{
	// Get the current selection.
	int   iLVItem = m_lvGrid.SelectionMark();
	CRow& oRow    = Row(iLVItem);

	ASSERT(&oRow != NULL);

	CString strRow;

	strRow  = oRow[CFixtures::DATE].GetString();

	// Get user to confirm action.
	if (QueryMsg("Delete the fixture: %s",  strRow) != IDYES)
		return;

	// Remove from the list view and collection.
	DeleteRow(iLVItem);
	m_oTable.DeleteRow(oRow);

	App.m_AppCmds.UpdateUI();
}

/******************************************************************************
** Method:		OnPrint()
**
** Description:	Print the list of fixtures.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CFixturesView::OnPrint()
{
}

/******************************************************************************
** Method:		OnImport()
**
** Description:	Import the fixtures table from a file.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CFixturesView::OnImport()
{
	ImportTable(CFixtures::FILE_FORMAT, CFixtures::FILE_VERSION);
}

/******************************************************************************
** Method:		OnExport()
**
** Description:	Export the fixtures table to a file.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CFixturesView::OnExport()
{
	ExportTable(CFixtures::FILE_FORMAT, CFixtures::FILE_VERSION);
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

CString CFixturesView::GetCellData(int nColumn, CRow& oRow, int nField)
{
	if (nColumn == DATE)
	{
		char   szDate[20] = { 0 };
		time_t tDate = oRow[CFixtures::DATE];

		strftime(szDate, sizeof(szDate), "%d/%m/%y", localtime(&tDate));

		return szDate;
	}

	return CGridViewDlg::GetCellData(nColumn, oRow, nField);
}
