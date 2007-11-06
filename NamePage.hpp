/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		NAMEPAGE.HPP
** COMPONENT:	The Application.
** DESCRIPTION:	The CNamePage class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef NAMEPAGE_HPP
#define NAMEPAGE_HPP

#if _MSC_VER > 1000
#pragma once
#endif

#include <WCL/CommonUI.hpp>

/******************************************************************************
** 
** This is the property page used to display the name and address.
**
*******************************************************************************
*/

class CNamePage : public CPropertyPage
{
public:
	//
	// Constructors/Destructor.
	//
	CNamePage(CRow& oRow);

protected:
	//
	// Members.
	//
	CRow&		m_oRow;

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
	virtual bool OnValidate();
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

#endif //NAMEPAGE_HPP
