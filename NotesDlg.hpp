/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		NOTESDLG.HPP
** COMPONENT:	The Application.
** DESCRIPTION:	The CNotesDlg class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef NOTESDLG_HPP
#define NOTESDLG_HPP

/******************************************************************************
** 
** This is the dialog that displays additional notes about an item.
**
*******************************************************************************
*/

class CNotesDlg : public CDialog
{
public:
	//
	// Constructors/Destructor.
	//
	CNotesDlg();
	
	//
	// Members.
	//
	CString	m_strNotes;
	int		m_nNotesLen;

protected:
	//
	// Members.
	//
	CEditBox	m_ebNotes;
	
	//
	// Message processors.
	//
	virtual void OnInitDialog();
	virtual bool OnOk();
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

#endif //NOTESDLG_HPP
