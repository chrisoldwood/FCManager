/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		NAMEPAGEDLG.HPP
** COMPONENT:	The Application.
** DESCRIPTION:	The CNamePageDlg class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef NAMEPAGEDLG_HPP
#define NAMEPAGEDLG_HPP

/******************************************************************************
** 
** This is the property page dialog used to display the name and address.
**
*******************************************************************************
*/

class CNamePageDlg : public CPropertyPageDlg
{
public:
	//
	// Constructors/Destructor.
	//
	CNamePageDlg();
	
	//
	// Members.
	//
	CString		m_strSurname;
	CString		m_strForename;
	CString		m_strStdPhone;
	CString		m_strAltPhone;
	CString		m_strEmailAddr;
	CString		m_strPostalAddr;

	int			m_nSurnameLen;
	int			m_nForenameLen;
	int			m_nStdPhoneLen;
	int			m_nAltPhoneLen;
	int			m_nEmailAddrLen;
	int			m_nPostalAddrLen;

protected:
	//
	// Members.
	//
	CEditBox	m_ebSurname;
	CEditBox	m_ebForename;
	CEditBox	m_ebStdPhone;
	CEditBox	m_ebAltPhone;
	CEditBox	m_ebEmailAddr;
	CEditBox	m_ebPostalAddr;

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

#endif //NAMEPAGEDLG_HPP
