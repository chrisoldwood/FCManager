/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		NOTESPAGEDLG.HPP
** COMPONENT:	The Application.
** DESCRIPTION:	The CNotesPageDlg class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef NOTESPAGEDLG_HPP
#define NOTESPAGEDLG_HPP

/******************************************************************************
** 
** This is the property page dialog that shows the additional notes.
**
*******************************************************************************
*/

class CNotesPageDlg : public CPropertyPageDlg
{
public:
	//
	// Constructors/Destructor.
	//
	CNotesPageDlg();
	
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

#endif //NOTESPAGEDLG_HPP
