/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		SUBSVIEW.CPP
** COMPONENT:	The Application.
** DESCRIPTION:	CSubsView class definition.
**
*******************************************************************************
*/

#include "AppHeaders.hpp"
#include "PrintViewDlg.hpp"

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

CSubsView::CSubsView(CFCMDoc& rDoc)
	: CViewDlg(IDD_GRID_VIEW)
	, m_oDB(rDoc.m_oDB)
{
	DEFINE_CTRL_TABLE
		CTRL(IDC_GRID, &m_lvGrid)
	END_CTRL_TABLE

	DEFINE_GRAVITY_TABLE
		CTRLGRAV(IDC_GRID, LEFT_EDGE, TOP_EDGE, RIGHT_EDGE, BOTTOM_EDGE)
	END_GRAVITY_TABLE
}

/******************************************************************************
** Method:		OnInitDialog()
**
** Description:	Initialise the dialog.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CSubsView::OnInitDialog()
{
	// Set the grid style.
	m_lvGrid.GridLines(true);
	m_lvGrid.FullRowSelect(true);
}

/******************************************************************************
** Method:		OnSelect()
**
** Description:	The view is being selected. Reload it if changed.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CSubsView::OnSelect()
{
	LoadGrid();
}

/******************************************************************************
** Method:		OnCommand()
**
** Description:	Executes the command.
**
** Parameters:	iCmdID		The command to execute.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CSubsView::OnCommand(uint iCmdID)
{
	switch (iCmdID)
	{
		case ID_OPTIONS_PRINT:	OnPrint();		break;
		default:				ASSERT(false);	break;
	}
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

void CSubsView::OnUIUpdate()
{
	bool bRows = (m_lvGrid.NumColumns() > 2);

	App.m_AppWnd.m_Menu.EnableCmd(ID_OPTIONS_ADD,    false);
	App.m_AppWnd.m_Menu.EnableCmd(ID_OPTIONS_EDIT,   false);
	App.m_AppWnd.m_Menu.EnableCmd(ID_OPTIONS_DELETE, false);
	App.m_AppWnd.m_Menu.EnableCmd(ID_OPTIONS_PRINT,  bRows);
	App.m_AppWnd.m_Menu.EnableCmd(ID_OPTIONS_IMPORT, false);
	App.m_AppWnd.m_Menu.EnableCmd(ID_OPTIONS_EXPORT, false);

	App.m_AppWnd.m_ToolBar.m_AddBtn.Enable(false);
	App.m_AppWnd.m_ToolBar.m_EditBtn.Enable(false);
	App.m_AppWnd.m_ToolBar.m_DeleteBtn.Enable(false);
	App.m_AppWnd.m_ToolBar.m_PrintBtn.Enable(bRows);
	App.m_AppWnd.m_ToolBar.m_ImportBtn.Enable(false);
	App.m_AppWnd.m_ToolBar.m_ExportBtn.Enable(false);
}

/******************************************************************************
** Method:		LoadGrid()
**
** Description:	Loads the entire grid, i.e. columns and rows.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CSubsView::LoadGrid()
{
	// Clear the existing rows and columns.
	m_lvGrid.DeleteAllItems();
	m_lvGrid.DeleteAllColumns();

	// Add the members column.
	m_lvGrid.InsertColumn(0, "Name", 150, LVCFMT_LEFT);

	// Add the balance sheet items.
	for (int r = 0, c = 1; r < m_oDB.m_oBalSheet.RowCount(); r++)
	{
		CRow& oRow = m_oDB.m_oBalSheet[r];

		// Income from members?
		if (oRow[CBalSheet::CREDIT_TYPE] == CBalSheet::VARIABLE)
		{
			CString strDate = App.FormatDate(oRow, CBalSheet::DATE);

			// Add column.
			m_lvGrid.InsertColumn(c++, strDate, 75, LVCFMT_RIGHT);
		}
	}

	// Add the balance column.
	m_lvGrid.InsertColumn(c, "£ Balance", 75, LVCFMT_RIGHT);

	// Add the members.
	for (int i = 0; i < m_oDB.m_oMembers.RowCount(); i++)
	{
		CRow& oMemberRow = m_oDB.m_oMembers[i];
		int   nBalance   = 0;

		// Create the grid row.
		int nGridRow = m_lvGrid.AppendItem(App.FormatName(oMemberRow, CMembers::FORENAME, CMembers::SURNAME, true), &oMemberRow);

		for (int j = 0, c = 1; j < m_oDB.m_oBalSheet.RowCount(); j++)
		{
			CRow& oBalShtRow = m_oDB.m_oBalSheet[j];

			// Income from members?
			if (oBalShtRow[CBalSheet::CREDIT_TYPE] == CBalSheet::VARIABLE)
			{
				// Look for a payment.
				CResultSet oRS = m_oDB.m_oSubs.Select(CWhereEqual(CSubs::MEMBER_ID, oMemberRow[CMembers::ID])
												& CWhereEqual(CSubs::ITEM_ID, oBalShtRow[CBalSheet::ID]));

				ASSERT(oRS.Count() <= 1);

				// Payment found?
				if (oRS.Count() == 1)
				{
					CRow& oPaymtRow = oRS[0];

					CString strFee  = App.FormatMoney(oPaymtRow, CSubs::FEE);
					CString strPaid = App.FormatMoney(oPaymtRow, CSubs::PAID);
					CString strItem;

					strItem.Format("%s  %s", strFee, strPaid);

					// Display fee & payment.
					m_lvGrid.ItemText(nGridRow, c, strItem);

					// Update balance.
					nBalance -= oPaymtRow[CSubs::FEE].GetInt();
					nBalance += oPaymtRow[CSubs::PAID].GetInt();
				}

				c++;
			}

		}

		// Set the balance.
		m_lvGrid.ItemText(nGridRow, c, App.FormatMoney(nBalance));
	}
}

/******************************************************************************
** Method:		OnPrint()
**
** Description:	Prints the view.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CSubsView::OnPrint()
{
	CPrintViewDlg Dlg("Subs");

	// Query for the printer and print parameters.
	if (Dlg.RunModal(*this) == IDOK)
	{


	}
}
