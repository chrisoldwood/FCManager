/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		CLUBDETAILSDLG.CPP
** COMPONENT:	The Application.
** DESCRIPTION:	CClubDetailsDlg class definition.
**
*******************************************************************************
*/

#include "AppHeaders.hpp"
#include "ClubDetailsDlg.hpp"

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

CClubDetailsDlg::CClubDetailsDlg(CRow& oDetails) : CDialog(IDD_CLUB_DETAILS)
	, m_oDetails(oDetails)
{
	DEFINE_CTRL_TABLE
		CTRL(IDC_CLUB_NAME,	&m_ebName)
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

void CClubDetailsDlg::OnInitDialog()
{
	// Initialise the controls.
	m_ebName.Text(m_oDetails[CClubDetails::NAME]);
	m_ebName.TextLimit(CClubDetails::NAME_LEN);
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

bool CClubDetailsDlg::OnOk()
{
	// Fetch data from the controls.
	m_oDetails[CClubDetails::NAME] = m_ebName.Text();

	return true;
}
