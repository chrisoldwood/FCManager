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
	{ "Date",       75, LVCFMT_LEFT,   CFixtures::DATE      },
	{ "Type",       75, LVCFMT_LEFT,   CFixtures::TYPE      },
	{ "Home Team", 150, LVCFMT_LEFT,   CFixtures::HOME_TEAM },
	{ "Result",     75, LVCFMT_CENTER, CFixtures::RESULT    },
	{ "Away Team", 150, LVCFMT_LEFT,   CFixtures::AWAY_TEAM },
	{ "Referee",   125, LVCFMT_LEFT,   CFixtures::REFEREE   },
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
	: CGridViewDlg(IDD_GRID_VIEW, rDoc.m_oDB, rDoc.m_oDB.m_oFixtures, NUM_COLUMNS, Columns)
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

	CFixtureDlg Dlg(m_oDB, oRow, false);

	if (Dlg.RunModal(*this) == IDOK)
	{
		// Add to the table.
		m_oTable.InsertRow(oRow);

		// Add to the list view and select it.
		int iLVItem = AddRow(oRow, true);
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
	// Ignore if no selection.
	if (!m_lvGrid.IsSelection())
		return;

	// Get the current selection.
	int   iLVItem = m_lvGrid.Selected();
	CRow& oRow    = Row(iLVItem);

	CFixtureDlg Dlg(m_oDB, oRow, true);

	if (Dlg.RunModal(*this) == IDOK)
	{
		// Update the list view.
		UpdateRow(iLVItem, true);

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
	// Ignore if no selection.
	if (!m_lvGrid.IsSelection())
		return;

	// Get the current selection.
	int   iLVItem = m_lvGrid.Selected();
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
	enum { NUM_PRT_COLUMNS = 6 };

	GridColumn aColumns[NUM_PRT_COLUMNS] =
	{
		{ "Date",       75, LVCFMT_LEFT,   CFixtures::DATE,      true },
		{ "Type",       75, LVCFMT_LEFT,   CFixtures::TYPE,      true },
		{ "Home Team", 150, LVCFMT_LEFT,   CFixtures::HOME_TEAM, true },
		{ "Result",     75, LVCFMT_CENTER, CFixtures::RESULT,    true },
		{ "Away Team", 150, LVCFMT_LEFT,   CFixtures::AWAY_TEAM, true },
		{ "Referee",   125, LVCFMT_LEFT,   CFixtures::REFEREE,   true },
	};

	PrintView("Fixtures", NUM_PRT_COLUMNS, aColumns);
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

int CFixturesView::CompareRows(CRow& oRow1, CRow& oRow2)
{
	time_t tValue1 = oRow1[CFixtures::DATE];
	time_t tValue2 = oRow2[CFixtures::DATE];

	return (tValue1 - tValue2);
}
