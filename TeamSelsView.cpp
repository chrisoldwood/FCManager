/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		TEAMSELSVIEW.CPP
** COMPONENT:	The Application.
** DESCRIPTION:	CTeamSelsView class definition.
**
*******************************************************************************
*/

#include "AppHeaders.hpp"
#include "TeamSelDlg.hpp"

// The list view columns.
GridColumn CTeamSelsView::Columns[NUM_COLUMNS] =
{
	{ "Date",      100, LVCFMT_LEFT,  CTeamSels::DATE      },
	{ "Opponents", 150, LVCFMT_LEFT,  CTeamSels::OPPONENTS }
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

CTeamSelsView::CTeamSelsView(CFCMDoc& rDoc)
	: CGridViewDlg(IDD_GRID_VIEW, rDoc.m_oDB[CFCMDB::TEAMSELS], NUM_COLUMNS, Columns)
	, m_oMembers(rDoc.m_oDB[CFCMDB::MEMBERS])
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

void CTeamSelsView::OnUIUpdate()
{
	bool bRows = (m_oTable.RowCount() != 0);

	App.m_AppWnd.m_Menu.EnableCmd(ID_OPTIONS_ADD,    true);
	App.m_AppWnd.m_Menu.EnableCmd(ID_OPTIONS_EDIT,   bRows);
	App.m_AppWnd.m_Menu.EnableCmd(ID_OPTIONS_DELETE, bRows);
	App.m_AppWnd.m_Menu.EnableCmd(ID_OPTIONS_PRINT,  bRows);
	App.m_AppWnd.m_Menu.EnableCmd(ID_OPTIONS_IMPORT, false);
	App.m_AppWnd.m_Menu.EnableCmd(ID_OPTIONS_EXPORT, false);

	App.m_AppWnd.m_ToolBar.m_AddBtn.Enable(true);
	App.m_AppWnd.m_ToolBar.m_EditBtn.Enable(bRows);
	App.m_AppWnd.m_ToolBar.m_DeleteBtn.Enable(bRows);
	App.m_AppWnd.m_ToolBar.m_PrintBtn.Enable(bRows);
	App.m_AppWnd.m_ToolBar.m_ImportBtn.Enable(false);
	App.m_AppWnd.m_ToolBar.m_ExportBtn.Enable(false);
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

void CTeamSelsView::OnAdd()
{
	// Allocate a row for the member.
	CRow& oRow = m_oTable.CreateRow();

	CTeamSelDlg Dlg(oRow, m_oMembers, false);

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
** Description:	Allows the user to edit the currently selected item.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CTeamSelsView::OnEdit()
{
	// Get the current selection.
	int   iLVItem = m_lvGrid.SelectionMark();
	CRow& oRow    = Row(iLVItem);

	CTeamSelDlg Dlg(oRow, m_oMembers, true);

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
** Description:	Allows the user to delete the currently selected item, after
**				confirmaing first.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CTeamSelsView::OnDelete()
{
	// Get the current selection.
	int   iLVItem = m_lvGrid.SelectionMark();
	CRow& oRow    = Row(iLVItem);

	ASSERT(&oRow != NULL);

	CString strName = App.FormatDate(oRow, CTeamSels::DATE);

	// Get user to confirm action.
	if (QueryMsg("Delete the team selection for: %s?",  strName) != IDYES)
		return;

	// Remove from the list view and collection.
	DeleteRow(iLVItem);
	m_oTable.DeleteRow(oRow);

	App.m_AppCmds.UpdateUI();
}

/******************************************************************************
** Method:		OnPrint()
**
** Description:	Print the currently selected team selection.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CTeamSelsView::OnPrint()
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

CString CTeamSelsView::GetCellData(int nColumn, CRow& oRow, int nField)
{
	// Format dates.
	if (nColumn == DATE)
		return App.FormatDate(oRow, nField);

	return CGridViewDlg::GetCellData(nColumn, oRow, nField);
}
