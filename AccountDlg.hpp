/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		ACCOUNTDLG.HPP
** COMPONENT:	The Application.
** DESCRIPTION:	The CAccountDlg class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef ACCOUNTDLG_HPP
#define ACCOUNTDLG_HPP

#include "BalShtItemPage.hpp"
#include "AccountPage.hpp"
#include "NotesPage.hpp"

/******************************************************************************
** 
** This dialog is used to enter/edit an accounts details.
**
*******************************************************************************
*/

class CAccountDlg : public CPropertySheet
{
public:
	//
	// Constructors/Destructor.
	//
	CAccountDlg(CFCMDB& m_oDB, CRow& oRow, bool bEditing);
	
	//
	// Members.
	//
	CRow&	m_oRow;
	
	//
	// Ancillary table methods.
	//
	void UpdateTransTable();

protected:
	//
	// Members.
	//
	bool			m_bEditing;

	CFCMDB&			m_oDB;
	int				m_nItemID;
//	CTmpSubs		m_oTmpSubs;
//	CMembers&		m_oMembers;
//	CTmpExps		m_oTmpExps;
//	CExpenseTypes&	m_oExpTypes;

	CAccountPage	m_oAccountPage;
	CNotesPage		m_oNotesPage;
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

#endif //ACCOUNTDLG_HPP
