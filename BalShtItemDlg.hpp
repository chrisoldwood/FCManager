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

#if _MSC_VER > 1000
#pragma once
#endif

#include <WCL/PropertySheet.hpp>
#include "BalShtItemPage.hpp"
#include "IncomePage.hpp"
#include "ExpensesPage.hpp"
#include "NotesPage.hpp"
#include "TmpSubs.hpp"
#include "TmpExps.hpp"

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
	void UpdateExpsTable();

protected:
	//
	// Members.
	//
	bool			m_bEditing;

	CFCMDB&			m_oDB;
	int				m_nItemID;
	CBalShtTypes&	m_oItemTypes;
	CTmpSubs		m_oTmpSubs;
	CMembers&		m_oMembers;
	CTmpExps		m_oTmpExps;
	CExpenseTypes&	m_oExpTypes;

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
