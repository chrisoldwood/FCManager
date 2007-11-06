/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		FCMMAINWND.HPP
** COMPONENT:	The Application.
** DESCRIPTION:	The CFCMMainWnd class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef FCMMAINWND_HPP
#define FCMMAINWND_HPP

#if _MSC_VER > 1000
#pragma once
#endif

#include <WCL/SDIFrame.hpp>
#include <WCL/FrameMenu.hpp>
#include "FCMToolBar.hpp"
#include <WCL/StatusBar.hpp>
#include <WCL/Accel.hpp>

/******************************************************************************
**
** This is the the applications main window.
**
*******************************************************************************
*/

class CFCMMainWnd : public CSDIFrame
{
public:
	//
	// Constructors/Destructor.
	//
	CFCMMainWnd();
	~CFCMMainWnd();

	//
	// Members.
	//
	CFrameMenu	m_Menu;
	CFCMToolBar	m_ToolBar;
	CStatusBar	m_StatusBar;

protected:
	//
	// Internal members.
	//
	CAccel		m_Accel;

	// Child window IDs.
	enum
	{
		IDC_TOOL_BAR   = IDC_VIEW + 1,
		IDC_STATUS_BAR = IDC_VIEW + 2
	};

	//
	// Message processors.
	//
	virtual void OnCreate(const CRect& rcClient);
	virtual bool OnQueryClose();
	virtual void OnActivate(bool bActivating);
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

#endif //FCMMAINWND_HPP
