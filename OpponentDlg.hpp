/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		OPPONENTDLG.HPP
** COMPONENT:	The Application.
** DESCRIPTION:	The COpponentDlg class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef OPPONENTDLG_HPP
#define OPPONENTDLG_HPP

#include "OpponentPage.hpp"
#include "SecNamePage.hpp"
#include "StatsPage.hpp"
#include "NotesPage.hpp"

/******************************************************************************
** 
** This dialog is used to enter/edit an opponents details.
**
*******************************************************************************
*/

class COpponentDlg : public CPropertySheet
{
public:
	//
	// Constructors/Destructor.
	//
	COpponentDlg(CFCMDB& oDB, CRow& oRow, bool bEditing);
	
	//
	// Members.
	//
	CRow&	m_oRow;
	
protected:
	//
	// Members.
	//
	bool			m_bEditing;

	COpponentPage	m_oOpponentPage;
	CSecNamePage	m_oSecretaryPage;
	CStatsPage		m_oStatsPage;
	CNotesPage		m_oNotesPage;
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

#endif //OPPONENTDLG_HPP
