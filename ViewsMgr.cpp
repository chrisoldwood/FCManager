/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		VIEWMGR.CPP
** COMPONENT:	The Application.
** DESCRIPTION:	CViewsMgr class definition.
**
*******************************************************************************
*/

#include "AppHeaders.hpp"

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

CViewsMgr::CViewsMgr(CFCMDoc& rDoc)
	: CSplitWnd(true, true)
	, m_eCurrView(NO_VIEW)
	, m_oMembersView(rDoc)
	, m_oFixturesView(rDoc)
	, m_oBalSheetView(rDoc)
	, m_oAccountsView(rDoc)
	, m_oTeamSelsView(rDoc)
	, m_oOpponentsView(rDoc)
	, m_oRefereesView(rDoc)
{
	// Initialise the array of data views.
	m_pDataViews[MEMBERS_VIEW]   = &m_oMembersView;
	m_pDataViews[FIXTURES_VIEW]  = &m_oFixturesView;
	m_pDataViews[ACCOUNTS_VIEW]  = &m_oAccountsView;
	m_pDataViews[BALANCE_VIEW]   = &m_oBalSheetView;
	m_pDataViews[TEAM_SELS_VIEW] = &m_oTeamSelsView;
	m_pDataViews[OPPONENTS_VIEW] = &m_oOpponentsView;
	m_pDataViews[REFEREES_VIEW]  = &m_oRefereesView;

	// Define the control message handlers.
	DEFINE_CTRLMSG_TABLE
		CMD_CTRLMSG(IDC_VIEW_BAR, 	LBN_SELCHANGE,	OnSelectView)
	END_CTRLMSG_TABLE
}

/******************************************************************************
** Method:		Destructor.
**
** Description:	.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

CViewsMgr::~CViewsMgr()
{
}

/******************************************************************************
** Method:		OnCreate()
**
** Description:	Create the the data view bar and the data view dialogs.
**
** Parameters:	rcClient	The client rectangle.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CViewsMgr::OnCreate(const CRect& rcClient)
{
	// Create the data view bar
	m_oViewsBar.Create(*this, IDC_VIEW_BAR, CRect(0, 0, 0, 0));
	Pane(LEFT_PANE, &m_oViewsBar);
	BarPos(100);

	// Create the data views.
	for (int i = 0; i < NUM_DATAVIEWS; i++)
		m_pDataViews[i]->RunModeless(*this);
}

/******************************************************************************
** Method:		SelectView()
**
** Description:	Select a view.
**
** Parameters:	eNewView	The view to show.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CViewsMgr::SelectView(DataView eNewView)
{
	// Ignore if not changing.
	if (eNewView == m_eCurrView)
		return;

	// Hide the old view, if one.
	if (m_eCurrView != NO_VIEW)
	{
		m_pDataViews[m_eCurrView]->OnDeselect();
		m_pDataViews[m_eCurrView]->Show(SW_HIDE);
	}

	m_eCurrView = eNewView;

	// Show the new view.
	Pane(RIGHT_PANE, m_pDataViews[m_eCurrView]);

	// Update the view bar selection, if different.
	if (m_oViewsBar.CurSel() != eNewView)
		m_oViewsBar.CurSel(eNewView);

	// Load the options menus.
	m_oOptionsMenus.LoadRsc(IDR_OPTIONS_MENUS);

	// Set the options menu in the frame window.
	App.m_AppWnd.m_Menu.SetItemPopup(3, m_oOptionsMenus.Popup(eNewView), m_oOptionsMenus.GetItemText(eNewView));
	App.m_AppWnd.DrawMenuBar();

	// Update the UI.
	m_pDataViews[m_eCurrView]->OnSelect();
	m_pDataViews[m_eCurrView]->OnUIUpdate();
	m_pDataViews[m_eCurrView]->Focus();
}

/******************************************************************************
** Method:		OnSelectView()
**
** Description:	The user has chosen another view.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CViewsMgr::OnSelectView()
{
	App.m_AppCmds.SelectView((DataView)m_oViewsBar.CurSel());
}

/******************************************************************************
** Method:		SetFocus()
**
** Description:	Sets the focus to the current view.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CViewsMgr::SetFocus()
{
	m_pDataViews[m_eCurrView]->Focus();
}
