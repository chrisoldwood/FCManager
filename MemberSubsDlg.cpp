/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		MEMBERSUBSLG.CPP
** COMPONENT:	The Application.
** DESCRIPTION:	CMemberSubsDlg class definition.
**
*******************************************************************************
*/

#include "AppHeaders.hpp"
#include "MemberSubsDlg.hpp"

/******************************************************************************
** Method:		Constructor.
**
** Description:	.
**
** Parameters:	oMembers	The members table.
**				oExclusions	The members to exclude.
**				oRow		The subs table row.
**				bEditing	Editing or creating row?
**
** Returns:		Nothing.
**
*******************************************************************************
*/

CMemberSubsDlg::CMemberSubsDlg(CMembers& oMembers, CIntArray& oExclusions, CRow& oRow, bool bEditing)
	: CDialog(IDD_MEMBER_SUBS)
	, m_oRow(oRow)
	, m_bEditing(bEditing)
	, m_ebFee(false, 6, 2)
	, m_ebPaid(false, 6, 2)
	, m_oMembers(oMembers)
	, m_oExclusions(oExclusions)
{
	DEFINE_CTRL_TABLE
		CTRL(IDC_MEMBERS,	&m_cbMembers)
		CTRL(IDC_FEE,		&m_ebFee)
		CTRL(IDC_PAID,		&m_ebPaid)
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

void CMemberSubsDlg::OnInitDialog()
{
	// Set the dialog title.
	Title((m_bEditing == true) ? "Edit Members Subs" : "Add A Members Subs");

	// Adding an entry?
	if (!m_bEditing)
	{
		// Load unused members into combo box.
		for (int i = 0; i < m_oMembers.RowCount(); i++)
		{
			CRow& oRow = m_oMembers[i];

			// Member already used?
			if (m_oExclusions.Find(oRow[CMembers::ID]) != -1)
				continue;

			// Create the combo string.
			CString strName = App.FormatName(oRow, CMembers::FORENAME, CMembers::SURNAME, true);

			// Add to the combo box.
			int n = m_cbMembers.Add(strName);
			m_cbMembers.ItemData(n, i);
		}
	}
	// Editing entry.
	else
	{
		// Find members details.
		int   nMember = m_oRow[CSubs::MEMBER_ID];
		CRow* pMember = m_oMembers.SelectRow(CMembers::ID, nMember);

		ASSERT(pMember != NULL);

		// Add to the combo box.
		m_cbMembers.Add(App.FormatName(*pMember, CMembers::FORENAME, CMembers::SURNAME, true));
	}

	// Default to first member.
	m_cbMembers.CurSel(0);
	m_cbMembers.Enable(!m_bEditing);

	// Initialise the fields with data.
	m_ebFee.Value (m_oRow[CSubs::FEE].GetInt()  / 100.0);
	m_ebPaid.Value(m_oRow[CSubs::PAID].GetInt() / 100.0);
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

bool CMemberSubsDlg::OnOk()
{
	// Fetch field data.
	int nRow = m_cbMembers.ItemData(m_cbMembers.CurSel());
	int nFee  = (int) (m_ebFee.Value()  * 100.0);
	int nPaid = (int) (m_ebPaid.Value() * 100.0);

	// Save member, if not editing.
	if (!m_bEditing)
		m_oRow[CSubs::MEMBER_ID] = m_oMembers[nRow][CMembers::ID];

	m_oRow[CSubs::FEE]  = nFee;
	m_oRow[CSubs::PAID] = nPaid;

	return true;
}
