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
