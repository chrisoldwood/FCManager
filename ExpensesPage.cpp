/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		EXPENSESPAGE.CPP
** COMPONENT:	The Application.
** DESCRIPTION:	CExpensesPage class definition.
**
*******************************************************************************
*/

#include "AppHeaders.hpp"
#include "ExpensesPage.hpp"

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

CExpensesPage::CExpensesPage(CRow& oRow)
	: CPropertyPage(IDD_EXPENSES_PAGE)
	, m_oRow(oRow)
	, m_nType(oRow[CBalSheet::DEBIT_TYPE])
	, m_nTotal(oRow[CBalSheet::DEBIT_TOTAL])
	, m_ebDebit(false, 6, 2)
{
	DEFINE_CTRL_TABLE
		CTRL(IDC_NO_DEBIT,			&m_rbNoDebit )
		CTRL(IDC_FIXED_DEBIT,		&m_rbFxdDebit)
		CTRL(IDC_VARIABLE_DEBIT,	&m_rbVarDebit)
		CTRL(IDC_DEBIT,				&m_ebDebit   )
		CTRL(IDC_DEBITS,			&m_lbDebits  )
	END_CTRL_TABLE

	DEFINE_CTRLMSG_TABLE
		CMD_CTRLMSG(IDC_NO_DEBIT,			BN_CLICKED, OnNoDebit  )
		CMD_CTRLMSG(IDC_FIXED_DEBIT,		BN_CLICKED, OnFxdDebit )
		CMD_CTRLMSG(IDC_VARIABLE_DEBIT,		BN_CLICKED, OnVarDebit )
		CMD_CTRLMSG(IDC_ADD_DEBIT,			BN_CLICKED, OnAddDebit )
		CMD_CTRLMSG(IDC_EDIT_DEBIT,			BN_CLICKED, OnEditDebit)
		CMD_CTRLMSG(IDC_DEL_DEBIT,			BN_CLICKED, OnDelDebit )
		CMD_CTRLMSG(IDC_DEBITS,				LBN_DBLCLK, OnEditDebit)
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

void CExpensesPage::OnInitDialog()
{
	// Initialise the controls.
	enum { NUM_TABSTOPS = 2 };

	int aiTabStops[NUM_TABSTOPS] = { 75, 105 };

	m_lbDebits.SetTabStops(NUM_TABSTOPS, aiTabStops);

	// Initialise the fields with data.
	m_ebDebit.Value(m_nTotal / 100.0);

	// Initialise controls.
	switch(m_nType)
	{
		case CBalSheet::NONE:
			m_rbNoDebit.Check(true);
			OnNoDebit();
			break;

		case CBalSheet::FIXED:
			m_rbFxdDebit.Check(true);
			OnFxdDebit();
			break;

		case CBalSheet::VARIABLE:
			m_rbVarDebit.Check(true);
			OnVarDebit();
			break;

		default:
			ASSERT(false);
			break;
	}

	// Load the credits/debits listboxes.
	RefreshDebits();
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

bool CExpensesPage::OnValidate()
{
	m_nTotal = (int) (m_ebDebit.Value() * 100.0);
	m_nType  = CBalSheet::NONE;

	if (m_rbFxdDebit.IsChecked())
		m_nType = CBalSheet::FIXED;
	else if (m_rbVarDebit.IsChecked())
		m_nType = CBalSheet::VARIABLE;

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

bool CExpensesPage::OnOk()
{
	int nCredit = m_oRow[CBalSheet::CREDIT_TOTAL];

	m_oRow[CBalSheet::DEBIT_TYPE]  = m_nType;
	m_oRow[CBalSheet::DEBIT_TOTAL] = m_nTotal;
	m_oRow[CBalSheet::BALANCE]     = nCredit - m_nTotal;

	return true;
}

/******************************************************************************
** Methods:		OnFxdDebit()
**				OnVarDebit()
**
** Description:	Radio button pushed. Enable/Disable the relevant controls.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CExpensesPage::OnNoDebit()
{
	m_ebDebit.Enable(false);
	m_lbDebits.Enable(false);

	Control(IDC_ADD_DEBIT).Enable(false);
	Control(IDC_EDIT_DEBIT).Enable(false);
	Control(IDC_DEL_DEBIT).Enable(false);

	m_ebDebit.Value(0.0);
}

void CExpensesPage::OnFxdDebit()
{
	m_ebDebit.Enable(true);
	m_lbDebits.Enable(false);

	Control(IDC_ADD_DEBIT).Enable(false);
	Control(IDC_EDIT_DEBIT).Enable(false);
	Control(IDC_DEL_DEBIT).Enable(false);
}

void CExpensesPage::OnVarDebit()
{
	m_ebDebit.Enable(false);
	m_lbDebits.Enable(true);

	m_lbDebits.CurSel(0);
	UpdateDebitBtns();
}

/******************************************************************************
** Methods:		OnAddDebit()
**				OnEditDebit()
**				OnDelDebit()
**
** Description:	Variable debit buttons pushed. Add, Edit or Delete an
**				 expenditure entry.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CExpensesPage::OnAddDebit()
{
}

void CExpensesPage::OnEditDebit()
{
}

void CExpensesPage::OnDelDebit()
{
}

/******************************************************************************
** Methods:		RefreshDebits()
**
** Description:	Reloads the appropriate listbox.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CExpensesPage::RefreshDebits()
{
}

/******************************************************************************
** Methods:		UpdateDebitBtns()
**
** Description:	Updates the Add/Edit/Delete buttons.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CExpensesPage::UpdateDebitBtns()
{
	Control(IDC_ADD_DEBIT).Enable(false);
	Control(IDC_EDIT_DEBIT).Enable(false);
	Control(IDC_DEL_DEBIT).Enable(false);
}

/******************************************************************************
** Methods:		UpdateDebitsTotal()
**
** Description:	Updates the sums of the credits/debits.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CExpensesPage::UpdateDebitsTotal()
{
}
