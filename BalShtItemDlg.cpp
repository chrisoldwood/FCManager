/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		BALSHTITEMDLG.CPP
** COMPONENT:	The Application.
** DESCRIPTION:	CBalShtItemDlg class definition.
**
*******************************************************************************
*/

#include "AppHeaders.hpp"
#include "BalShtItemDlg.hpp"
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

CBalShtItemDlg::CBalShtItemDlg(CMDB& oDB, CRow& oItem, bool bEditing)
	: CDialog(IDD_BALSHEET_ITEM)
	, m_oItem(oItem)
	, m_bEditing(bEditing)
	, m_ebCredit(false, 6, 2)
	, m_ebDebit(false, 6, 2)
	, m_oDB(oDB)
	, m_nItemID(oItem[CBalSheet::ID])
	, m_oTmpSubs(oDB, "#TmpSubs")
	, m_oMembers(oDB[CFCMDB::MEMBERS])
{
	DEFINE_CTRL_TABLE
		CTRL(IDC_NAME,				&m_ebName)
		CTRL(IDC_DATE,				&m_dtpDate)
		CTRL(IDC_TYPE,				&m_cbType)
		CTRL(IDC_NO_CREDIT,			&m_rbNoCredit)
		CTRL(IDC_FIXED_CREDIT,		&m_rbFxdCredit)
		CTRL(IDC_VARIABLE_CREDIT,	&m_rbVarCredit)
		CTRL(IDC_CREDIT,			&m_ebCredit)
		CTRL(IDC_CREDITS,			&m_lbCredits)
		CTRL(IDC_NO_DEBIT,			&m_rbNoDebit)
		CTRL(IDC_FIXED_DEBIT,		&m_rbFxdDebit)
		CTRL(IDC_VARIABLE_DEBIT,	&m_rbVarDebit)
		CTRL(IDC_DEBIT,				&m_ebDebit)
		CTRL(IDC_DEBITS,			&m_lbDebits)
	END_CTRL_TABLE

	DEFINE_CTRLMSG_TABLE
		CMD_CTRLMSG(IDC_NOTES,				BN_CLICKED, OnNotes)
		CMD_CTRLMSG(IDC_NO_CREDIT,			BN_CLICKED, OnNoCredit)
		CMD_CTRLMSG(IDC_FIXED_CREDIT,		BN_CLICKED, OnFxdCredit)
		CMD_CTRLMSG(IDC_VARIABLE_CREDIT,	BN_CLICKED, OnVarCredit)
		CMD_CTRLMSG(IDC_NO_DEBIT,			BN_CLICKED, OnNoDebit)
		CMD_CTRLMSG(IDC_FIXED_DEBIT,		BN_CLICKED, OnFxdDebit)
		CMD_CTRLMSG(IDC_VARIABLE_DEBIT,		BN_CLICKED, OnVarDebit)
		CMD_CTRLMSG(IDC_ADD_CREDIT,			BN_CLICKED, OnAddCredit)
		CMD_CTRLMSG(IDC_EDIT_CREDIT,		BN_CLICKED, OnEditCredit)
		CMD_CTRLMSG(IDC_DEL_CREDIT,			BN_CLICKED, OnDelCredit)
		CMD_CTRLMSG(IDC_ADD_DEBIT,			BN_CLICKED, OnAddDebit)
		CMD_CTRLMSG(IDC_EDIT_DEBIT,			BN_CLICKED, OnEditDebit)
		CMD_CTRLMSG(IDC_DEL_DEBIT,			BN_CLICKED, OnDelDebit)
		CMD_CTRLMSG(IDC_CREDITS,			LBN_DBLCLK, OnEditCredit)
		CMD_CTRLMSG(IDC_DEBITS,				LBN_DBLCLK, OnEditDebit)
	END_CTRLMSG_TABLE

	// Construct temporary subs table mirroring the real one.
	m_oTmpSubs.AddColumn("ItemID",   MDCT_INT,                0,            CColumn::DEFAULTS);
	m_oTmpSubs.AddColumn("MemberID", m_oDB[CFCMDB::MEMBERS],  CMembers::ID, CColumn::FOREIGN_KEY | CColumn::UNIQUE);
	m_oTmpSubs.AddColumn("Fee",      MDCT_INT,                0,            CColumn::DEFAULTS);
	m_oTmpSubs.AddColumn("Paid",     MDCT_INT,                0,            CColumn::DEFAULTS);
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

void CBalShtItemDlg::OnInitDialog()
{
	// Set the dialog title.
	Title((m_bEditing == true) ? "Edit Balance Sheet Item" : "Add A Balance Sheet Item");

	// Editing existing item?
	if (m_bEditing)
	{
		CTable& oTable  = m_oDB[CFCMDB::SUBS];

		// Fetch the current subs for the item.
		CResultSet oRS = oTable.Select(CWhereEqual(CSubs::ITEM_ID, m_nItemID));

		// Copy to temporary table.
		for (int i = 0; i < oRS.Count(); i++)
		{
			CRow& oOrig = oRS[i];
			CRow& oCopy = m_oTmpSubs.CreateRow();

			ASSERT(oOrig[CSubs::ITEM_ID] == m_nItemID);

			oCopy[CSubs::ITEM_ID]   = m_nItemID;
			oCopy[CSubs::MEMBER_ID] = oOrig[CSubs::MEMBER_ID];
			oCopy[CSubs::FEE]       = oOrig[CSubs::FEE];
			oCopy[CSubs::PAID]      = oOrig[CSubs::PAID];

			m_oTmpSubs.InsertRow(oCopy, false);
		}
	}

	// Initialise the controls.
	m_ebName.TextLimit(CBalSheet::NAME_LEN);
	m_dtpDate.Format("ddd' 'dd'/'MM'/'yyyy");

	m_cbType.Add("Other");
	m_cbType.Add("Match");
	m_cbType.Add("Training");

	// Listbox tab settings.
	enum { NUM_TABSTOPS = 2 };

	int aiTabStops[NUM_TABSTOPS] = { 75, 105 };

	m_lbCredits.SetTabStops(NUM_TABSTOPS, aiTabStops);
	m_lbDebits.SetTabStops(NUM_TABSTOPS, aiTabStops);

	// Initialise the fields with data.
	m_ebName.Text(m_oItem[CBalSheet::NAME]);
	m_dtpDate.SetDate(CDate(m_oItem[CBalSheet::DATE]));
	m_cbType.CurSel(m_oItem[CBalSheet::TYPE].GetInt());
	m_ebCredit.Value(m_oItem[CBalSheet::CREDIT_TOTAL].GetInt() / 100.0);
	m_ebDebit.Value(m_oItem[CBalSheet::DEBIT_TOTAL].GetInt() / 100.0);

	// Initialise the notes dialog.
	m_oNotesDlg.m_strNotes  = m_oItem[CBalSheet::NOTES];
	m_oNotesDlg.m_nNotesLen = CBalSheet::NOTES_LEN;

	// Initialise credits and debits controls.
	switch(m_oItem[CBalSheet::CREDIT_TYPE].GetInt())
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

	switch(m_oItem[CBalSheet::DEBIT_TYPE].GetInt())
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
	RefreshCredits();
	RefreshDebits();
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

bool CBalShtItemDlg::OnOk()
{
	// At least the name supplied?
	if (m_ebName.TextLength() == 0)
	{
		AlertMsg("You must provide at least a name for the item");
		return false;
	}

	int nCreditTotal = (int) (m_ebCredit.Value() * 100.0);
	int nDebitTotal  = (int) (m_ebDebit.Value()  * 100.0);
	int nCreditType  = CBalSheet::NONE;
	int nDebitType   = CBalSheet::NONE;

	if (m_rbFxdCredit.IsChecked())
		nCreditType = CBalSheet::FIXED;
	else if (m_rbVarCredit.IsChecked())
		nCreditType = CBalSheet::VARIABLE;

	if (m_rbFxdDebit.IsChecked())
		nDebitType = CBalSheet::FIXED;
	else if (m_rbVarDebit.IsChecked())
		nDebitType = CBalSheet::VARIABLE;

	// Update balance sheet row.
	m_oItem[CBalSheet::NAME]          = m_ebName.Text();
	m_oItem[CBalSheet::DATE]          = m_dtpDate.GetDate();
	m_oItem[CBalSheet::TYPE]          = m_cbType.CurSel();
	m_oItem[CBalSheet::CREDIT_TYPE]   = nCreditType;
	m_oItem[CBalSheet::CREDIT_TOTAL]  = nCreditTotal;
	m_oItem[CBalSheet::DEBIT_TYPE]    = nDebitType;
	m_oItem[CBalSheet::DEBIT_TOTAL]   = nDebitTotal;
	m_oItem[CBalSheet::BALANCE]       = nCreditTotal - nDebitTotal;
	m_oItem[CBalSheet::NOTES]         = m_oNotesDlg.m_strNotes;

	return true;
}

/******************************************************************************
** Method:		OnNotes()
**
** Description:	Show the notes editing dialog.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CBalShtItemDlg::OnNotes()
{
	m_oNotesDlg.RunModal(*this);
}

/******************************************************************************
** Methods:		OnFxdCredit()
**				OnVarCredit()
**				OnFxdDebit()
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

void CBalShtItemDlg::OnNoCredit()
{
	m_ebCredit.Enable(false);
	m_lbCredits.Enable(false);

	Control(IDC_ADD_CREDIT).Enable(false);
	Control(IDC_EDIT_CREDIT).Enable(false);
	Control(IDC_DEL_CREDIT).Enable(false);

	m_ebCredit.Value(0.0);
}

void CBalShtItemDlg::OnFxdCredit()
{
	m_ebCredit.Enable(true);
	m_lbCredits.Enable(false);

	Control(IDC_ADD_CREDIT).Enable(false);
	Control(IDC_EDIT_CREDIT).Enable(false);
	Control(IDC_DEL_CREDIT).Enable(false);
}

void CBalShtItemDlg::OnVarCredit()
{
	m_ebCredit.Enable(false);
	m_lbCredits.Enable(true);

	m_lbCredits.CurSel(0);
	UpdateCreditBtns();
	UpdateCreditsTotal();
}

void CBalShtItemDlg::OnNoDebit()
{
	m_ebDebit.Enable(false);
	m_lbDebits.Enable(false);

	Control(IDC_ADD_DEBIT).Enable(false);
	Control(IDC_EDIT_DEBIT).Enable(false);
	Control(IDC_DEL_DEBIT).Enable(false);

	m_ebDebit.Value(0.0);
}

void CBalShtItemDlg::OnFxdDebit()
{
	m_ebDebit.Enable(true);
	m_lbDebits.Enable(false);

	Control(IDC_ADD_DEBIT).Enable(false);
	Control(IDC_EDIT_DEBIT).Enable(false);
	Control(IDC_DEL_DEBIT).Enable(false);
}

void CBalShtItemDlg::OnVarDebit()
{
	m_ebDebit.Enable(false);
	m_lbDebits.Enable(true);

	m_lbDebits.CurSel(0);
	UpdateDebitBtns();
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

void CBalShtItemDlg::OnAddCredit()
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

void CBalShtItemDlg::OnEditCredit()
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

void CBalShtItemDlg::OnDelCredit()
{
	// Delete subs row.
	m_oTmpSubs.DeleteRow(m_lbCredits.ItemData(m_lbCredits.CurSel()));

	RefreshCredits();
	UpdateCreditBtns();
	UpdateCreditsTotal();
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

void CBalShtItemDlg::OnAddDebit()
{
}

void CBalShtItemDlg::OnEditDebit()
{
}

void CBalShtItemDlg::OnDelDebit()
{
}

/******************************************************************************
** Methods:		RefreshCredits()
**				RefreshDebits()
**
** Description:	Reloads the appropriate listbox.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CBalShtItemDlg::RefreshCredits()
{
	CTable& oMembers = m_oDB[CFCMDB::MEMBERS];

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
		CRow* pMember = oMembers.SelectRow(CMembers::ID, oSubs[CSubs::MEMBER_ID]);
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

void CBalShtItemDlg::RefreshDebits()
{
}

/******************************************************************************
** Methods:		UpdateCreditBtns()
**				UpdateDebitBtns()
**
** Description:	Updates the Add/Edit/Delete buttons.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CBalShtItemDlg::UpdateCreditBtns()
{
	bool bSubsRows = (m_oTmpSubs.RowCount() > 0);
	bool bSubsLeft = (m_oTmpSubs.RowCount() != m_oMembers.RowCount());

	Control(IDC_ADD_CREDIT).Enable(bSubsLeft);
	Control(IDC_EDIT_CREDIT).Enable(bSubsRows);
	Control(IDC_DEL_CREDIT).Enable(bSubsRows);
}

void CBalShtItemDlg::UpdateDebitBtns()
{
	Control(IDC_ADD_DEBIT).Enable(false);
	Control(IDC_EDIT_DEBIT).Enable(false);
	Control(IDC_DEL_DEBIT).Enable(false);
}

/******************************************************************************
** Methods:		UpdateCreditsTotal()
**				UpdateDebitsTotal()
**
** Description:	Updates the sums of the credits/debits.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CBalShtItemDlg::UpdateCreditsTotal()
{
	int nTotal = 0;

	for (int i = 0; i < m_oTmpSubs.RowCount(); i++)
		nTotal += m_oTmpSubs[i][CSubs::PAID].GetInt();

	m_ebCredit.Value(nTotal / 100.0);
}

void CBalShtItemDlg::UpdateDebitsTotal()
{
}

/******************************************************************************
** Methods:		UpdateSubsTable()
**				UpdateDebitsTotal()
**
** Description:	Updates the sums of the credits/debits.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CBalShtItemDlg::UpdateSubsTable()
{
	// Credits table untouched?
	if (!m_oTmpSubs.Modified())
		return;

	CTable& oSubs   = m_oDB[CFCMDB::SUBS];
	int     nItemID = m_oItem[CBalSheet::ID];

	// Was editing item?
	if (m_bEditing)
	{
		// Fetch the current subs for the item.
		CResultSet oRS = oSubs.Select(CWhereEqual(CSubs::ITEM_ID, nItemID));

		// Delete all rows for the item.
		for (int i = 0; i < oRS.Count(); i++)
			oSubs.DeleteRow(oRS[i]);
	}

	// Copy from temporary table to real table.
	for (int i = 0; i < m_oTmpSubs.RowCount(); i++)
	{
		CRow& oTmp = m_oTmpSubs[i];
		CRow& oNew = oSubs.CreateRow();

		oNew[CSubs::ITEM_ID]   = nItemID;
		oNew[CSubs::MEMBER_ID] = oTmp[CSubs::MEMBER_ID];
		oNew[CSubs::FEE]       = oTmp[CSubs::FEE];
		oNew[CSubs::PAID]      = oTmp[CSubs::PAID];

		oSubs.InsertRow(oNew);
	}
}

void CBalShtItemDlg::UpdateExpensesTable()
{
}
