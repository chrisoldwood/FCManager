/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		TEAMSELSVIEW.HPP
** COMPONENT:	The Application.
** DESCRIPTION:	The CTeamSelsView class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef TEAMSELSVIEW_HPP
#define TEAMSELSVIEW_HPP

/******************************************************************************
** 
** This is the data view used to display and edit team selections.
**
*******************************************************************************
*/

class CTeamSelsView : public CViewDlg
{
public:
	//
	// Constructors/Destructor.
	//
	CTeamSelsView(CFCMDoc& rDoc);
	
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

#endif //TEAMSELSVIEW_HPP
