/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		OPPONENTPAGE.CPP
** COMPONENT:	The Application.
** DESCRIPTION:	COpponentPage class definition.
**
*******************************************************************************
*/

#include "Common.hpp"
#include "OpponentPage.hpp"
#include "Opponents.hpp"
#include <MDBL/ResultSet.hpp>
#include <MDBL/WhereCmp.hpp>
#include <MDBL/WhereExp.hpp>

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

COpponentPage::COpponentPage(CRow& oRow)
	: CPropertyPage(IDD_OPPONENT_PAGE)
	, m_oRow(oRow)
	, m_strClubName  (oRow[COpponents::CLUB_NAME])
	, m_strGround    (oRow[COpponents::GROUND])
	, m_strStdColours(oRow[COpponents::STANDARD_CLRS])
	, m_strAltColours(oRow[COpponents::ALTERNATE_CLRS])
{
	DEFINE_CTRL_TABLE
		CTRL(IDC_CLUB_NAME,			&m_ebClubName)
		CTRL(IDC_GROUND,			&m_ebGround)
		CTRL(IDC_STD_COLOURS,		&m_ebStdColours)
		CTRL(IDC_ALT_COLOURS,		&m_ebAltColours)
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

void COpponentPage::OnInitDialog()
{
	// Initialise the controls.
	m_ebClubName.TextLimit  (COpponents::CLUB_NAME_LEN);
	m_ebGround.TextLimit    (COpponents::GROUND_LEN);
	m_ebStdColours.TextLimit(COpponents::COLOURS_LEN);
	m_ebAltColours.TextLimit(COpponents::COLOURS_LEN);

	// Initialise the fields with data.
	m_ebClubName.Text  (m_strClubName);
	m_ebGround.Text    (m_strGround);
	m_ebStdColours.Text(m_strStdColours);
	m_ebAltColours.Text(m_strAltColours);
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

bool COpponentPage::OnValidate()
{
	m_strClubName   = m_ebClubName.Text();
	m_strGround     = m_ebGround.Text();
	m_strStdColours = m_ebStdColours.Text();
	m_strAltColours = m_ebAltColours.Text();

	// At least the club name supplied?
	if (m_ebClubName.TextLength() == 0)
	{
		AlertMsg("You must provide at least the Club Name");
		return false;
	}

	COpponents& oTable = static_cast<COpponents&>(m_oRow.Table());

	// Find clubs with the same name but different ID.
	CResultSet oRS = oTable.Select(CWhereCmp(COpponents::CLUB_NAME, CWhereCmp::EQUALS,     m_ebClubName.Text())
								&& CWhereCmp(COpponents::ID,        CWhereCmp::NOT_EQUALS, m_oRow[COpponents::ID]));

	// Club already exists?
	if (oRS.Count() > 0)
	{
		AlertMsg("A club with that name already exists");
		return false;
	}

	return true;
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

bool COpponentPage::OnOk()
{
	m_oRow[COpponents::CLUB_NAME]       = m_strClubName;
	m_oRow[COpponents::GROUND]          = m_strGround;
	m_oRow[COpponents::STANDARD_CLRS]   = m_strStdColours;
	m_oRow[COpponents::ALTERNATE_CLRS]  = m_strAltColours;

	return true;
}
