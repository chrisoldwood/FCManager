/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		REFEREEDLG.HPP
** COMPONENT:	The Application.
** DESCRIPTION:	The CRefereeDlg class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef REFEREEDLG_HPP
#define REFEREEDLG_HPP

#include "RefNamePage.hpp"
#include "StatsPage.hpp"
#include "NotesPage.hpp"

/******************************************************************************
** 
** This dialog is used to enter/edit a referees details.
**
*******************************************************************************
*/

class CRefereeDlg : public CPropertySheet
{
public:
	//
	// Constructors/Destructor.
	//
	CRefereeDlg(CFCMDB& oDB, CRow& oRow, bool bEditing);
	
	//
	// Members.
	//
	CRow&	m_oRow;
	
protected:
	//
	// Members.
	//
	bool		m_bEditing;

	CRefNamePage	m_oNamePage;
	CStatsPage		m_oStatsPage;
	CNotesPage		m_oNotesPage;
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

#endif //REFEREEDLG_HPP
