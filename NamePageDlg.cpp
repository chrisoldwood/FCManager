/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		NAMEPAGEDLG.CPP
** COMPONENT:	The Application.
** DESCRIPTION:	CNamePageDlg class definition.
**
*******************************************************************************
*/

#include "AppHeaders.hpp"
#include "NamePageDlg.hpp"

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

CNamePageDlg::CNamePageDlg()
	: CPropertyPageDlg(IDD_NAME_PAGE)
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

void CNamePageDlg::OnInitDialog()
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
** Method:		OnOk()
**
** Description:	Validate the data and close the dialog.
**
** Parameters:	None.
**
** Returns:		true or false.
**
*******************************************************************************
*/

bool CNamePageDlg::OnOk()
{
	m_strSurname    = m_ebSurname.Text();
	m_strForename   = m_ebForename.Text();
	m_strStdPhone   = m_ebStdPhone.Text();
	m_strAltPhone   = m_ebAltPhone.Text();
	m_strEmailAddr  = m_ebEmailAddr.Text();
	m_strPostalAddr = m_ebPostalAddr.Text();

	return true;
}
