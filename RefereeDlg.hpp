/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		REFEREEDLG.HPP
** COMPONENT:	The Application.
** DESCRIPTION:	The CRefereeDlg class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef REFEREEDLG_HPP
#define REFEREEDLG_HPP

/******************************************************************************
** 
** This dialog is used to enter/edit a referees details.
**
*******************************************************************************
*/

class CRefereeDlg : public CDialog
{
public:
	//
	// Constructors/Destructor.
	//
	CRefereeDlg(CRow& oReferee, bool bEditing);
	
	//
	// Members.
	//
	CRow&	m_oReferee;
	
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

#endif //REFEREEDLG_HPP
