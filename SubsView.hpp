/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		SUBSVIEW.HPP
** COMPONENT:	The Application.
** DESCRIPTION:	The CSubsView class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef SUBSVIEW_HPP
#define SUBSVIEW_HPP

/******************************************************************************
** 
** This is the data view used to display and edit the members subs.
**
*******************************************************************************
*/

class CSubsView : public CViewDlg
{
public:
	//
	// Constructors/Destructor.
	//
	CSubsView(CFCMDoc& rDoc);
	
protected:
	//
	// Members.
	//
	CFCMDoc&	m_rDoc;
	
	//
	// Message handlers.
	//
	virtual void OnInitDialog();

	//
	// Control message handlers.
	//

	//
	// Internal methods.
	//
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

#endif //SUBSVIEW_HPP
