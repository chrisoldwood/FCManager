/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		INCOMEPAGE.CPP
** COMPONENT:	The Application.
** DESCRIPTION:	CIncomePage class definition.
**
*******************************************************************************
*/

#include "AppHeaders.hpp"
#include "IncomePage.hpp"
#include "MemberSubsDlg.hpp"

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

CIncomePage::CIncomePage(CRow& oRow, CTmpSubs& oTmpSubs, CMembers& oMembers)
	: CPropertyPage(IDD_INCOME_PAGE)
	, m_oRow(oRow)
	, m_oTmpSubs(oTmpSubs)
	, m_oMembers(oMembers)
	, m_nType(oRow[CBalSheet::CREDIT_TYPE])
	, m_nTotal(oRow[CBalSheet::CREDIT_TOTAL])
	, m_ebCredit(false, 6, 2)
{
	DEFINE_CTRL_TABLE
		CTRL(IDC_NO_CREDIT,			&m_rbNoCredit )
		CTRL(IDC_FIXED_CREDIT,		&m_rbFxdCredit)
		CTRL(IDC_VARIABLE_CREDIT,	&m_rbVarCredit)
		CTRL(IDC_CREDIT,			&m_ebCredit   )
		CTRL(IDC_CREDITS,			&m_lvCredits  )
	END_CTRL_TABLE

	DEFINE_CTRLMSG_TABLE
		CMD_CTRLMSG(IDC_NO_CREDIT,			BN_CLICKED, OnNoCredit  )
		CMD_CTRLMSG(IDC_FIXED_CREDIT,		BN_CLICKED, OnFxdCredit )
		CMD_CTRLMSG(IDC_VARIABLE_CREDIT,	BN_CLICKED, OnVarCredit )
		CMD_CTRLMSG(IDC_ADD_CREDIT,			BN_CLICKED, OnAddCredit )
		CMD_CTRLMSG(IDC_EDIT_CREDIT,		BN_CLICKED, OnEditCredit)
		CMD_CTRLMSG(IDC_DEL_CREDIT,			BN_CLICKED, OnDelCredit )
		NFY_CTRLMSG(IDC_CREDITS,			NM_DBLCLK,  OnDblClick )
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

void CIncomePage::OnInitDialog()
{
	// Initialise the controls.
	m_lvCredits.InsertColumn(0, "Name",   125);
	m_lvCredits.InsertColumn(1, "£ Fee",   50);
	m_lvCredits.InsertColumn(2, "£ Paid",  50);

	m_lvCredits.FullRowSelect();
	m_lvCredits.GridLines();

	// Initialise the fields with data.
	m_ebCredit.Value(m_nTotal / 100.0);

	// Initialise controls.
	switch(m_nType)
	{
		case CBalSheet::NONE:
			m_rbNoCredit.Check(true);
			OnNoCredit();
			break;

		case CBalSheet::FIXED:
			m_rbFxdCredit.Check(true);
			OnFxdCredit();
			break;

		case CBalSheet::VARIABLE:
			m_rbVarCredit.Check(true);
			OnVarCredit();
			break;

		default:
			ASSERT(false);
			break;
	}

	// Load the credits/debits ListViews.
	RefreshCredits();
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

bool CIncomePage::OnValidate()
{
	m_nTotal = (int) (m_ebCredit.Value() * 100.0);
	m_nType  = CBalSheet::NONE;

	if (m_rbFxdCredit.IsChecked())
		m_nType = CBalSheet::FIXED;
	else if (m_rbVarCredit.IsChecked())
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

bool CIncomePage::OnOk()
{
	int nDebit = m_oRow[CBalSheet::DEBIT_TOTAL];

	m_oRow[CBalSheet::CREDIT_TYPE]  = m_nType;
	m_oRow[CBalSheet::CREDIT_TOTAL] = m_nTotal;
	m_oRow[CBalSheet::BALANCE]      = m_nTotal - nDebit;

	return true;
}

/******************************************************************************
** Methods:		OnFxdCredit()
**				OnVarCredit()
**
** Description:	Radio button pushed. Enable/Disable the relevant controls.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CIncomePage::OnNoCredit()
{
	m_ebCredit.Enable(false);
	m_lvCredits.Enable(false);

	Control(IDC_ADD_CREDIT).Enable(false);
	Control(IDC_EDIT_CREDIT).Enable(false);
	Control(IDC_DEL_CREDIT).Enable(false);

	m_ebCredit.Value(0.0);
}

void CIncomePage::OnFxdCredit()
{
	m_ebCredit.Enable(true);
	m_lvCredits.Enable(false);

	Control(IDC_ADD_CREDIT).Enable(false);
	Control(IDC_EDIT_CREDIT).Enable(false);
	Control(IDC_DEL_CREDIT).Enable(false);
}

void CIncomePage::OnVarCredit()
{
	m_ebCredit.Enable(false);
	m_lvCredits.Enable(true);

	m_lvCredits.Select(0);
	UpdateCreditBtns();
	UpdateCreditsTotal();
}

/******************************************************************************
** Methods:		OnAddCredit()
**				OnEditCredit()
**				OnDelCredit()
**
** Description:	Variable credit buttons pushed. Add, Edit or Delete a members
**				subs entry.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CIncomePage::OnAddCredit()
{
	// Allocate a new Subs table row.
	CRow&       oRow = m_oTmpSubs.CreateRow();
	TArray<int> oExclusions;

	// Create a list of members to exclude.
	for (int i = 0; i < m_oTmpSubs.RowCount(); i++)
		oExclusions.Add(m_oTmpSubs[i][CSubs::MEMBER_ID]);

	CMemberSubsDlg Dlg(m_oMembers, oExclusions, oRow, false);

	if (Dlg.RunModal(*this) == IDOK)
	{
		m_oTmpSubs.InsertRow(oRow);
		RefreshCredits();
		UpdateCreditBtns();
		UpdateCreditsTotal();
	}
	else
	{
		delete &oRow;
	}
}

void CIncomePage::OnEditCredit()
{
	// Get subs row.
	CRow&       oRow = m_oTmpSubs[m_lvCredits.ItemData(m_lvCredits.Selection())];
	TArray<int> oExclusions;

	CMemberSubsDlg Dlg(m_oMembers, oExclusions, oRow, true);

	if (Dlg.RunModal(*this) == IDOK)
	{
		RefreshCredits();
		UpdateCreditsTotal();
	}
}

void CIncomePage::OnDelCredit()
{
	// Delete subs row.
	m_oTmpSubs.DeleteRow(m_lvCredits.ItemData(m_lvCredits.Selection()));

	RefreshCredits();
	UpdateCreditBtns();
	UpdateCreditsTotal();
}

LRESULT CIncomePage::OnDblClick(NMHDR&)
{
	// User double-clicked an item?
	if (m_lvCredits.IsSelection())
		OnEditCredit();

	return 0;
}

/******************************************************************************
** Methods:		RefreshCredits()
**
** Description:	Reloads the credits ListView.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CIncomePage::RefreshCredits()
{
	// Save old selection.
	int nSel = m_lvCredits.Selection();

	// Clear ListView.
	m_lvCredits.Redraw(false);
	m_lvCredits.DeleteAllItems();

	// For all subs rows.
	for (int i = 0; i < m_oTmpSubs.RowCount(); i++)
	{
		CRow& oSubs = m_oTmpSubs[i];

		// Find the members entry.
		CRow* pMember = m_oMembers.SelectRow(CMembers::ID, oSubs[CSubs::MEMBER_ID]);
		ASSERT(pMember != NULL);

		// Create ListView fields.
		CString strName = App.FormatName(*pMember, CMembers::FORENAME, CMembers::SURNAME, true);
		CString strFee  = App.FormatMoney(oSubs, CSubs::FEE);
		CString strPaid = App.FormatMoney(oSubs, CSubs::PAID);

		// Add the the ListView.
		int n = m_lvCredits.AppendItem(strName);
		m_lvCredits.ItemText(n, 1, strFee);
		m_lvCredits.ItemText(n, 2, strPaid);
		m_lvCredits.ItemData(n, i);
	}

	// Restore old selection.
	m_lvCredits.RestoreSel(nSel);

	// Redraw.
	m_lvCredits.Redraw(true);
	m_lvCredits.Invalidate();
}

/******************************************************************************
** Methods:		UpdateCreditBtns()
**
** Description:	Updates the Add/Edit/Delete buttons.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CIncomePage::UpdateCreditBtns()
{
	bool bSubsRows = (m_oTmpSubs.RowCount() > 0);
	bool bSubsLeft = (m_oTmpSubs.RowCount() != m_oMembers.RowCount());

	Control(IDC_ADD_CREDIT).Enable(bSubsLeft);
	Control(IDC_EDIT_CREDIT).Enable(bSubsRows);
	Control(IDC_DEL_CREDIT).Enable(bSubsRows);
}

/******************************************************************************
** Methods:		UpdateCreditsTotal()
**
** Description:	Updates the sums of the credits/debits.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CIncomePage::UpdateCreditsTotal()
{
	int nTotal = 0;

	for (int i = 0; i < m_oTmpSubs.RowCount(); i++)
		nTotal += m_oTmpSubs[i][CSubs::PAID].GetInt();

	m_ebCredit.Value(nTotal / 100.0);
}
