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
	, m_nType(oRow[CAccounts::TYPE])
	, m_nTotal(oRow[CAccounts::BALANCE])
	, m_ebBalance(true, 6, 2)
{
	DEFINE_CTRL_TABLE
		CTRL(IDC_NAME,     &m_ebName)
		CTRL(IDC_BALANCE,  &m_ebBalance)
		CTRL(IDC_FIXED,    &m_rbFixed)
		CTRL(IDC_VARIABLE, &m_rbVariable)
		CTRL(IDC_TRANS,    &m_lvTrans)
	END_CTRL_TABLE

	DEFINE_CTRLMSG_TABLE
		CMD_CTRLMSG(IDC_FIXED,		BN_CLICKED, OnFixed    )
		CMD_CTRLMSG(IDC_VARIABLE,	BN_CLICKED, OnVariable )
		CMD_CTRLMSG(IDC_ADD,		BN_CLICKED, OnAddTrans )
		CMD_CTRLMSG(IDC_EDIT,		BN_CLICKED, OnEditTrans)
		CMD_CTRLMSG(IDC_DEL,		BN_CLICKED, OnDelTrans )
		NFY_CTRLMSG(IDC_TRANS,		NM_DBLCLK,  OnDblClick )
	END_CTRLMSG_TABLE
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

	m_lvTrans.InsertColumn(0, "Transaction", 150);
	m_lvTrans.InsertColumn(1, "£ Amount",     75);

	m_lvTrans.FullRowSelect();
	m_lvTrans.GridLines();

	// Initialise the fields with data.
	m_ebName.Text(m_strName);
	m_ebBalance.RealValue(m_nTotal / 100.0);

	// Initialise controls.
	switch(m_nType)
	{
		case CAccounts::FIXED:
			m_rbFixed.Check(true);
			OnFixed();
			break;

		case CAccounts::VARIABLE:
			m_rbVariable.Check(true);
			OnVariable();
			break;

		default:
			ASSERT_FALSE();
			break;
	}

	// Load the Transactions ListView.
//	RefreshTrans();
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

	m_nTotal = (int) (m_ebBalance.RealValue() * 100.0);
	m_nType  = CAccounts::FIXED;

	if (m_rbFixed.IsChecked())
		m_nType = CAccounts::FIXED;
	else if (m_rbVariable.IsChecked())
		m_nType = CAccounts::VARIABLE;

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
	m_oRow[CAccounts::NAME]    = m_strName;
	m_oRow[CAccounts::TYPE]    = m_nType;
	m_oRow[CAccounts::BALANCE] = m_nTotal;

	return true;
}

/******************************************************************************
** Methods:		OnFixed()
**				OnVariable()
**
** Description:	Radio button pushed. Enable/Disable the relevant controls.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CAccountPage::OnFixed()
{
	m_ebBalance.Enable(true);
	m_lvTrans.Enable(false);

	Control(IDC_ADD).Enable(false);
	Control(IDC_EDIT).Enable(false);
	Control(IDC_DEL).Enable(false);
}

void CAccountPage::OnVariable()
{
	m_ebBalance.Enable(false);
	m_lvTrans.Enable(true);

	m_lvTrans.Select(0);
//	UpdateTransBtns();
//	UpdateTransTotal();
}

/******************************************************************************
** Methods:		OnAddTrans()
**				OnEditTrans()
**				OnDelTrans()
**
** Description:	Variable trans buttons pushed. Add, Edit or Delete a
**				transaction entry.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CAccountPage::OnAddTrans()
{
/*	// Allocate a new Expenses table row.
	CRow& oRow = m_oTmpExps.CreateRow();

	CExpenseItemDlg Dlg(m_oTypes, oRow, false);

	if (Dlg.RunModal(*this) == IDOK)
	{
		m_oTmpExps.InsertRow(oRow);
		RefreshDebits();
		UpdateDebitBtns();
		UpdateDebitsTotal();
	}
	else
	{
		delete &oRow;
	}*/
}

void CAccountPage::OnEditTrans()
{
	// Get expenses row.
/*	CRow& oRow = m_oTmpExps[m_lvDebits.ItemData(m_lvDebits.Selected())];

	CExpenseItemDlg Dlg(m_oTypes, oRow, true);

	if (Dlg.RunModal(*this) == IDOK)
	{
		RefreshDebits();
		UpdateDebitsTotal();
	}*/
}

void CAccountPage::OnDelTrans()
{
	// Delete expenses row.
/*	m_oTmpExps.DeleteRow(m_lvDebits.ItemData(m_lvDebits.Selected()));

	RefreshDebits();
	UpdateDebitBtns();
	UpdateDebitsTotal();*/
}

LRESULT CAccountPage::OnDblClick(NMHDR&)
{
	// User double-clicked an item?
	if (m_lvTrans.IsSelection())
		OnEditTrans();

	return 0;
}
