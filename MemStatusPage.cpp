/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		MEMSTATUSPAGE.CPP
** COMPONENT:	The Application.
** DESCRIPTION:	CMemStatusPage class definition.
**
*******************************************************************************
*/

#include "AppHeaders.hpp"
#include "MemStatusPage.hpp"

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

CMemStatusPage::CMemStatusPage(CRow& oRow)
	: CPropertyPage(IDD_MEMSTATUS_PAGE)
	, m_oRow(oRow)
	, m_bIsRegistered(oRow[CMembers::IS_REGISTERED])
	, m_bIsSenior    (oRow[CMembers::IS_SENIOR])
	, m_nTeam        (oRow[CMembers::USUAL_TEAM])
	, m_nPosition    (oRow[CMembers::USUAL_POSITION])
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

void CMemStatusPage::OnInitDialog()
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

bool CMemStatusPage::OnValidate()
{
	m_bIsRegistered = m_ckIsRegistered.IsChecked();
	m_bIsSenior     = m_ckIsSenior.IsChecked();
	m_nTeam         = m_cbTeam.CurSel();
	m_nPosition     = m_cbPosition.CurSel();

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

bool CMemStatusPage::OnOk()
{
	m_oRow[CMembers::IS_REGISTERED]   = m_bIsRegistered;
	m_oRow[CMembers::IS_SENIOR]       = m_bIsSenior;
	m_oRow[CMembers::USUAL_TEAM]      = m_nTeam;
	m_oRow[CMembers::USUAL_POSITION]  = m_nPosition;

	return true;
}
