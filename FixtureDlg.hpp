/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		FIXTUREDLG.HPP
** COMPONENT:	The Application.
** DESCRIPTION:	The CFixtureDlg class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef FIXTUREDLG_HPP
#define FIXTUREDLG_HPP

/******************************************************************************
** 
** This dialog is used to enter/edit a fixtures details.
**
*******************************************************************************
*/

class CFixtureDlg : public CDialog
{
public:
	//
	// Constructors/Destructor.
	//
	CFixtureDlg(CRow& oFixture, bool bEditing);
	
	//
	// Members.
	//
	CRow&	m_oFixture;
	
protected:
	//
	// Members.
	//
	bool		m_bEditing;

	CDateTimePicker	m_dtpDate;
	CComboBox		m_cbType;
	CComboBox		m_cbHomeTeam;
	CComboBox		m_cbAwayTeam;
	CComboBox		m_cbReferee;
	CEditBox		m_ebResult;
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

#endif //FIXTUREDLG_HPP
