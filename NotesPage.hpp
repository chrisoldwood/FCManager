/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		NOTESPAGE.HPP
** COMPONENT:	The Application.
** DESCRIPTION:	The CNotesPage class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef NOTESPAGE_HPP
#define NOTESPAGE_HPP

/******************************************************************************
** 
** This is the property page that shows the additional notes.
**
*******************************************************************************
*/

class CNotesPage : public CPropertyPage
{
public:
	//
	// Constructors/Destructor.
	//
	CNotesPage(CRow& oRow, int nColumn, int nMaxLen);
	
protected:
	//
	// Members.
	//
	CRow&		m_oRow;
	int			m_nColumn;

	CEditBox	m_ebNotes;

	CString		m_strNotes;
	int			m_nMaxLen;
	
	//
	// Message processors.
	//
	virtual void OnInitDialog();
	virtual bool OnValidate();
	virtual bool OnOk();
	virtual void OnActivate(bool bActivating);
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

#endif //NOTESPAGE_HPP
