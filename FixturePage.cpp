/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		FIXTUREPAGE.CPP
** COMPONENT:	The Application.
** DESCRIPTION:	CFixturePage class definition.
**
*******************************************************************************
*/

#include "Common.hpp"
#include "FixturePage.hpp"
#include "FCMApp.hpp"

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

CFixturePage::CFixturePage(CFCMDB& oDB, CRow& oRow)
	: CPropertyPage(IDD_FIXTURE_PAGE)
	, m_oDB(oDB)
	, m_oRow(oRow)
{
	DEFINE_CTRL_TABLE
		CTRL(IDC_DATE,		&m_dtpDate)
		CTRL(IDC_TYPE,		&m_cbType)
		CTRL(IDC_HOME_TEAM,	&m_cbHomeTeam)
		CTRL(IDC_AWAY_TEAM,	&m_cbAwayTeam)
		CTRL(IDC_REFEREE,	&m_cbReferee)
		CTRL(IDC_RESULT,	&m_ebResult)
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

void CFixturePage::OnInitDialog()
{
	// Fill the home & away team combos.
	CTable& oOpponents = App.Doc()->m_oDB.m_oOpponents;

	for (size_t i = 0; i < oOpponents.RowCount(); i++)
	{
		const tchar* pszTeam = oOpponents[i][COpponents::CLUB_NAME];

		m_cbHomeTeam.Add(pszTeam);
		m_cbAwayTeam.Add(pszTeam);
	}

	// Fill in the referee combo.
	CTable& oReferees = App.Doc()->m_oDB.m_oReferees;

	for (size_t i = 0; i < oReferees.RowCount(); i++)
	{
		CString strName;

		strName += oReferees[i][CReferees::FORENAME].GetString();
		strName += ' ';
		strName += oReferees[i][CReferees::SURNAME].GetString();

		m_cbReferee.Add(strName);
	}

	// Fill the match types combo.
	m_cbType.Add(TXT("League"));
	m_cbType.Add(TXT("Cup"));
	m_cbType.Add(TXT("Friendly"));

	// Initialise the controls limits.
	m_dtpDate.Format(TXT("ddd' 'dd'/'MM'/'yyyy"));
	m_cbHomeTeam.TextLimit(CFixtures::TEAM_LEN);
	m_cbAwayTeam.TextLimit(CFixtures::TEAM_LEN);
	m_cbReferee.TextLimit(CFixtures::NAME_LEN);
	m_ebResult.TextLimit(CFixtures::RESULT_LEN);

	// Initialise the fields.
	m_dtpDate.SetDate(CDate(m_oRow[CFixtures::DATE]));
	m_ebResult.Text(m_oRow[CFixtures::RESULT]);

	// Locate or add type.
	const tchar* pszType = m_oRow[CFixtures::TYPE];
	int          nType   = m_cbType.FindExact(pszType);
	
	if (nType == LB_ERR)
		nType = m_cbType.Add(pszType);

	m_cbType.CurSel(nType);

	// Locate or add home team.
	const tchar* pszHomeTeam = m_oRow[CFixtures::HOME_TEAM];
	int          nHomeTeam   = m_cbHomeTeam.FindExact(pszHomeTeam);
	
	if (nHomeTeam == LB_ERR)
		nHomeTeam = m_cbHomeTeam.Add(pszHomeTeam);

	m_cbHomeTeam.CurSel(nHomeTeam);

	// Locate or add away team.
	const tchar* pszAwayTeam = m_oRow[CFixtures::AWAY_TEAM];
	int          nAwayTeam   = m_cbAwayTeam.FindExact(pszAwayTeam);
	
	if (nAwayTeam == LB_ERR)
		nAwayTeam = m_cbAwayTeam.Add(pszAwayTeam);

	m_cbAwayTeam.CurSel(nAwayTeam);

	// Locate or add referee.
	const tchar* pszReferee = m_oRow[CFixtures::REFEREE];
	int          nReferee   = m_cbReferee.FindExact(pszReferee);
	
	if (nReferee == LB_ERR)
		nReferee = m_cbReferee.Add(pszReferee);

	m_cbReferee.CurSel(nReferee);
}

/******************************************************************************
** Method:		OnOk()
**
** Description:	Save the data.
**
** Parameters:	None.
**
** Returns:		true or false.
**
*******************************************************************************
*/

bool CFixturePage::OnOk()
{
	m_oRow[CFixtures::DATE]      = m_dtpDate.GetDate().GetDateInSecs();
	m_oRow[CFixtures::TYPE]      = m_cbType.Text();
	m_oRow[CFixtures::HOME_TEAM] = m_cbHomeTeam.Text();
	m_oRow[CFixtures::AWAY_TEAM] = m_cbAwayTeam.Text();
	m_oRow[CFixtures::REFEREE]   = m_cbReferee.Text();
	m_oRow[CFixtures::RESULT]    = m_ebResult.Text();

	return true;
}
