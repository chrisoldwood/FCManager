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
		TBGAP()
		TBCTL(&m_AddBtn,	ID_OPTIONS_POPUP+1)
		TBCTL(&m_EditBtn,	ID_OPTIONS_POPUP+2)
		TBCTL(&m_DeleteBtn,	ID_OPTIONS_POPUP+3)
		TBCTL(&m_PrintBtn,	ID_OPTIONS_POPUP+5)
		TBCTL(&m_ImportBtn,	ID_OPTIONS_POPUP+6)
		TBCTL(&m_ExportBtn,	ID_OPTIONS_POPUP+7)
		TBGAP()
		TBCTL(&m_AboutBtn,	ID_HELP_ABOUT)
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
