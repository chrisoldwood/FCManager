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
	, m_rDoc(rDoc)
{
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
}
