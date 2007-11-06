/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		OPPONENTSVIEW.CPP
** COMPONENT:	The Application.
** DESCRIPTION:	COpponentsView class definition.
**
*******************************************************************************
*/

#include "Common.hpp"
#include "OpponentsView.hpp"
#include "OpponentDlg.hpp"
#include "StatTypesDlg.hpp"
#include "FCMApp.hpp"
#include <MDBL/ValueSet.hpp>

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
	: CGridViewDlg(IDD_GRID_VIEW, rDoc.m_oDB, rDoc.m_oDB.m_oOpponents, NUM_COLUMNS, Columns)
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

	COpponentDlg Dlg(m_oDB, oRow, false);

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
	// Ignore if no selection.
	if (!m_lvGrid.IsSelection())
		return;

	// Get the current selection.
	int   iLVItem = m_lvGrid.Selection();
	CRow& oRow    = Row(iLVItem);

	COpponentDlg Dlg(m_oDB, oRow, true);

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
	// Ignore if no selection.
	if (!m_lvGrid.IsSelection())
		return;

	// Get the current selection.
	int   iLVItem = m_lvGrid.Selection();
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

void COpponentsView::OnDeleteAll()
{
	// Get user to confirm action.
	if (QueryMsg("Delete ALL opponents?") != IDYES)
		return;

	// Remove from the list view and collection.
	DeleteAllRows();
	m_oTable.Truncate();

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
	enum { NUM_PRT_COLUMNS = 5 };

	GridColumn aColumns[NUM_PRT_COLUMNS] =
	{
		{ "Name",      20, LVCFMT_LEFT, COpponents::CLUB_NAME,       true  },
		{ "Ground",    20, LVCFMT_LEFT, COpponents::GROUND,          true  },
		{ "Secretary", 20, LVCFMT_LEFT, 0,                           true  },
		{ "Phone #1",  20, LVCFMT_LEFT, COpponents::STANDARD_PHONE,  true  },
		{ "Phone #2",  20, LVCFMT_LEFT, COpponents::ALTERNATE_PHONE, false },
	};

	PrintView("Opponents", NUM_PRT_COLUMNS, aColumns);
}

/******************************************************************************
** Method:		OnImport()
**
** Description:	Import the opponents table from a file.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void COpponentsView::OnImport()
{
	ImportTable(COpponents::FILE_FORMAT, COpponents::FILE_VERSION);
}

/******************************************************************************
** Method:		OnExport()
**
** Description:	Export the opponents table to a file.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void COpponentsView::OnExport()
{
	ExportTable(COpponents::FILE_FORMAT, COpponents::FILE_VERSION);
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

void COpponentsView::OnMiscCmd1()
{
	// Get the stat types and those currently in use.
	COppStatTypes& oTypes = m_oDB.m_oOppStatTypes;
	COppStats&     oStats = m_oDB.m_oOppStats;
	CValueSet      oUsed  = oStats.SelectAll().Distinct(CStats::TYPE_ID);

	CStatTypesDlg Dlg("Opponent", oTypes, oUsed);

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

CString COpponentsView::GetCellData(int nColumn, CRow& oRow, int nField)
{
	// Compose full name if name column.
	if (nColumn == SECRETARY)
	{
		return App.FormatName(oRow, COpponents::FORENAME, COpponents::SURNAME, true);
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

int COpponentsView::CompareRows(CRow& oRow1, CRow& oRow2)
{
	const char* pszValue1;
	const char* pszValue2;
	int			nResult;

	pszValue1 = oRow1[COpponents::CLUB_NAME];
	pszValue2 = oRow2[COpponents::CLUB_NAME];
	nResult   = stricmp(pszValue1, pszValue2);

	return nResult;
}
