/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		REFNAMEPAGE.CPP
** COMPONENT:	The Application.
** DESCRIPTION:	CRefNamePage class definition.
**
*******************************************************************************
*/

#include "AppHeaders.hpp"
#include "RefNamePage.hpp"

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

CRefNamePage::CRefNamePage(CRow& oRow)
	: CNamePage(oRow)
	, m_oRow(oRow)
{
	m_strSurname     = m_oRow[CReferees::SURNAME].GetString();
	m_strForename    = m_oRow[CReferees::FORENAME].GetString();
	m_strStdPhone    = m_oRow[CReferees::STANDARD_PHONE].GetString();
	m_strAltPhone    = m_oRow[CReferees::ALTERNATE_PHONE].GetString();
	m_strEmailAddr   = m_oRow[CReferees::EMAIL_ADDRESS].GetString();
	m_strPostalAddr  = m_oRow[CReferees::POSTAL_ADDRESS].GetString();

	m_nSurnameLen    = CReferees::SURNAME_LEN;
	m_nForenameLen   = CReferees::FORENAME_LEN;
	m_nStdPhoneLen   = CReferees::PHONE_LEN;
	m_nAltPhoneLen   = CReferees::PHONE_LEN;
	m_nEmailAddrLen  = CReferees::EMAIL_LEN;
	m_nPostalAddrLen = CReferees::POSTAL_LEN;
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

bool CRefNamePage::OnValidate()
{
	// Fetch the data.
	if (!CNamePage::OnValidate())
		return false;

	// At least part of the name supplied?
	if ( (m_ebSurname.TextLength() == 0) && (m_ebForename.TextLength() == 0) )
	{
		AlertMsg("You must provide either the first or last names");
		return false;
	}

	CReferees& oTable = static_cast<CReferees&>(m_oRow.Table());

	// Find referees with the same name but different ID.
	CResultSet oRS = oTable.Select(CWhereCmp(CReferees::FORENAME, CWhereCmp::EQUALS,     m_ebForename.Text())
								&& CWhereCmp(CReferees::SURNAME,  CWhereCmp::EQUALS,     m_ebSurname.Text())
								&& CWhereCmp(CReferees::ID,       CWhereCmp::NOT_EQUALS, m_oRow[CReferees::ID]));

	// Referee already exists?
	if (oRS.Count() > 0)
	{
		AlertMsg("A referee with that name already exists");
		return false;
	}

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

bool CRefNamePage::OnOk()
{
	m_oRow[CReferees::SURNAME]         = m_strSurname;
	m_oRow[CReferees::FORENAME]        = m_strForename;
	m_oRow[CReferees::STANDARD_PHONE]  = m_strStdPhone;
	m_oRow[CReferees::ALTERNATE_PHONE] = m_strAltPhone;
	m_oRow[CReferees::EMAIL_ADDRESS]   = m_strEmailAddr;
	m_oRow[CReferees::POSTAL_ADDRESS]  = m_strPostalAddr;

	return true;
}
