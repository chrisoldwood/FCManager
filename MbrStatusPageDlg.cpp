/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		MBRSTATUSPAGEDLG.CPP
** COMPONENT:	The Application.
** DESCRIPTION:	CMbrStatusPageDlg class definition.
**
*******************************************************************************
*/

#include "AppHeaders.hpp"
#include "MbrStatusPageDlg.hpp"

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

CMbrStatusPageDlg::CMbrStatusPageDlg()
	: CPropertyPageDlg(IDD_MBRSTATUS_PAGE)
{
	DEFINE_CTRL_TABLE
		CTRL(IDC_REGISTERED,	&m_ckIsRegistered)
		CTRL(IDC_SENIOR,		&m_ckIsSenior)
		CTRL(IDC_USUAL_TEAM,	&m_cbTeam)
		CTRL(IDC_USUAL_POS,		&m_cbPosition)
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

void CMbrStatusPageDlg::OnInitDialog()
{
	for (int i = 0; i < MAX_CLUB_TEAMS+1; i++)
		m_cbTeam.Add(astrTeams[i]);

	for (int j = 0; j < MAX_POSITIONS+1; j++)
		m_cbPosition.Add(astrPositions[j]);

	// Initialise the fields with data.
	m_ckIsRegistered.Check(m_bIsRegistered);
	m_ckIsSenior.Check(m_bIsSenior);
	m_cbTeam.CurSel(m_nTeam);
	m_cbPosition.CurSel(m_nPosition);
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

bool CMbrStatusPageDlg::OnOk()
{
	m_bIsRegistered = m_ckIsRegistered.IsChecked();
	m_bIsSenior     = m_ckIsSenior.IsChecked();
	m_nTeam         = m_cbTeam.CurSel();
	m_nPosition     = m_cbPosition.CurSel();

	return true;
}
