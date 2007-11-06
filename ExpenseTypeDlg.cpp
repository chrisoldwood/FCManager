/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		EXPENSETYPEDLG.CPP
** COMPONENT:	The Application.
** DESCRIPTION:	CExpenseTypeDlg class definition.
**
*******************************************************************************
*/

#include "Common.hpp"
#include "ExpenseTypeDlg.hpp"
#include "ExpenseTypes.hpp"

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

CExpenseTypeDlg::CExpenseTypeDlg(CRow& oRow)
	: CDialog(IDD_EXPENSE_TYPE)
	, m_oRow(oRow)
	, m_ebDefault(false, 6, 2)
{
	DEFINE_CTRL_TABLE
		CTRL(IDC_NAME,		&m_ebName)
		CTRL(IDC_DEFAULT,	&m_ebDefault)
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

void CExpenseTypeDlg::OnInitDialog()
{
	// Setup the controls.
	m_ebName.TextLimit(CExpenseTypes::NAME_LEN);

	// Initialise the controls with data.
	m_ebName.Text(m_oRow[CExpenseTypes::NAME]);
	m_ebDefault.RealValue(m_oRow[CExpenseTypes::DEFAULT].GetInt() / 100.0);
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

bool CExpenseTypeDlg::OnOk()
{
	// Get the controls data.
	CString strName  = m_ebName.Text();
	int     nDefault = (int) (m_ebDefault.RealValue() * 100.0);

	// Validate it.
	if (strName.Length() == 0)
	{
		AlertMsg("You must provide a name.");
		return false;
	}

	// Save the data.
	m_oRow[CExpenseTypes::NAME]    = strName;
	m_oRow[CExpenseTypes::DEFAULT] = nDefault;

	return true;
}
