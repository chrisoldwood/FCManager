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
	CBalShtItemDlg(CRow& oItem, bool bEditing);
	
	//
	// Members.
	//
	CRow&	m_oItem;
	
protected:
	//
	// Members.
	//
	bool			m_bEditing;

	CEditBox		m_ebName;
	CDateTimePicker	m_dtpDate;
	CRadioBtn		m_rbFxdCredit;
	CRadioBtn		m_rbVarCredit;
	CListBox		m_lbCredits;
	CDecimalBox		m_ebCredit;
	CRadioBtn		m_rbFxdDebit;
	CRadioBtn		m_rbVarDebit;
	CDecimalBox		m_ebDebit;
	CListBox		m_lbDebits;
	CNotesDlg		m_oNotesDlg;

	//
	// Message processors.
	//
	virtual void OnInitDialog();
	virtual bool OnOk();
	
	void OnNotes();
	void OnFxdCredit();
	void OnVarCredit();
	void OnFxdDebit();
	void OnVarDebit();
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

#endif //BALSHTITEMDLG_HPP
