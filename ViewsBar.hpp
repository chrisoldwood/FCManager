/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		VIEWSBAR.HPP
** COMPONENT:	The Application.
** DESCRIPTION:	The CViewsBar class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef VIEWSBAR_HPP
#define VIEWSBAR_HPP

#if _MSC_VER > 1000
#pragma once
#endif

#include <WCL/ListBox.hpp>
#include <WCL/TransparentBmp.hpp>

/******************************************************************************
** 
** This window is the left hand pane used to pick which view is shown in the
** right hand pane.
**
*******************************************************************************
*/

class CViewsBar : public CListBox
{
public:
	//
	// Constructors/Destructor.
	//
	CViewsBar();
	~CViewsBar();
	
protected:
	//
	// Members.
	//
	CTransparentBmp	m_bmpIcons;

	// Icon size.
	enum { ICON_SIZE = 32 };

	// Border sizes.
	enum { BORDER = 4 };

	//
	// Window creation template methods.
	//
	virtual void GetCreateParams(WNDCREATE& rParams);

	//
	// Message processors (Overriden from the base class).
	//
	virtual	LRESULT WndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam);
	virtual void OnCreate(const CRect& rcClient);
	virtual void OnDrawItem(uint iID, uint iAction, uint iState, CDC& rDC, uint iItem, const CRect& rcItem);
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

#endif //VIEWSBAR_HPP
