/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		FCMVIEW.CPP
** COMPONENT:	The Application.
** DESCRIPTION:	CFCMView class definition.
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

CFCMView::CFCMView(CFCMDoc& rDoc)
	: CView(rDoc)
	, m_ViewsMgr(rDoc)
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

CFCMView::~CFCMView()
{
}

/******************************************************************************
** Method:		OnCreate()
**
** Description:	Create the split view which manages the data views.
**
** Parameters:	rcClient	The client rectangle.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CFCMView::OnCreate(const CRect& /*rcClient*/)
{
	// Create the split window that fills the view.
	m_ViewsMgr.Create(*this, IDC_VIEWS_MGR, ClientRect());
}

/******************************************************************************
** Method:		OnResize()
**
** Description:	Resize the data views manager to fill the window.
**
** Parameters:	iFlag		The resize method.
**				rNewSize	The new window dimensions.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CFCMView::OnResize(int /*iFlag*/, const CSize& /*rNewSize*/)
{
	m_ViewsMgr.Move(ClientRect());
}
