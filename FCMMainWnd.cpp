/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		FCMMAINWND.CPP
** COMPONENT:	The Application.
** DESCRIPTION:	CFCMMainWnd class definition.
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

CFCMMainWnd::CFCMMainWnd() : CSDIFrame(IDR_APPICON)
{
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

CFCMMainWnd::~CFCMMainWnd()
{
}

/******************************************************************************
** Method:		OnCreate()
**
** Description:	Creates the toolbar and status bars.
**
** Parameters:	rcClient	The client rectangle.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CFCMMainWnd::OnCreate(const CRect& rcClient)
{
	//
	// Create and attach the components.
	//
	m_Accel.LoadRsc(IDR_APPACCEL);
	Accel(&m_Accel);

	m_Menu.LoadRsc(IDR_APPMENU);
	Menu(&m_Menu);

	m_ToolBar.Create(*this, IDC_TOOL_BAR, rcClient);
	ToolBar(&m_ToolBar);

	m_StatusBar.Create(*this, IDC_STATUS_BAR, rcClient);
	StatusBar(&m_StatusBar);

	// Call base class.
	CSDIFrame::OnCreate(rcClient);
}

/******************************************************************************
** Method:		OnQueryClose()
**
** Description:	Check if the app can close.
**
** Parameters:	None.
**
** Returns:		true or false.
**
*******************************************************************************
*/

bool CFCMMainWnd::OnQueryClose()
{
	// Save windows final position.
	App.m_rcAppWnd = Placement();

	// Close the app if the file was closed.
	return App.m_AppCmds.CloseFile();
}

/******************************************************************************
** Method:		OnActivate()
**
** Description:	Main window (de)activated, pass focus onto view.
**
** Parameters:	bActivating		Activating or deactivating?
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CFCMMainWnd::OnActivate(bool bActivating)
{
	if (bActivating)
		App.m_AppCmds.SetFocus();
}
