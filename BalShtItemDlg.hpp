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

/******************************************************************************
** 
** This dialog is used to enter/edit a balance sheet items details.
**
*******************************************************************************
*/

class CBalShtItemDlg : public CDialog
{
public:
	//
	// Constructors/Destructor.
	//
	CBalShtItemDlg(CMDB& m_oDB, CRow& oItem, bool bEditing);
	
	//
	// Members.
	//
	CRow&	m_oItem;
	
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

	CEditBox		m_ebName;
	CDateTimePicker	m_dtpDate;
	CComboBox		m_cbType;
	CRadioBtn		m_rbNoCredit;
	CRadioBtn		m_rbFxdCredit;
	CRadioBtn		m_rbVarCredit;
	CListBox		m_lbCredits;
	CDecimalBox		m_ebCredit;
	CRadioBtn		m_rbNoDebit;
	CRadioBtn		m_rbFxdDebit;
	CRadioBtn		m_rbVarDebit;
	CDecimalBox		m_ebDebit;
	CListBox		m_lbDebits;
	CNotesDlg		m_oNotesDlg;

	CMDB&			m_oDB;
	int				m_nItemID;
	CTable			m_oTmpSubs;
	CTable&			m_oMembers;

	//
	// Message processors.
	//
	virtual void OnInitDialog();
	virtual bool OnOk();
	
	void OnNotes();
	void OnNoCredit();
	void OnFxdCredit();
	void OnVarCredit();
	void OnNoDebit();
	void OnFxdDebit();
	void OnVarDebit();
	void OnAddCredit();
	void OnEditCredit();
	void OnDelCredit();
	void OnAddDebit();
	void OnEditDebit();
	void OnDelDebit();

	//
	// Internal methods.
	//
	void RefreshCredits();
	void RefreshDebits();
	void UpdateCreditBtns();
	void UpdateDebitBtns();
	void UpdateCreditsTotal();
	void UpdateDebitsTotal();
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

#endif //BALSHTITEMDLG_HPP
