/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		OPPONENTDLG.HPP
** COMPONENT:	The Application.
** DESCRIPTION:	The COpponentDlg class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef OPPONENTDLG_HPP
#define OPPONENTDLG_HPP

/******************************************************************************
** 
** This dialog is used to enter/edit an opponents details.
**
*******************************************************************************
*/

class COpponentDlg : public CDialog
{
public:
	//
	// Constructors/Destructor.
	//
	COpponentDlg(CRow& oOpponent, bool bEditing);
	
	//
	// Members.
	//
	CRow&	m_oOpponent;
	
protected:
	//
	// Members.
	//
	bool		m_bEditing;

	CEditBox	m_ebClubName;
	CEditBox	m_ebGround;
	CEditBox	m_ebStdColours;
	CEditBox	m_ebAltColours;
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

#endif //OPPONENTDLG_HPP
