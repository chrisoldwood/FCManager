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
#include "ExpenseItemDlg.hpp"

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

CExpensesPage::CExpensesPage(CRow& oRow, CTmpExps& oTmpExps, CExpenseTypes& oTypes)
	: CPropertyPage(IDD_EXPENSES_PAGE)
	, m_oRow(oRow)
	, m_oTmpExps(oTmpExps)
	, m_oTypes(oTypes)
	, m_nType(oRow[CBalSheet::DEBIT_TYPE])
	, m_nTotal(oRow[CBalSheet::DEBIT_TOTAL])
	, m_ebDebit(false, 6, 2)
{
	DEFINE_CTRL_TABLE
		CTRL(IDC_NO_DEBIT,			&m_rbNoDebit )
		CTRL(IDC_FIXED_DEBIT,		&m_rbFxdDebit)
		CTRL(IDC_VARIABLE_DEBIT,	&m_rbVarDebit)
		CTRL(IDC_DEBIT,				&m_ebDebit   )
		CTRL(IDC_DEBITS,			&m_lvDebits  )
	END_CTRL_TABLE

	DEFINE_CTRLMSG_TABLE
		CMD_CTRLMSG(IDC_NO_DEBIT,			BN_CLICKED, OnNoDebit  )
		CMD_CTRLMSG(IDC_FIXED_DEBIT,		BN_CLICKED, OnFxdDebit )
		CMD_CTRLMSG(IDC_VARIABLE_DEBIT,		BN_CLICKED, OnVarDebit )
		CMD_CTRLMSG(IDC_ADD_DEBIT,			BN_CLICKED, OnAddDebit )
		CMD_CTRLMSG(IDC_EDIT_DEBIT,			BN_CLICKED, OnEditDebit)
		CMD_CTRLMSG(IDC_DEL_DEBIT,			BN_CLICKED, OnDelDebit )
		NFY_CTRLMSG(IDC_DEBITS,				NM_DBLCLK,  OnDblClick )
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
	m_lvDebits.InsertColumn(0, "Item",   125);
	m_lvDebits.InsertColumn(1, "£ Paid",  50);

	m_lvDebits.FullRowSelect();
	m_lvDebits.GridLines();

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

	// Load the credits/debits ListViews.
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
	m_lvDebits.Enable(false);

	Control(IDC_ADD_DEBIT).Enable(false);
	Control(IDC_EDIT_DEBIT).Enable(false);
	Control(IDC_DEL_DEBIT).Enable(false);

	m_ebDebit.Value(0.0);
}

void CExpensesPage::OnFxdDebit()
{
	m_ebDebit.Enable(true);
	m_lvDebits.Enable(false);

	Control(IDC_ADD_DEBIT).Enable(false);
	Control(IDC_EDIT_DEBIT).Enable(false);
	Control(IDC_DEL_DEBIT).Enable(false);
}

void CExpensesPage::OnVarDebit()
{
	m_ebDebit.Enable(false);
	m_lvDebits.Enable(true);

	m_lvDebits.Select(0);
	UpdateDebitBtns();
	UpdateDebitsTotal();
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
	// Allocate a new Expenses table row.
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
	}
}

void CExpensesPage::OnEditDebit()
{
	// Get expenses row.
	CRow& oRow = m_oTmpExps[m_lvDebits.ItemData(m_lvDebits.Selection())];

	CExpenseItemDlg Dlg(m_oTypes, oRow, true);

	if (Dlg.RunModal(*this) == IDOK)
	{
		RefreshDebits();
		UpdateDebitsTotal();
	}
}

void CExpensesPage::OnDelDebit()
{
	// Delete expenses row.
	m_oTmpExps.DeleteRow(m_lvDebits.ItemData(m_lvDebits.Selection()));

	RefreshDebits();
	UpdateDebitBtns();
	UpdateDebitsTotal();
}

LRESULT CExpensesPage::OnDblClick(NMHDR&)
{
	// User double-clicked an item?
	if (m_lvDebits.IsSelection())
		OnEditDebit();

	return 0;
}

/******************************************************************************
** Methods:		RefreshDebits()
**
** Description:	Reloads the appropriate ListView.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CExpensesPage::RefreshDebits()
{
	// Save old selection.
	int nSel = m_lvDebits.Selection();

	// Clear ListView.
	m_lvDebits.Redraw(false);
	m_lvDebits.DeleteAllItems();

	// For all subs rows.
	for (int i = 0; i < m_oTmpExps.RowCount(); i++)
	{
		CRow& oExps = m_oTmpExps[i];

		// Find the types entry.
		CRow* pType = m_oTypes.SelectRow(CExpenseTypes::ID, oExps[CExpenses::TYPE_ID]);
		ASSERT(pType != NULL);

		// Create ListView fields.
		CString strName = (*pType)[CExpenseTypes::NAME];
		CString strPaid = App.FormatMoney(oExps, CExpenses::PAID);

		// Add the the ListView.
		int n = m_lvDebits.AppendItem(strName, i, 0);
		m_lvDebits.ItemText(n, 1, strPaid);
	}

	// Restore old selection.
	m_lvDebits.RestoreSel(nSel);

	// Redraw.
	m_lvDebits.Redraw(true);
	m_lvDebits.Invalidate();
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
	bool bExpsRows = (m_oTmpExps.RowCount() > 0);
	bool bExpsLeft = true;

	Control(IDC_ADD_DEBIT).Enable(bExpsLeft);
	Control(IDC_EDIT_DEBIT).Enable(bExpsRows);
	Control(IDC_DEL_DEBIT).Enable(bExpsRows);
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
	int nTotal = 0;

	for (int i = 0; i < m_oTmpExps.RowCount(); i++)
		nTotal += m_oTmpExps[i][CExpenses::PAID].GetInt();

	m_ebDebit.Value(nTotal / 100.0);
}
