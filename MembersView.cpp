/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		MEMBERSVIEW.CPP
** COMPONENT:	The Application.
** DESCRIPTION:	CMembersView class definition.
**
*******************************************************************************
*/

#include "Common.hpp"
#include "MembersView.hpp"
#include "MemberDlg.hpp"
#include "StatTypesDlg.hpp"
#include "FCMApp.hpp"
#include <MDBL/ValueSet.hpp>

// The list view columns.
GridColumn CMembersView::Columns[NUM_COLUMNS] =
{
	{ TXT("Name"),       150, LVCFMT_LEFT,  0                         },
	{ TXT("Phone #1"),   150, LVCFMT_LEFT,  CMembers::STANDARD_PHONE  },
	{ TXT("Phone #2"),   150, LVCFMT_LEFT,  CMembers::ALTERNATE_PHONE },
	{ TXT("Registered?"), 75, LVCFMT_LEFT,  CMembers::IS_REGISTERED   },
	{ TXT("Senior?"),     75, LVCFMT_LEFT,  CMembers::IS_SENIOR       },
	{ TXT("Available?"),  75, LVCFMT_LEFT,  CMembers::IS_AVAILABLE    },
	{ TXT("� Balance"),   75, LVCFMT_RIGHT, CMembers::BALANCE         }
};

