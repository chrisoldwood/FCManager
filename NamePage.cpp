/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		NAMEPAGE.CPP
** COMPONENT:	The Application.
** DESCRIPTION:	CNamePage class definition.
**
*******************************************************************************
*/

#include "AppHeaders.hpp"
#include "NamePage.hpp"

/******************************************************************************
** Method:		Constructor.
**
** Description:	.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

CNamePage::CNamePage(CRow& oRow)
	: CPropertyPage(IDD_NAME_PAGE)
	, m_oRow(oRow)
{
	DEFINE_CTRL_TABLE
		CTRL(IDC_SURNAME,			&m_ebSurname)
		CTRL(IDC_FORENAME,			&m_ebForename)
		CTRL(IDC_STD_PHONE,			&m_ebStdPhone)
		CTRL(IDC_ALT_PHONE,			&m_ebAltPhone)
		CTRL(IDC_EMAIL_ADDRESS,		&m_ebEmailAddr)
		CTRL(IDC_POSTAL_ADDRESS,	&m_ebPostalAddr)
	END_CTRL_TABLE
}

/******************************************************************************
** Method:		OnInitDialog()
**
** Description:	Initialise the dialog.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CNamePage::OnInitDialog()
{
	// Initialise the controls.
	m_ebSurname.TextLimit(m_nSurnameLen);
	m_ebForename.TextLimit(m_nForenameLen);
	m_ebStdPhone.TextLimit(m_nStdPhoneLen);
	m_ebAltPhone.TextLimit(m_nAltPhoneLen);
	m_ebEmailAddr.TextLimit(m_nEmailAddrLen);
	m_ebPostalAddr.TextLimit(m_nPostalAddrLen);

	// Initialise the fields with data.
	m_ebSurname.Text(m_strSurname);
	m_ebForename.Text(m_strForename);
	m_ebStdPhone.Text(m_strStdPhone);
	m_ebAltPhone.Text(m_strAltPhone);
	m_ebEmailAddr.Text(m_strEmailAddr);
	m_ebPostalAddr.Text(m_strPostalAddr);
}

/******************************************************************************
** Method:		OnValidate()
**
** Description:	Validate the data.
**
** Parameters:	None.
**
** Returns:		true or false.
**
*******************************************************************************
*/

bool CNamePage::OnValidate()
{
	m_strSurname    = m_ebSurname.Text();
	m_strForename   = m_ebForename.Text();
	m_strStdPhone   = m_ebStdPhone.Text();
	m_strAltPhone   = m_ebAltPhone.Text();
	m_strEmailAddr  = m_ebEmailAddr.Text();
	m_strPostalAddr = m_ebPostalAddr.Text();

	return true;
}
