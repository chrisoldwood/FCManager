/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		SECNAMEPAGE.CPP
** COMPONENT:	The Application.
** DESCRIPTION:	CSecNamePage class definition.
**
*******************************************************************************
*/

#include "Common.hpp"
#include "SecNamePage.hpp"
#include "Opponents.hpp"

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

CSecNamePage::CSecNamePage(CRow& oRow)
	: CNamePage(oRow)
	, m_oRow(oRow)
{
	m_strSurname     = m_oRow[COpponents::SURNAME].GetString();
	m_strForename    = m_oRow[COpponents::FORENAME].GetString();
	m_strStdPhone    = m_oRow[COpponents::STANDARD_PHONE].GetString();
	m_strAltPhone    = m_oRow[COpponents::ALTERNATE_PHONE].GetString();
	m_strEmailAddr   = m_oRow[COpponents::EMAIL_ADDRESS].GetString();
	m_strPostalAddr  = m_oRow[COpponents::POSTAL_ADDRESS].GetString();

	m_nSurnameLen    = COpponents::SURNAME_LEN;
	m_nForenameLen   = COpponents::FORENAME_LEN;
	m_nStdPhoneLen   = COpponents::PHONE_LEN;
	m_nAltPhoneLen   = COpponents::PHONE_LEN;
	m_nEmailAddrLen  = COpponents::EMAIL_LEN;
	m_nPostalAddrLen = COpponents::POSTAL_LEN;
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

bool CSecNamePage::OnValidate()
{
	// Fetch the data.
	if (!CNamePage::OnValidate())
		return false;

	return true;
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

bool CSecNamePage::OnOk()
{
	m_oRow[COpponents::SURNAME]         = m_strSurname;
	m_oRow[COpponents::FORENAME]        = m_strForename;
	m_oRow[COpponents::STANDARD_PHONE]  = m_strStdPhone;
	m_oRow[COpponents::ALTERNATE_PHONE] = m_strAltPhone;
	m_oRow[COpponents::EMAIL_ADDRESS]   = m_strEmailAddr;
	m_oRow[COpponents::POSTAL_ADDRESS]  = m_strPostalAddr;

	return true;
}
