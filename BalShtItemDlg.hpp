/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		BALSHTITEMDLG.HPP
** COMPONENT:	The Application.
** DESCRIPTION:	The CBalShtItemDlg class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef BALSHTITEMDLG_HPP
#define BALSHTITEMDLG_HPP

#include "BalShtItemPage.hpp"
#include "IncomePage.hpp"
#include "ExpensesPage.hpp"
#include "NotesPage.hpp"

/******************************************************************************
** 
** This dialog is used to enter/edit a balance sheet items details.
**
*******************************************************************************
*/

class CBalShtItemDlg : public CPropertySheet
{
public:
	//
	// Constructors/Destructor.
	//
	CBalShtItemDlg(CFCMDB& m_oDB, CRow& oRow, bool bEditing);
	
	//
	// Members.
	//
	CRow&	m_oRow;
	
	//
	// Ancillary table methods.
	//
	void UpdateSubsTable();
	void UpdateExpensesTable();

protected:
	//
	// Members.
	//
	bool			m_bEditing;

	CFCMDB&			m_oDB;
	int				m_nItemID;
	CTmpSubs		m_oTmpSubs;
	CMembers&		m_oMembers;

	CBalShtItemPage	m_oItemPage;
	CIncomePage		m_oIncomePage;
	CExpensesPage	m_oExpensesPage;
	CNotesPage		m_oNotesPage;
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

#endif //BALSHTITEMDLG_HPP
