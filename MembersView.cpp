/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		MEMBERSVIEW.CPP
** COMPONENT:	The Application.
** DESCRIPTION:	CMembersView class definition.
**
*******************************************************************************
*/

#include "AppHeaders.hpp"
#include "MemberDlg.hpp"

// The list view columns.
GridColumn CMembersView::Columns[NUM_COLUMNS] =
{
	{ "Name",       150, LVCFMT_LEFT, 0                         },
	{ "Phone #1",   150, LVCFMT_LEFT, CMembers::STANDARD_PHONE  },
	{ "Phone #2",   150, LVCFMT_LEFT, CMembers::ALTERNATE_PHONE },
	{ "Registered",  75, LVCFMT_LEFT, CMembers::IS_REGISTERED   },
	{ "Senior",      75, LVCFMT_LEFT, CMembers::IS_SENIOR       }
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
	: CGridViewDlg(IDD_GRID_VIEW, rDoc.m_oDB[CFCMDB::MEMBERS], NUM_COLUMNS, Columns)
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

void CMembersView::OnAdd()
{
	// Allocate a row for the member.
	CRow& oRow = m_oTable.CreateRow();

	CMemberDlg Dlg(oRow, false);

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
	// Get the current selection.
	int   iLVItem = m_lvGrid.SelectionMark();
	CRow& oRow    = Row(iLVItem);

	CMemberDlg Dlg(oRow, true);

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
	// Get the current selection.
	int   iLVItem = m_lvGrid.SelectionMark();
	CRow& oRow    = Row(iLVItem);

	ASSERT(&oRow != NULL);

	CString strName = App.FormatName(oRow, CMembers::FORENAME, CMembers::SURNAME);

	// Get user to confirm action.
	if (QueryMsg("Delete the member: %s?",  strName) != IDYES)
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

void CMembersView::OnPrint()
{
	PrintView("Members");
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

CString CMembersView::GetCellData(int nColumn, CRow& oRow, int nField)
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

		return (bFlag == true) ? "Yes" : "No";
	}

	return CGridViewDlg::GetCellData(nColumn, oRow, nField);
}
