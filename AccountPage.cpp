/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		ACCOUNTPAGE.CPP
** COMPONENT:	The Application.
** DESCRIPTION:	CAccountPage class definition.
**
*******************************************************************************
*/

#include "AppHeaders.hpp"
#include "AccountPage.hpp"

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

CAccountPage::CAccountPage(CRow& oRow)
	: CPropertyPage(IDD_ACCOUNT_PAGE)
	, m_oRow(oRow)
	, m_strName(oRow[CAccounts::NAME])
{
	DEFINE_CTRL_TABLE
		CTRL(IDC_NAME, &m_ebName)
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

void CAccountPage::OnInitDialog()
{
	// Initialise the controls.
	m_ebName.TextLimit(CAccounts::NAME_LEN);

	// Initialise the fields with data.
	m_ebName.Text(m_strName);
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

bool CAccountPage::OnValidate()
{
	m_strName = m_ebName.Text();

	// At least the name supplied?
	if (m_ebName.TextLength() == 0)
	{
		AlertMsg("You must provide at least a name for the account");
		return false;
	}

	return true;
}

/******************************************************************************
** Method:		OnOk()
**
** Description:	Save the data.
**
** Parameters:	None.
**
** Returns:		true or false.
**
*******************************************************************************
*/

bool CAccountPage::OnOk()
{
	m_oRow[CAccounts::NAME] = m_strName;

	return true;
}
