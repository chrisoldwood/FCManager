/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		FIXTUREDLG.CPP
** COMPONENT:	The Application.
** DESCRIPTION:	CFixtureDlg class definition.
**
*******************************************************************************
*/

#include "AppHeaders.hpp"
#include "FixtureDlg.hpp"

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

CFixtureDlg::CFixtureDlg(CRow& oFixture, bool bEditing) : CDialog(IDD_FIXTURE)
	, m_oFixture(oFixture)
	, m_bEditing(bEditing)
{
	DEFINE_CTRL_TABLE
		CTRL(IDC_DATE,		&m_dtpDate)
		CTRL(IDC_TYPE,		&m_cbType)
		CTRL(IDC_HOME_TEAM,	&m_cbHomeTeam)
		CTRL(IDC_AWAY_TEAM,	&m_cbAwayTeam)
		CTRL(IDC_REFEREE,	&m_cbReferee)
		CTRL(IDC_RESULT,	&m_ebResult)
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

void CFixtureDlg::OnInitDialog()
{
	// Set the dialog title.
	Title((m_bEditing == true) ? "Edit Fixture Details" : "Add A Fixture");

	int i;

	// Fill the home & away team combos.
	CTable& oOpponents = App.Doc()->m_oDB[CFCMDB::OPPONENTS];

	for (i = 0; i < oOpponents.RowCount(); i++)
	{
		const char* pszTeam = oOpponents[i][COpponents::CLUB_NAME];

		m_cbHomeTeam.Add(pszTeam);
		m_cbAwayTeam.Add(pszTeam);
	}

	// Fill in the referee combo.
	CTable& oReferees = App.Doc()->m_oDB[CFCMDB::REFEREES];

	for (i = 0; i < oReferees.RowCount(); i++)
	{
		CString strName;

		strName += oReferees[i][CReferees::FORENAME].GetString();
		strName += ' ';
		strName += oReferees[i][CReferees::SURNAME].GetString();

		m_cbReferee.Add(strName);
	}

	// Fill the match types combo.
	m_cbType.Add("League");
	m_cbType.Add("Cup");
	m_cbType.Add("Friendly");

	// Initialise the controls limits.
	m_dtpDate.Format("ddd' 'dd'/'MM'/'yyyy");
	m_cbHomeTeam.TextLimit(CFixtures::TEAM_LEN);
	m_cbAwayTeam.TextLimit(CFixtures::TEAM_LEN);
	m_cbReferee.TextLimit(CFixtures::NAME_LEN);
	m_ebResult.TextLimit(CFixtures::RESULT_LEN);

	// Initialise the fields.
	m_dtpDate.SetDate(m_oFixture[CFixtures::DATE]);
	m_ebResult.Text(m_oFixture[CFixtures::RESULT]);

	// Locate or add type.
	const char* pszType = m_oFixture[CFixtures::TYPE];
	int         nType   = m_cbType.FindExact(pszType);
	
	if (nType == LB_ERR)
		nType = m_cbType.Add(pszType);

	m_cbType.CurSel(nType);

	// Locate or add home team.
	const char* pszHomeTeam = m_oFixture[CFixtures::HOME_TEAM];
	int         nHomeTeam   = m_cbHomeTeam.FindExact(pszHomeTeam);
	
	if (nHomeTeam == LB_ERR)
		nHomeTeam = m_cbHomeTeam.Add(pszHomeTeam);

	m_cbHomeTeam.CurSel(nHomeTeam);

	// Locate or add away team.
	const char* pszAwayTeam = m_oFixture[CFixtures::AWAY_TEAM];
	int         nAwayTeam   = m_cbAwayTeam.FindExact(pszAwayTeam);
	
	if (nAwayTeam == LB_ERR)
		nAwayTeam = m_cbAwayTeam.Add(pszAwayTeam);

	m_cbAwayTeam.CurSel(nAwayTeam);

	// Locate or add referee.
	const char* pszReferee = m_oFixture[CFixtures::REFEREE];
	int         nReferee   = m_cbReferee.FindExact(pszReferee);
	
	if (nReferee == LB_ERR)
		nReferee = m_cbReferee.Add(pszReferee);

	m_cbReferee.CurSel(nReferee);

	// Initialise the notes dialog.
	m_oNotesDlg.m_strNotes  = m_oFixture[CFixtures::NOTES];
	m_oNotesDlg.m_nNotesLen = CFixtures::NOTES_LEN;
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

bool CFixtureDlg::OnOk()
{
	m_oFixture[CFixtures::DATE]      = m_dtpDate.GetDate();
	m_oFixture[CFixtures::TYPE]      = m_cbType.Text();
	m_oFixture[CFixtures::HOME_TEAM] = m_cbHomeTeam.Text();
	m_oFixture[CFixtures::AWAY_TEAM] = m_cbAwayTeam.Text();
	m_oFixture[CFixtures::REFEREE]   = m_cbReferee.Text();
	m_oFixture[CFixtures::RESULT]    = m_ebResult.Text();
	m_oFixture[CFixtures::NOTES]     = m_oNotesDlg.m_strNotes;

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

void CFixtureDlg::OnNotes()
{
	m_oNotesDlg.RunModal(*this);
}