// Unavailability reasons.
static tchar* astrReasons[MAX_REASONS] =
{
	TXT("Unavailable"), TXT("Injured"), TXT("On Holiday"), TXT("Transferred"), TXT("Resigned"), TXT("Uncontactable")
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

CMembersView::CMembersView(CFCMDoc& rDoc)
	: CGridViewDlg(IDD_GRID_VIEW, rDoc.m_oDB, rDoc.m_oDB.m_oMembers, NUM_COLUMNS, Columns)
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

void CMembersView::OnUIUpdate()
{
	bool bRows = (m_oTable.RowCount() != 0);

	App.m_AppWnd.m_Menu.EnableCmd(ID_OPTIONS_ADD,       true);
	App.m_AppWnd.m_Menu.EnableCmd(ID_OPTIONS_EDIT,      bRows);
	App.m_AppWnd.m_Menu.EnableCmd(ID_OPTIONS_DELETE,    bRows);
	App.m_AppWnd.m_Menu.EnableCmd(ID_OPTIONS_DELETEALL, bRows);
	App.m_AppWnd.m_Menu.EnableCmd(ID_OPTIONS_PRINT,     bRows);
	App.m_AppWnd.m_Menu.EnableCmd(ID_OPTIONS_IMPORT,    !bRows);
	App.m_AppWnd.m_Menu.EnableCmd(ID_OPTIONS_EXPORT,    bRows);

	App.m_AppWnd.m_ToolBar.m_AddBtn.Enable(true);
	App.m_AppWnd.m_ToolBar.m_EditBtn.Enable(bRows);
	App.m_AppWnd.m_ToolBar.m_DeleteBtn.Enable(bRows);
	App.m_AppWnd.m_ToolBar.m_PrintBtn.Enable(bRows);
	App.m_AppWnd.m_ToolBar.m_ImportBtn.Enable(!bRows);
	App.m_AppWnd.m_ToolBar.m_ExportBtn.Enable(bRows);
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

void CMembersView::OnAdd()
{
	// Allocate a row for the member.
	CRow& oRow = m_oTable.CreateRow();

	CMemberDlg Dlg(m_oDB, oRow, false);

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

void CMembersView::OnEdit()
{
	// Ignore if no selection.
	if (!m_lvGrid.IsSelection())
		return;

	// Get the current selection.
	int   iLVItem = m_lvGrid.Selection();
	CRow& oRow    = Row(iLVItem);

	CMemberDlg Dlg(m_oDB, oRow, true);

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
** Description:	Allows the user to delete the currently selected member.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CMembersView::OnDelete()
{
	static const tchar* pszMsg = TXT("Delete the member: %s?\n\n")
								 TXT("This will also delete their stats, any\n")
								 TXT("income and their place in any team sheets.");

	// Ignore if no selection.
	if (!m_lvGrid.IsSelection())
		return;

	// Get the current selection.
	int   iLVItem = m_lvGrid.Selection();
	CRow& oRow    = Row(iLVItem);
	int   nID     = oRow[CMembers::ID];

	CString strName = App.FormatName(oRow, CMembers::FORENAME, CMembers::SURNAME);

	// Get user to confirm action.
	if (QueryMsg(pszMsg,  strName) != IDYES)
		return;

	// Remove any stats, income and team sheet places.
	m_oDB.m_oMemStats.DeleteMembersStats(nID);
//	m_oDB.m_oSubs;
//	m_oDB.m_oTeamSels;

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

void CMembersView::OnDeleteAll()
{
//	static const tchar* pszMsg = TXT("Delete the member: %s?\n\n")
//								 TXT("This will also delete their stats, any\n")
//								 TXT("income and their place in any team sheets.");

	// Get user to confirm action.
	if (QueryMsg(TXT("Delete ALL members?")) != IDYES)
		return;

	// Remove any stats, income and team sheet places.
//	m_oDB.m_oMemStats.DeleteMembersStats(nID);
//	m_oDB.m_oSubs;
//	m_oDB.m_oTeamSels;

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

void CMembersView::OnPrint()
{
	enum { NUM_PRT_COLUMNS = 7 };

	GridColumn aColumns[NUM_PRT_COLUMNS] =
	{
		{ TXT("Name"),        30, LVCFMT_LEFT, 0,                         true  },
		{ TXT("Phone #1"),    20, LVCFMT_LEFT, CMembers::STANDARD_PHONE,  true  },
		{ TXT("Phone #2"),    20, LVCFMT_LEFT, CMembers::ALTERNATE_PHONE, true  },
//		{ TXT("Address"),     20, LVCFMT_LEFT, CMembers::POSTAL_ADDRESS,  false },
//		{ TXT("Email"),       20, LVCFMT_LEFT, CMembers::EMAIL_ADDRESS,   false },
		{ TXT("Registered?"), 10, LVCFMT_LEFT, CMembers::IS_REGISTERED,   true  },
		{ TXT("Senior?"),     10, LVCFMT_LEFT, CMembers::IS_SENIOR,       true  },
		{ TXT("Available?"),  10, LVCFMT_LEFT, CMembers::IS_AVAILABLE,    true  },
	    { TXT("� Balance"),   10, LVCFMT_LEFT, CMembers::BALANCE,         true  }
	};

	PrintView(TXT("Members"), NUM_PRT_COLUMNS, aColumns);
}

/******************************************************************************
** Method:		OnImport()
**
** Description:	Import the members table from a file.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CMembersView::OnImport()
{
	ImportTable(CMembers::FILE_FORMAT, CMembers::FILE_VERSION);
}

/******************************************************************************
** Method:		OnExport()
**
** Description:	Export the members table to a file.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CMembersView::OnExport()
{
	ExportTable(CMembers::FILE_FORMAT, CMembers::FILE_VERSION);
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

void CMembersView::OnMiscCmd1()
{
	// Get the stat types and those currently in use.
	CMemStatTypes& oTypes = m_oDB.m_oMemStatTypes;
	CMemStats&     oStats = m_oDB.m_oMemStats;
	CValueSet      oUsed  = oStats.SelectAll().Distinct(CStats::TYPE_ID);

	CStatTypesDlg Dlg(TXT("Member"), oTypes, oUsed);

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

CString CMembersView::GetCellData(size_t nColumn, CRow& oRow, size_t nField)
{
	// Compose full name if name column.
	if (nColumn == NAME)
	{
		return App.FormatName(oRow, CMembers::FORENAME, CMembers::SURNAME, true);
	}
	// Change bool flags to strings.
	else if ( (nColumn == IS_REGISTERED) || (nColumn == IS_SENIOR) )
	{
		bool bFlag = oRow[nField];

		return (bFlag == true) ? TXT("Yes") : TXT("No");
	}
	// Set availability.
	else if (nColumn == IS_AVAILABLE)
	{
		bool bFlag = oRow[nField];

		return (bFlag == true) ? TXT("Yes") : astrReasons[oRow[CMembers::UNAVAIL_REASON].GetInt()];
	}
	// Balance.
	else if (nColumn == BALANCE)
	{
		return App.FormatMoney(oRow, CMembers::BALANCE);
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

int CMembersView::CompareRows(CRow& oRow1, CRow& oRow2)
{
	const tchar* pszValue1;
	const tchar* pszValue2;
	int			 nResult;

	// First compare surnames.
	pszValue1 = oRow1[CMembers::SURNAME];
	pszValue2 = oRow2[CMembers::SURNAME];
	nResult   = tstricmp(pszValue1, pszValue2);

	// Not equal?
	if (nResult != 0)
		return nResult;

	// If equal, compare forenames.
	pszValue1 = oRow1[CMembers::FORENAME];
	pszValue2 = oRow2[CMembers::FORENAME];
	nResult   = tstricmp(pszValue1, pszValue2);

	return nResult;
}

/******************************************************************************
** Method:		RefreshRows()
**
** Description:	Refreshes the grid rows for the data rows supplied.
**
** Parameters:	aoRows		The data rows to refresh.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CMembersView::RefreshRows(const CMembers::RowList& aoRows)
{
	// For all data rows, update grid row.
	for (size_t i = 0; i != aoRows.size(); i++)
		UpdateRow(FindRow(*aoRows[i]), false);
}
