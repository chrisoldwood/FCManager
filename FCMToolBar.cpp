/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		FCMTOOLBAR.CPP
** COMPONENT:	The Application.
** DESCRIPTION:	CFCMToolBar class definition.
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

CFCMToolBar::CFCMToolBar()
{
	// Define the toolbar.
	DEFINE_TOOLBAR
		TBCTL(&m_NewBtn,	ID_FILE_NEW)
		TBCTL(&m_OpenBtn,	ID_FILE_OPEN)
		TBCTL(&m_SaveBtn,	ID_FILE_SAVE)
//		TBGAP()
	END_TOOLBAR
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

CFCMToolBar::~CFCMToolBar()
{
}
