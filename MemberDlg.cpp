/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		MEMBERDLG.CPP
** COMPONENT:	The Application.
** DESCRIPTION:	CMemberDlg class definition.
**
*******************************************************************************
*/

#include "AppHeaders.hpp"
#include "MemberDlg.hpp"

// List of teams.
static char* astrTeams[MAX_CLUB_TEAMS+1] =
{
	"Any", "1st Team", "2nd Team", "3rd Team"
};

// List of positions.
static char* astrPositions[MAX_POSITIONS+1] =
{
	"Any", "Goalkeeper", "Defender", "Midfielder", "Attacker"
};

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

CMemberDlg::CMemberDlg(CRow& oMember, bool bEditing) : CDialog(IDD_MEMBER)
	, m_oMember(oMember)
	, m_bEditing(bEditing)
{
	DEFINE_CTRL_TABLE
		CTRL(IDC_SURNAME,			&m_ebSurname)
		CTRL(IDC_FORENAME,			&m_ebForename)
		CTRL(IDC_STD_PHONE,			&m_ebStdPhone)
		CTRL(IDC_ALT_PHONE,			&m_ebAltPhone)
		CTRL(IDC_EMAIL_ADDRESS,		&m_ebEmailAddr)
		CTRL(IDC_POSTAL_ADDRESS,	&m_ebPostalAddr)
		CTRL(IDC_REGISTERED,		&m_ckIsRegtrd)
		CTRL(IDC_SENIOR,			&m_ckIsSenior)
		CTRL(IDC_USUAL_TEAM,		&m_cbTeam)
		CTRL(IDC_USUAL_POS,			&m_cbPosition)
	END_CTRL_TABLE

	DEFINE_CTRLMSG_TABLE
		CMD_CTRLMSG(IDC_NOTES, BN_CLICKED, OnNotes)
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

void CMemberDlg::OnInitDialog()
{
	// Set the dialog title.
	Title((m_bEditing == true) ? "Edit Member Details" : "Add A Member");

	// Initialise the controls.
	m_ebSurname.TextLimit(CMembers::SURNAME_LEN);
	m_ebForename.TextLimit(CMembers::FORENAME_LEN);
	m_ebStdPhone.TextLimit(CMembers::PHONE_LEN);
	m_ebAltPhone.TextLimit(CMembers::PHONE_LEN);
	m_ebEmailAddr.TextLimit(CMembers::EMAIL_LEN);
	m_ebPostalAddr.TextLimit(CMembers::POSTAL_LEN);

	for (int i = 0; i < MAX_CLUB_TEAMS+1; i++)
		m_cbTeam.Add(astrTeams[i]);

	for (int j = 0; j < MAX_POSITIONS+1; j++)
		m_cbPosition.Add(astrPositions[j]);

	// Initialise the fields with data.
	m_ebSurname.Text(m_oMember[CMembers::SURNAME]);
	m_ebForename.Text(m_oMember[CMembers::FORENAME]);
	m_ebStdPhone.Text(m_oMember[CMembers::STANDARD_PHONE]);
	m_ebAltPhone.Text(m_oMember[CMembers::ALTERNATE_PHONE]);
	m_ebEmailAddr.Text(m_oMember[CMembers::EMAIL_ADDRESS]);
	m_ebPostalAddr.Text(m_oMember[CMembers::POSTAL_ADDRESS]);
	m_ckIsRegtrd.Check(m_oMember[CMembers::IS_REGISTERED]);
	m_ckIsSenior.Check(m_oMember[CMembers::IS_SENIOR]);
	m_cbTeam.CurSel(m_oMember[CMembers::USUAL_TEAM].GetInt());
	m_cbPosition.CurSel(m_oMember[CMembers::USUAL_POSITION].GetInt());

	// Initialise the notes dialog.
	m_oNotesDlg.m_strNotes  = m_oMember[CMembers::NOTES];
	m_oNotesDlg.m_nNotesLen = CMembers::NOTES_LEN;
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

bool CMemberDlg::OnOk()
{
	// At least the surname supplied?
	if ( (m_ebSurname.TextLength() == 0) && (m_ebForename.TextLength() == 0) )
	{
		AlertMsg("You must provide either the Forename or Surname");
		return false;
	}

	CMembers& oTable = static_cast<CMembers&>(m_oMember.Table());

	// Find members with the same name but different ID.
	CResultSet oRS = oTable.Select(CWhereEqual(CMembers::FORENAME,  m_ebForename.Text())
								   & CWhereEqual(CMembers::SURNAME, m_ebSurname.Text())
								   & CWhereNotEqual(CMembers::ID,   m_oMember[CMembers::ID]));

	// Member already exists?
	if (oRS.Size() > 0)
	{
		AlertMsg("A member with that name already exists");
		return false;
	}

	m_oMember[CMembers::SURNAME]         = m_ebSurname.Text();
	m_oMember[CMembers::FORENAME]        = m_ebForename.Text();
	m_oMember[CMembers::STANDARD_PHONE]  = m_ebStdPhone.Text();
	m_oMember[CMembers::ALTERNATE_PHONE] = m_ebAltPhone.Text();
	m_oMember[CMembers::EMAIL_ADDRESS]   = m_ebEmailAddr.Text();
	m_oMember[CMembers::POSTAL_ADDRESS]  = m_ebPostalAddr.Text();
	m_oMember[CMembers::IS_REGISTERED]   = m_ckIsRegtrd.IsChecked();
	m_oMember[CMembers::IS_SENIOR]       = m_ckIsSenior.IsChecked();
	m_oMember[CMembers::USUAL_TEAM]      = m_cbTeam.CurSel();
	m_oMember[CMembers::USUAL_POSITION]  = m_cbPosition.CurSel();
	m_oMember[CMembers::NOTES]           = m_oNotesDlg.m_strNotes;

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

void CMemberDlg::OnNotes()
{
	m_oNotesDlg.RunModal(*this);
}
