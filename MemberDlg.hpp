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

/******************************************************************************
** 
** This dialog is used to enter/edit a members details.
**
*******************************************************************************
*/

class CMemberDlg : public CDialog
{
public:
	//
	// Constructors/Destructor.
	//
	CMemberDlg(CRow& oMember, bool bEditing);
	
	//
	// Members.
	//
	CRow&	m_oMember;
	
protected:
	//
	// Members.
	//
	bool		m_bEditing;

	CEditBox	m_ebSurname;
	CEditBox	m_ebForename;
	CEditBox	m_ebStdPhone;
	CEditBox	m_ebAltPhone;
	CEditBox	m_ebEmailAddr;
	CEditBox	m_ebPostalAddr;
	CCheckBox	m_ckIsRegtrd;
	CCheckBox	m_ckIsSenior;
	CComboBox	m_cbTeam;
	CComboBox	m_cbPosition;
	CNotesDlg	m_oNotesDlg;

	//
	// Message processors.
	//
	virtual void OnInitDialog();
	virtual bool OnOk();
	        void OnNotes();
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

#endif //MEMBERDLG_HPP
