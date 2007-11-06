/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		FCMVIEW.HPP
** COMPONENT:	The Application.
** DESCRIPTION:	The CFCMView class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef FCMVIEW_HPP
#define FCMVIEW_HPP

#if _MSC_VER > 1000
#pragma once
#endif

#include <WCL/View.hpp>
#include "ViewsMgr.hpp"

/******************************************************************************
** 
** This is the main view class.
**
*******************************************************************************
*/

class CFCMView : public CView
{
public:
	//
	// Constructors/Destructor.
	//
	CFCMView(CFCMDoc& rDoc);
	~CFCMView();
	
	//
	// Members.
	//
	CViewsMgr	m_ViewsMgr;

protected:
	// Child window ID.
	enum { IDC_VIEWS_MGR = 100 };
	
	//
	// Message processors (Overriden from the base class).
	//
	virtual void OnCreate(const CRect& rcClient);
	virtual void OnResize(int iFlag, const CSize& rNewSize);
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

#endif //FCMVIEW_HPP
