/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		FIXTUREDLG.HPP
** COMPONENT:	The Application.
** DESCRIPTION:	The CFixtureDlg class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef FIXTUREDLG_HPP
#define FIXTUREDLG_HPP

#include "FixturePage.hpp"
#include "StatsPage.hpp"
#include "NotesPage.hpp"

/******************************************************************************
** 
** This dialog is used to enter/edit a fixtures details.
**
*******************************************************************************
*/

class CFixtureDlg : public CPropertySheet
{
public:
	//
	// Constructors/Destructor.
	//
	CFixtureDlg(CFCMDB& oDB, CRow& oRow, bool bEditing);
	
	//
	// Members.
	//
	CRow&	m_oRow;
	
protected:
	//
	// Members.
	//
	bool		m_bEditing;

	CFixturePage	m_oDetailsPage;
	CStatsPage		m_oStatsPage;
	CNotesPage		m_oNotesPage;
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

#endif //FIXTUREDLG_HPP
