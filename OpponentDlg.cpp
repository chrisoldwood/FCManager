/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		OPPONENTDLG.CPP
** COMPONENT:	The Application.
** DESCRIPTION:	COpponentDlg class definition.
**
*******************************************************************************
*/

#include "AppHeaders.hpp"
#include "OpponentDlg.hpp"

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

COpponentDlg::COpponentDlg(CRow& oOpponent, bool bEditing) : CDialog(IDD_OPPONENT)
	, m_oOpponent(oOpponent)
	, m_bEditing(bEditing)
{
	DEFINE_CTRL_TABLE
		CTRL(IDC_CLUB_NAME,			&m_ebClubName)
		CTRL(IDC_GROUND,			&m_ebGround)
		CTRL(IDC_STD_COLOURS,		&m_ebStdColours)
		CTRL(IDC_ALT_COLOURS,		&m_ebAltColours)
		CTRL(IDC_SURNAME,			&m_ebSurname)
		CTRL(IDC_FORENAME,			&m_ebForename)
		CTRL(IDC_STD_PHONE,			&m_ebStdPhone)
		CTRL(IDC_ALT_PHONE,			&m_ebAltPhone)
		CTRL(IDC_EMAIL_ADDRESS,		&m_ebEmailAddr)
		CTRL(IDC_POSTAL_ADDRESS,	&m_ebPostalAddr)
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

void COpponentDlg::OnInitDialog()
{
	// Set the dialog title.
	Title((m_bEditing == true) ? "Edit Opponent Details" : "Add An Opponent");

	// Initialise the controls.
	m_ebClubName.TextLimit(COpponents::CLUB_NAME_LEN);
	m_ebGround.TextLimit(COpponents::GROUND_LEN);
	m_ebStdColours.TextLimit(COpponents::COLOURS_LEN);
	m_ebAltColours.TextLimit(COpponents::COLOURS_LEN);
	m_ebSurname.TextLimit(COpponents::SURNAME_LEN);
	m_ebForename.TextLimit(COpponents::FORENAME_LEN);
	m_ebStdPhone.TextLimit(COpponents::PHONE_LEN);
	m_ebAltPhone.TextLimit(COpponents::PHONE_LEN);
	m_ebEmailAddr.TextLimit(COpponents::EMAIL_LEN);
	m_ebPostalAddr.TextLimit(COpponents::POSTAL_LEN);

	// Initialise the fields with data.
	m_ebClubName.Text(m_oOpponent[COpponents::CLUB_NAME]);
	m_ebGround.Text(m_oOpponent[COpponents::GROUND]);
	m_ebStdColours.Text(m_oOpponent[COpponents::STANDARD_CLRS]);
	m_ebAltColours.Text(m_oOpponent[COpponents::ALTERNATE_CLRS]);
	m_ebSurname.Text(m_oOpponent[COpponents::SURNAME]);
	m_ebForename.Text(m_oOpponent[COpponents::FORENAME]);
	m_ebStdPhone.Text(m_oOpponent[COpponents::STANDARD_PHONE]);
	m_ebAltPhone.Text(m_oOpponent[COpponents::ALTERNATE_PHONE]);
	m_ebEmailAddr.Text(m_oOpponent[COpponents::EMAIL_ADDRESS]);
	m_ebPostalAddr.Text(m_oOpponent[COpponents::POSTAL_ADDRESS]);

	// Initialise the notes dialog.
	m_oNotesDlg.m_strNotes  = m_oOpponent[COpponents::NOTES];
	m_oNotesDlg.m_nNotesLen = COpponents::NOTES_LEN;
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

bool COpponentDlg::OnOk()
{
	// At least the surname supplied?
	if (m_ebClubName.TextLength() == 0)
	{
		AlertMsg("You must provide at least the Club Name");
		return false;
	}

	COpponents& oTable = static_cast<COpponents&>(m_oOpponent.Table());

	// Find clubs with the same name but different ID.
	CResultSet oRS = oTable.Select(CWhereEqual(COpponents::CLUB_NAME, m_ebClubName.Text())
								   & CWhereNotEqual(COpponents::ID,   m_oOpponent[COpponents::ID]));

	// Club already exists?
	if (oRS.Size() > 0)
	{
		AlertMsg("A club with that name already exists");
		return false;
	}

	m_oOpponent[COpponents::CLUB_NAME]       = m_ebClubName.Text();
	m_oOpponent[COpponents::GROUND]          = m_ebGround.Text();
	m_oOpponent[COpponents::STANDARD_CLRS]   = m_ebStdColours.Text();
	m_oOpponent[COpponents::ALTERNATE_CLRS]  = m_ebAltColours.Text();
	m_oOpponent[COpponents::SURNAME]         = m_ebSurname.Text();
	m_oOpponent[COpponents::FORENAME]        = m_ebForename.Text();
	m_oOpponent[COpponents::STANDARD_PHONE]  = m_ebStdPhone.Text();
	m_oOpponent[COpponents::ALTERNATE_PHONE] = m_ebAltPhone.Text();
	m_oOpponent[COpponents::EMAIL_ADDRESS]   = m_ebEmailAddr.Text();
	m_oOpponent[COpponents::POSTAL_ADDRESS]  = m_ebPostalAddr.Text();
	m_oOpponent[COpponents::NOTES]           = m_oNotesDlg.m_strNotes;

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

void COpponentDlg::OnNotes()
{
	m_oNotesDlg.RunModal(*this);
}
