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

CBalShtItemDlg::CBalShtItemDlg(CRow& oItem, bool bEditing) : CDialog(IDD_BALSHEET_ITEM)
	, m_oItem(oItem)
	, m_bEditing(bEditing)
	, m_ebCredit(false, 6, 2)
	, m_ebDebit(false, 6, 2)
{
	DEFINE_CTRL_TABLE
		CTRL(IDC_NAME,				&m_ebName)
		CTRL(IDC_DATE,				&m_dtpDate)
		CTRL(IDC_FIXED_CREDIT,		&m_rbFxdCredit)
		CTRL(IDC_VARIABLE_CREDIT,	&m_rbVarCredit)
		CTRL(IDC_CREDIT,			&m_ebCredit)
		CTRL(IDC_CREDITS,			&m_lbCredits)
		CTRL(IDC_FIXED_DEBIT,		&m_rbFxdDebit)
		CTRL(IDC_VARIABLE_DEBIT,	&m_rbVarDebit)
		CTRL(IDC_DEBIT,				&m_ebDebit)
		CTRL(IDC_DEBITS,			&m_lbDebits)
	END_CTRL_TABLE

	DEFINE_CTRLMSG_TABLE
		CMD_CTRLMSG(IDC_NOTES,				BN_CLICKED, OnNotes)
		CMD_CTRLMSG(IDC_FIXED_CREDIT,		BN_CLICKED, OnFxdCredit)
		CMD_CTRLMSG(IDC_VARIABLE_CREDIT,	BN_CLICKED, OnVarCredit)
		CMD_CTRLMSG(IDC_FIXED_DEBIT,		BN_CLICKED, OnFxdDebit)
		CMD_CTRLMSG(IDC_VARIABLE_DEBIT,		BN_CLICKED, OnVarDebit)
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

void CBalShtItemDlg::OnInitDialog()
{
	// Set the dialog title.
	Title((m_bEditing == true) ? "Edit Balance Sheet Item" : "Add A Balance Sheet Item");

	// Initialise the controls.
	m_ebName.TextLimit(CBalSheet::NAME_LEN);
	m_dtpDate.Format("ddd' 'dd'/'MM'/'yyyy");

	// Initialise the fields with data.
	m_ebName.Text(m_oItem[CBalSheet::NAME]);
	m_dtpDate.SetDate(m_oItem[CBalSheet::DATE]);
	m_rbFxdCredit.Check(true);
	m_rbVarCredit.Check(false);
	m_ebCredit.Value(m_oItem[CBalSheet::CREDIT].GetInt() / 100.0);
	m_rbFxdDebit.Check(true);
	m_rbVarDebit.Check(false);
	m_ebDebit.Value(m_oItem[CBalSheet::DEBIT].GetInt() / 100.0);

	// Initialise the notes dialog.
	m_oNotesDlg.m_strNotes  = m_oItem[CBalSheet::NOTES];
	m_oNotesDlg.m_nNotesLen = CBalSheet::NOTES_LEN;

	// Enable/Disable controls.
	OnFxdCredit();
	OnFxdDebit();
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
		AlertMsg("You must provide at least a name");
		return false;
	}

//	CBalSheet& oTable = static_cast<CBalSheet&>(m_oItem.Table());

	// Item already exists?
/*	if (oTable.Exists(m_ebForename.Text(), m_ebSurname.Text()))
	{
		AlertMsg("A referee with that name already exists");
		return false;
	}*/

	m_oItem[CBalSheet::NAME]   = m_ebName.Text();
	m_oItem[CBalSheet::DATE]   = m_dtpDate.GetDate();
	m_oItem[CBalSheet::CREDIT] = (int) (m_ebCredit.Value() * 100.0);
	m_oItem[CBalSheet::DEBIT]  = (int) (m_ebDebit.Value()  * 100.0);
	m_oItem[CBalSheet::TOTAL]  = (m_oItem[CBalSheet::CREDIT].GetInt() - m_oItem[CBalSheet::DEBIT].GetInt());
	m_oItem[CBalSheet::NOTES]  = m_oNotesDlg.m_strNotes;

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
** Method:		OnFxdCredit()
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
	Control(IDC_ADD_CREDIT).Enable(true);
	Control(IDC_EDIT_CREDIT).Enable(true);
	Control(IDC_DEL_CREDIT).Enable(true);
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
	Control(IDC_ADD_DEBIT).Enable(true);
	Control(IDC_EDIT_DEBIT).Enable(true);
	Control(IDC_DEL_DEBIT).Enable(true);
}
