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

#if _MSC_VER > 1000
#pragma once
#endif

#include <WCL/ToolBar.hpp>
#include <WCL/CmdBtn.hpp>

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
	CFCMToolBar(WCL::IMsgThread& thread, WCL::ICmdController& controller);
	~CFCMToolBar();
	
	//
	// Members.
	//
	CCmdButton	m_NewBtn;
	CCmdButton	m_OpenBtn;
	CCmdButton	m_SaveBtn;
	CCmdButton	m_AddBtn;
	CCmdButton	m_EditBtn;
	CCmdButton	m_DeleteBtn;
	CCmdButton	m_PrintBtn;
	CCmdButton	m_ImportBtn;
	CCmdButton	m_ExportBtn;
	CCmdButton	m_AboutBtn;
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

#endif //FCMTOOLBAR_HPP
