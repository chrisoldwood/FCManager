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
	
	//
	// Methods (Overriden).
	//
	virtual void OnSelect();
	virtual void OnCommand(uint iCmdID);
	virtual void OnUIUpdate();

	//
	// Commands.
	//
	virtual void OnPrint();

protected:
	//
	// Members.
	//
	CFCMDoc&	m_rDoc;
	CMDB&		m_oDB;
	CTable&		m_oMembers;
	CTable&		m_oBalSheet;
	CTable&		m_oSubs;
	CListView	m_lvGrid;
	
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
	void LoadGrid();
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

#endif //SUBSVIEW_HPP
