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
		CTRL(IDC_CREDITS,			&m_lbCredits  )
	END_CTRL_TABLE

	DEFINE_CTRLMSG_TABLE
		CMD_CTRLMSG(IDC_NO_CREDIT,			BN_CLICKED, OnNoCredit  )
		CMD_CTRLMSG(IDC_FIXED_CREDIT,		BN_CLICKED, OnFxdCredit )
		CMD_CTRLMSG(IDC_VARIABLE_CREDIT,	BN_CLICKED, OnVarCredit )
		CMD_CTRLMSG(IDC_ADD_CREDIT,			BN_CLICKED, OnAddCredit )
		CMD_CTRLMSG(IDC_EDIT_CREDIT,		BN_CLICKED, OnEditCredit)
		CMD_CTRLMSG(IDC_DEL_CREDIT,			BN_CLICKED, OnDelCredit )
		CMD_CTRLMSG(IDC_CREDITS,			LBN_DBLCLK, OnEditCredit)
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
	enum { NUM_TABSTOPS = 2 };

	int aiTabStops[NUM_TABSTOPS] = { 75, 105 };

	m_lbCredits.SetTabStops(NUM_TABSTOPS, aiTabStops);

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

	// Load the credits/debits listboxes.
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
	m_lbCredits.Enable(false);

	Control(IDC_ADD_CREDIT).Enable(false);
	Control(IDC_EDIT_CREDIT).Enable(false);
	Control(IDC_DEL_CREDIT).Enable(false);

	m_ebCredit.Value(0.0);
}

void CIncomePage::OnFxdCredit()
{
	m_ebCredit.Enable(true);
	m_lbCredits.Enable(false);

	Control(IDC_ADD_CREDIT).Enable(false);
	Control(IDC_EDIT_CREDIT).Enable(false);
	Control(IDC_DEL_CREDIT).Enable(false);
}

void CIncomePage::OnVarCredit()
{
	m_ebCredit.Enable(false);
	m_lbCredits.Enable(true);

	m_lbCredits.CurSel(0);
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
	CRow&     oRow = m_oTmpSubs.CreateRow();
	CIntArray oExclusions;

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
	CRow&     oRow = m_oTmpSubs[m_lbCredits.ItemData(m_lbCredits.CurSel())];
	CIntArray oExclusions;

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
	m_oTmpSubs.DeleteRow(m_lbCredits.ItemData(m_lbCredits.CurSel()));

	RefreshCredits();
	UpdateCreditBtns();
	UpdateCreditsTotal();
}

/******************************************************************************
** Methods:		RefreshCredits()
**
** Description:	Reloads the credits listbox.
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
	int nSel = m_lbCredits.CurSel();

	// Clear listbox.
	m_lbCredits.Redraw(false);
	m_lbCredits.Reset();

	// For all subs rows.
	for (int i = 0; i < m_oTmpSubs.RowCount(); i++)
	{
		CRow& oSubs = m_oTmpSubs[i];

		// Find the members entry.
		CRow* pMember = m_oMembers.SelectRow(CMembers::ID, oSubs[CSubs::MEMBER_ID]);
		ASSERT(pMember != NULL);

		// Create listbox fields.
		CString strName = App.FormatName(*pMember, CMembers::FORENAME, CMembers::SURNAME, true);
		CString strFee  = App.FormatMoney(oSubs, CSubs::FEE);
		CString strPaid = App.FormatMoney(oSubs, CSubs::PAID);
		CString strItem;

		strItem.Format("%s\t£ %s\t£ %s", strName, strFee, strPaid);

		// Add the the listbox.
		int n = m_lbCredits.Add(strItem);
		m_lbCredits.ItemData(n, i);
	}

	// Restore old selection.
	m_lbCredits.RestoreSel(nSel);

	// Redraw.
	m_lbCredits.Redraw(true);
	m_lbCredits.Invalidate();
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
