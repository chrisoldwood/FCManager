/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		EXPENSEITEMDLG.CPP
** COMPONENT:	The Application.
** DESCRIPTION:	CExpenseItemDlg class definition.
**
*******************************************************************************
*/

#include "Common.hpp"
#include "ExpenseItemDlg.hpp"
#include "ExpenseTypes.hpp"
#include "Expenses.hpp"

/******************************************************************************
** Method:		Constructor.
**
** Description:	.
**
** Parameters:	oTypes		The expense types table.
**				oRow		The subs table row.
**				bEditing	Editing or creating row?
**
** Returns:		Nothing.
**
*******************************************************************************
*/

CExpenseItemDlg::CExpenseItemDlg(CExpenseTypes& oTypes, CRow& oRow, bool bEditing)
	: CDialog(IDD_EXPENSE_ITEM)
	, m_oRow(oRow)
	, m_bEditing(bEditing)
	, m_ebPaid(false, 6, 2)
	, m_oTypes(oTypes)
{
	DEFINE_CTRL_TABLE
		CTRL(IDC_EXPENSES,	&m_cbTypes)
		CTRL(IDC_PAID,		&m_ebPaid)
	END_CTRL_TABLE

	DEFINE_CTRLMSG_TABLE
		CMD_CTRLMSG(IDC_EXPENSES, LBN_SELCHANGE, &CExpenseItemDlg::OnSelectType)
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

void CExpenseItemDlg::OnInitDialog()
{
	// Set the dialog title.
	Title((m_bEditing == true) ? TXT("Edit Expense") : TXT("Add An Expense"));

	// Adding an entry?
	if (!m_bEditing)
	{
		// Load types into combo box.
		for (size_t i = 0; i < m_oTypes.RowCount(); i++)
		{
			CRow& oRow = m_oTypes[i];

			// Add to the combo box.
			int n = m_cbTypes.Add(oRow[CExpenseTypes::NAME]);
			m_cbTypes.ItemData(n, i);
		}
	}
	// Editing entry.
	else
	{
		// Find type details.
		int   nType = m_oRow[CExpenses::TYPE_ID];
		CRow* pType = m_oTypes.SelectRow(CExpenseTypes::ID, nType);

		ASSERT(pType != NULL);

		// Add to the combo box.
		m_cbTypes.Add((*pType)[CExpenseTypes::NAME]);
	}

	// Default to first member.
	m_cbTypes.CurSel(0U);
	m_cbTypes.Enable(!m_bEditing);


	// Initialise the paid field.
	if (m_bEditing)
		m_ebPaid.RealValue(m_oRow[CExpenses::PAID].GetInt() / 100.0);
	else
		OnSelectType();
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

bool CExpenseItemDlg::OnOk()
{
	// Fetch field data.
	int nRow  = m_cbTypes.ItemData(m_cbTypes.CurSel());
	int nPaid = static_cast<int>(m_ebPaid.RealValue() * 100.0);

	// Save type, if not editing.
	if (!m_bEditing)
		m_oRow[CExpenses::TYPE_ID] = m_oTypes[nRow][CExpenseTypes::ID];

	m_oRow[CExpenses::PAID] = nPaid;

	return true;
}

/******************************************************************************
** Method:		OnSelectType()
**
** Description:	Expense type selected.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CExpenseItemDlg::OnSelectType()
{
	// Only if a new entry.
	if (!m_bEditing)
	{
		int nRow     = m_cbTypes.ItemData(m_cbTypes.CurSel());
		int nDefault = m_oTypes[nRow][CExpenseTypes::DEFAULT];

		// Set the default value.
		m_ebPaid.RealValue(nDefault / 100.0);
	}
}
