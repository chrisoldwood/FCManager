/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		ACCOUNTPAGE.HPP
** COMPONENT:	The Application.
** DESCRIPTION:	The CAccountPage class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef ACCOUNTPAGE_HPP
#define ACCOUNTPAGE_HPP

/******************************************************************************
** 
** This dialog is used to enter/edit an accounts details.
**
*******************************************************************************
*/

class CAccountPage : public CPropertyPage
{
public:
	//
	// Constructors/Destructor.
	//
	CAccountPage(CRow& oRow);
	
protected:
	//
	// Members.
	//
	CRow&			m_oRow;

	CString			m_strName;

	CEditBox		m_ebName;

	//
	// Message processors.
	//
	virtual void OnInitDialog();
	virtual bool OnValidate();
	virtual bool OnOk();
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

#endif //ACCOUNTPAGE_HPP
