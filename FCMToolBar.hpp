/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		FCMTOOLBAR.HPP
** COMPONENT:	The Application.
** DESCRIPTION:	The CFCMToolBar class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef FCMTOOLBAR_HPP
#define FCMTOOLBAR_HPP

/******************************************************************************
** 
** This is the applications toolbar.
**
*******************************************************************************
*/

class CFCMToolBar : public CToolBar
{
public:
	//
	// Constructors/Destructor.
	//
	CFCMToolBar();
	~CFCMToolBar();
	
	//
	// Members.
	//
	CCmdButton	m_NewBtn;
	CCmdButton	m_OpenBtn;
	CCmdButton	m_SaveBtn;
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

#endif //FCMTOOLBAR_HPP
