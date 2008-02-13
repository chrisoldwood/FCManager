/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		MEMSTATUSPAGE.CPP
** COMPONENT:	The Application.
** DESCRIPTION:	CMemStatusPage class definition.
**
*******************************************************************************
*/

#include "Common.hpp"
#include "MemStatusPage.hpp"
#include "FCMDoc.hpp"

// List of teams.
static tchar* astrTeams[MAX_CLUB_TEAMS+1] =
{
	TXT("Any"), TXT("1st Team"), TXT("2nd Team"), TXT("3rd Team")
};

// List of positions.
static tchar* astrPositions[MAX_POSITIONS+1] =
{
	TXT("Any"), TXT("Goalkeeper"), TXT("Defender"), TXT("Midfielder"), TXT("Attacker")
};

// Unavailability reasons.
static tchar* astrReasons[MAX_REASONS] =
{
	TXT("(none)"), TXT("Injured"), TXT("On Holiday"), TXT("Transferred"), TXT("Resigned"), TXT("Uncontactable")
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
	, m_bIsAvailable (oRow[CMembers::IS_AVAILABLE])
	, m_nReason      (oRow[CMembers::UNAVAIL_REASON])
{
	DEFINE_CTRL_TABLE
		CTRL(IDC_REGISTERED,	&m_ckIsRegistered)
		CTRL(IDC_SENIOR,		&m_ckIsSenior)
		CTRL(IDC_USUAL_TEAM,	&m_cbTeam)
		CTRL(IDC_USUAL_POS,		&m_cbPosition)
		CTRL(IDC_AVAILABLE,		&m_ckIsAvailable)
		CTRL(IDC_REASON,		&m_cbReason)
	END_CTRL_TABLE

	DEFINE_CTRLMSG_TABLE
		CMD_CTRLMSG(IDC_AVAILABLE, BN_CLICKED, &CMemStatusPage::OnAvailable)
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

void CMemStatusPage::OnInitDialog()
{
	// Fill combos.
	for (int i = 0; i < MAX_CLUB_TEAMS+1; i++)
		m_cbTeam.Add(astrTeams[i]);

	for (int j = 0; j < MAX_POSITIONS+1; j++)
		m_cbPosition.Add(astrPositions[j]);

	for (int k = 0; k < MAX_REASONS; k++)
		m_cbReason.Add(astrReasons[k]);

	// Initialise the fields with data.
	m_ckIsRegistered.Check(m_bIsRegistered);
	m_ckIsSenior.Check(m_bIsSenior);
	m_cbTeam.CurSel(m_nTeam);
	m_cbPosition.CurSel(m_nPosition);
	m_ckIsAvailable.Check(m_bIsAvailable);
	m_cbReason.CurSel(m_nReason);

	// Initialise control state.
	m_cbReason.Enable(!m_bIsAvailable);
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
	m_bIsAvailable  = m_ckIsAvailable.IsChecked();
	m_nReason       = m_cbReason.CurSel();

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
	m_oRow[CMembers::IS_AVAILABLE]    = m_bIsAvailable;
	m_oRow[CMembers::UNAVAIL_REASON]  = (!m_bIsAvailable) ? m_nReason : NO_REASON;

	return true;
}

/******************************************************************************
** Method:		OnAvailable()
**
** Description:	The available checkbox has changed states.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CMemStatusPage::OnAvailable()
{
	bool bAvailable = m_ckIsAvailable.IsChecked();

	m_cbReason.Enable(!bAvailable);
	m_cbReason.CurSel(0U);
}
