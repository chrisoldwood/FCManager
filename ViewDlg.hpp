/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		VIEWDLG.HPP
** COMPONENT:	The Application.
** DESCRIPTION:	The CViewDlg class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef VIEWDLG_HPP
#define VIEWDLG_HPP

#if _MSC_VER > 1000
#pragma once
#endif

#include <WCL/Dialog.hpp>

/******************************************************************************
** 
** This is the base class for all data view dialogs.
**
*******************************************************************************
*/

class CViewDlg : public CDialog
{
public:
	//
	// Constructors/Destructor.
	//
	CViewDlg(uint iRscID);
	
	//
	// Methods.
	//
	virtual void OnSelect();
	virtual void OnDeselect();

	virtual void OnCommand(uint iCmdID);
	virtual void OnUIUpdate();

protected:
	//
	// Members.
	//
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

#endif //VIEWDLG_HPP
