/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		STATTYPEDLG.CPP
** COMPONENT:	The Application.
** DESCRIPTION:	CStatTypeDlg class definition.
**
*******************************************************************************
*/

#include "AppHeaders.hpp"
#include "StatTypeDlg.hpp"

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

CStatTypeDlg::CStatTypeDlg(CRow& oRow)
	: CDialog(IDD_STAT_TYPE)
	, m_oRow(oRow)
{
	DEFINE_CTRL_TABLE
		CTRL(IDC_NAME,	&m_ebName)
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

void CStatTypeDlg::OnInitDialog()
{
	// Setup the controls.
	m_ebName.TextLimit(CStatTypes::NAME_LEN);

	// Initialise the controls with data.
	m_ebName.Text(m_oRow[CStatTypes::NAME]);
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

bool CStatTypeDlg::OnOk()
{
	// Get the controls data.
	CString strName = m_ebName.Text();

	// Validate it.
	if (strName.Length() == 0)
	{
		AlertMsg("You must provide a name.");
		return false;
	}

	// Save the data.
	m_oRow[CStatTypes::NAME] = strName;

	return true;
}
