/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		MEMNAMEPAGE.CPP
** COMPONENT:	The Application.
** DESCRIPTION:	CMemNamePage class definition.
**
*******************************************************************************
*/

#include "AppHeaders.hpp"
#include "MemNamePage.hpp"

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

CMemNamePage::CMemNamePage(CRow& oRow)
	: CNamePage(oRow)
	, m_oRow(oRow)
{
	m_strSurname     = m_oRow[CMembers::SURNAME].GetString();
	m_strForename    = m_oRow[CMembers::FORENAME].GetString();
	m_strStdPhone    = m_oRow[CMembers::STANDARD_PHONE].GetString();
	m_strAltPhone    = m_oRow[CMembers::ALTERNATE_PHONE].GetString();
	m_strEmailAddr   = m_oRow[CMembers::EMAIL_ADDRESS].GetString();
	m_strPostalAddr  = m_oRow[CMembers::POSTAL_ADDRESS].GetString();

	m_nSurnameLen    = CMembers::SURNAME_LEN;
	m_nForenameLen   = CMembers::FORENAME_LEN;
	m_nStdPhoneLen   = CMembers::PHONE_LEN;
	m_nAltPhoneLen   = CMembers::PHONE_LEN;
	m_nEmailAddrLen  = CMembers::EMAIL_LEN;
	m_nPostalAddrLen = CMembers::POSTAL_LEN;
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

bool CMemNamePage::OnValidate()
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

	CMembers& oTable = static_cast<CMembers&>(m_oRow.Table());

	// Find members with the same name but different ID.
	CResultSet oRS = oTable.Select(CWhereEqual(CMembers::FORENAME,  m_ebForename.Text())
								   & CWhereEqual(CMembers::SURNAME, m_ebSurname.Text())
								   & CWhereNotEqual(CMembers::ID,   m_oRow[CMembers::ID]));

	// Member already exists?
	if (oRS.Count() > 0)
	{
		AlertMsg("A member with that name already exists");
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

bool CMemNamePage::OnOk()
{
	m_oRow[CMembers::SURNAME]         = m_strSurname;
	m_oRow[CMembers::FORENAME]        = m_strForename;
	m_oRow[CMembers::STANDARD_PHONE]  = m_strStdPhone;
	m_oRow[CMembers::ALTERNATE_PHONE] = m_strAltPhone;
	m_oRow[CMembers::EMAIL_ADDRESS]   = m_strEmailAddr;
	m_oRow[CMembers::POSTAL_ADDRESS]  = m_strPostalAddr;

	return true;
}
