/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		MEMBERDLG.HPP
** COMPONENT:	The Application.
** DESCRIPTION:	The CMemberDlg class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef MEMBERDLG_HPP
#define MEMBERDLG_HPP

#include "MemNamePage.hpp"
#include "MemStatusPage.hpp"
#include "PaymentsPage.hpp"
#include "StatsPage.hpp"
#include "NotesPage.hpp"

/******************************************************************************
** 
** This dialog is used to enter/edit a members details.
**
*******************************************************************************
*/

class CMemberDlg : public CPropertySheet
{
public:
	//
	// Constructors/Destructor.
	//
	CMemberDlg(CFCMDB& oDB, CRow& oRow, bool bEditing);
	
	//
	// Members.
	//
	CRow&	m_oRow;
	
protected:
	//
	// Members.
	//
	bool			m_bEditing;

	CMemNamePage	m_oNamePage;
	CMemStatusPage	m_oStatusPage;
	CPaymentsPage	m_oPaymentsPage;
	CStatsPage		m_oStatsPage;
	CNotesPage		m_oNotesPage;
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

#endif //MEMBERDLG_HPP
