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

/******************************************************************************
** 
** This dialog is used to enter/edit a balance sheet items details.
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
	CListBox		m_lbCredits;

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
