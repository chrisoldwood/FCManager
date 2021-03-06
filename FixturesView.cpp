/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		FIXTURESVIEW.CPP
** COMPONENT:	The Application.
** DESCRIPTION:	CFixturesView class definition.
**
*******************************************************************************
*/

#include "Common.hpp"
#include "FixturesView.hpp"
#include "FixtureDlg.hpp"
#include "StatTypesDlg.hpp"
#include "FCMApp.hpp"
#include <time.h>
#include <MDBL/ValueSet.hpp>
#include <tchar.h>

// The list view columns.
GridColumn CFixturesView::Columns[NUM_COLUMNS] =
{
	{ TXT("Date"),       75, LVCFMT_LEFT,   CFixtures::DATE      },
	{ TXT("Type"),       75, LVCFMT_LEFT,   CFixtures::TYPE      },
	{ TXT("Home Team"), 150, LVCFMT_LEFT,   CFixtures::HOME_TEAM },
	{ TXT("Result"),     75, LVCFMT_CENTER, CFixtures::RESULT    },
	{ TXT("Away Team"), 150, LVCFMT_LEFT,   CFixtures::AWAY_TEAM },
	{ TXT("Referee"),   125, LVCFMT_LEFT,   CFixtures::REFEREE   },
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
	int   iLVItem = m_lvGrid.Selection();
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
	int   iLVItem = m_lvGrid.Selection();
	CRow& oRow    = Row(iLVItem);

	ASSERT(&oRow != NULL);

	CString strRow;

	strRow  = oRow[CFixtures::DATE].GetString();

	// Get user to confirm action.
	if (QueryMsg(TXT("Delete the fixture: %s"),  strRow) != IDYES)
		return;

	// Remove from the list view and collection.
	DeleteRow(iLVItem);
	m_oTable.DeleteRow(oRow);

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

void CFixturesView::OnDeleteAll()
{
	// Get user to confirm action.
	if (QueryMsg(TXT("Delete ALL fixtures?")) != IDYES)
		return;

	// Remove from the list view and collection.
	DeleteAllRows();
	m_oTable.Truncate();

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
		{ TXT("Date"),       75, LVCFMT_LEFT,   CFixtures::DATE,      true },
		{ TXT("Type"),       75, LVCFMT_LEFT,   CFixtures::TYPE,      true },
		{ TXT("Home Team"), 150, LVCFMT_LEFT,   CFixtures::HOME_TEAM, true },
		{ TXT("Result"),     75, LVCFMT_CENTER, CFixtures::RESULT,    true },
		{ TXT("Away Team"), 150, LVCFMT_LEFT,   CFixtures::AWAY_TEAM, true },
		{ TXT("Referee"),   125, LVCFMT_LEFT,   CFixtures::REFEREE,   true },
	};

	PrintView(TXT("Fixtures"), NUM_PRT_COLUMNS, aColumns);
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
** Method:		OnMiscCmd1()
**
** Description:	Maintain the statistic types.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CFixturesView::OnMiscCmd1()
{
	// Get the stat types and those currently in use.
	CFixStatTypes& oTypes = m_oDB.m_oFixStatTypes;
	CFixStats&     oStats = m_oDB.m_oFixStats;
	CValueSet      oUsed  = oStats.SelectAll().Distinct(CStats::TYPE_ID);

	CStatTypesDlg Dlg(TXT("Fixture"), oTypes, oUsed);

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

CString CFixturesView::GetCellData(size_t nColumn, CRow& oRow, size_t nField)
{
	if (nColumn == DATE)
	{
		tchar  szDate[20] = { 0 };
		time_t tDate = oRow[CFixtures::DATE];

		_tcsftime(szDate, sizeof(szDate), TXT("%d/%m/%y"), localtime(&tDate));

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

	return static_cast<int>(tValue1 - tValue2);
}
