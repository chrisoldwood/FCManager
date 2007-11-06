/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		INCOMEPAGE.HPP
** COMPONENT:	The Application.
** DESCRIPTION:	The CIncomePage class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef INCOMEPAGE_HPP
#define INCOMEPAGE_HPP

#if _MSC_VER > 1000
#pragma once
#endif

#include <WCL/CommonUI.hpp>

// Forward declarations.
class CTmpSubs;
class CMembers;

/******************************************************************************
** 
** This dialog is used to enter/edit balance sheet item income details.
**
*******************************************************************************
*/

class CIncomePage : public CPropertyPage
{
public:
	//
	// Constructors/Destructor.
	//
	CIncomePage(CRow& oRow, CTmpSubs& oTmpSubs, CMembers& oMembers);
	
protected:
	//
	// Members.
	//
	CRow&			m_oRow;
	CTmpSubs&		m_oTmpSubs;
	CMembers&		m_oMembers;

	int				m_nType;
	int				m_nTotal;

	CRadioBtn		m_rbNoCredit;
	CRadioBtn		m_rbFxdCredit;
	CRadioBtn		m_rbVarCredit;
	CDecimalBox		m_ebCredit;
	CListView		m_lvCredits;

	//
	// Message processors.
	//
	virtual void OnInitDialog();
	virtual bool OnValidate();
	virtual bool OnOk();
	
	void OnNoCredit();
	void OnFxdCredit();
	void OnVarCredit();
	void OnAddCredit();
	void OnEditCredit();
	void OnDelCredit();
	LRESULT OnDblClick(NMHDR&);

	//
	// Internal methods.
	//
	void RefreshCredits();
	void UpdateCreditBtns();
	void UpdateCreditsTotal();
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

#endif //INCOMEPAGE_HPP
