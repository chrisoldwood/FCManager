/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		REFEREESVIEW.CPP
** COMPONENT:	The Application.
** DESCRIPTION:	CRefereesView class definition.
**
*******************************************************************************
*/

#include "Common.hpp"
#include "RefereesView.hpp"
#include "RefereeDlg.hpp"
#include "StatTypesDlg.hpp"
#include "FCMApp.hpp"
#include <MDBL/ValueSet.hpp>

// The list view columns.
GridColumn CRefereesView::Columns[NUM_COLUMNS] =
{
	{ TXT("Name"),       150, LVCFMT_LEFT, 0                          },
	{ TXT("Phone #1"),   150, LVCFMT_LEFT, CReferees::STANDARD_PHONE  },
	{ TXT("Phone #2"),   150, LVCFMT_LEFT, CReferees::ALTERNATE_PHONE },
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

CRefereesView::CRefereesView(CFCMDoc& rDoc)
	: CGridViewDlg(IDD_GRID_VIEW, rDoc.m_oDB, rDoc.m_oDB.m_oReferees, NUM_COLUMNS, Columns)
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

void CRefereesView::OnAdd()
{
	// Allocate a row for the referee.
	CRow& oRow = m_oTable.CreateRow();

	CRefereeDlg Dlg(m_oDB, oRow, false);

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
** Description:	Allows the user to edit the currently selected member.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CRefereesView::OnEdit()
{
	// Ignore if no selection.
	if (!m_lvGrid.IsSelection())
		return;

	// Get the current selection.
	int   iLVItem = m_lvGrid.Selection();
	CRow& oRow    = Row(iLVItem);

	CRefereeDlg Dlg(m_oDB, oRow, true);

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
** Description:	Allows the user to delete the currently selected member, after
**				confirmaing first.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CRefereesView::OnDelete()
{
	// Ignore if no selection.
	if (!m_lvGrid.IsSelection())
		return;

	// Get the current selection.
	int   iLVItem = m_lvGrid.Selection();
	CRow& oRow    = Row(iLVItem);

	ASSERT(&oRow != NULL);

	CString strName = App.FormatName(oRow, CReferees::FORENAME, CReferees::SURNAME);

	// Get user to confirm action.
	if (QueryMsg(TXT("Delete the referee: %s?"), strName) != IDYES)
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

void CRefereesView::OnDeleteAll()
{
	// Get user to confirm action.
	if (QueryMsg(TXT("Delete ALL referees?")) != IDYES)
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

void CRefereesView::OnPrint()
{
	enum { NUM_PRT_COLUMNS = 3 };

	GridColumn aColumns[NUM_PRT_COLUMNS] =
	{
		{ TXT("Name"),       33, LVCFMT_LEFT, 0,                          true },
		{ TXT("Phone #1"),   33, LVCFMT_LEFT, CReferees::STANDARD_PHONE,  true },
		{ TXT("Phone #2"),   33, LVCFMT_LEFT, CReferees::ALTERNATE_PHONE, true },
	};

	PrintView(TXT("Referees"), NUM_PRT_COLUMNS, aColumns);
}

/******************************************************************************
** Method:		OnImport()
**
** Description:	Import the referees table from a file.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CRefereesView::OnImport()
{
	ImportTable(CReferees::FILE_FORMAT, CReferees::FILE_VERSION);
}

/******************************************************************************
** Method:		OnExport()
**
** Description:	Export the referees table to a file.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CRefereesView::OnExport()
{
	ExportTable(CReferees::FILE_FORMAT, CReferees::FILE_VERSION);
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

void CRefereesView::OnMiscCmd1()
{
	// Get the stat types and those currently in use.
	CRefStatTypes& oTypes = m_oDB.m_oRefStatTypes;
	CRefStats&     oStats = m_oDB.m_oRefStats;
	CValueSet      oUsed  = oStats.SelectAll().Distinct(CStats::TYPE_ID);

	CStatTypesDlg Dlg(TXT("Referee"), oTypes, oUsed);

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

CString CRefereesView::GetCellData(int nColumn, CRow& oRow, int nField)
{
	// Compose full name if name column.
	if (nColumn == NAME)
	{
		return App.FormatName(oRow, CReferees::FORENAME, CReferees::SURNAME, true);
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

int CRefereesView::CompareRows(CRow& oRow1, CRow& oRow2)
{
	const tchar* pszValue1;
	const tchar* pszValue2;
	int			 nResult;

	// First compare surnames.
	pszValue1 = oRow1[CReferees::SURNAME];
	pszValue2 = oRow2[CReferees::SURNAME];
	nResult   = tstricmp(pszValue1, pszValue2);

	// Not equal?
	if (nResult != 0)
		return nResult;

	// If equal, compare forenames.
	pszValue1 = oRow1[CReferees::FORENAME];
	pszValue2 = oRow2[CReferees::FORENAME];
	nResult   = tstricmp(pszValue1, pszValue2);

	return nResult;
}
