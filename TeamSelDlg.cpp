/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		TEAMSELSDLG.CPP
** COMPONENT:	The Application.
** DESCRIPTION:	CTeamSelDlg class definition.
**
*******************************************************************************
*/

#include "AppHeaders.hpp"
#include "TeamSelDlg.hpp"

// List of teams.
static char* astrTeams[MAX_CLUB_TEAMS+1] =
{
	"Any", "1st Team", "2nd Team", "3rd Team"
};

// List of positions.
static char* astrPositions[MAX_POSITIONS+1] =
{
	"All", "Goalkeepers", "Defenders", "Midfielders", "Attackers"
};

// List of formations.
static char* astrFormations[MAX_FORMATIONS] =
{
	"4-4-2", "5-3-2"
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

CTeamSelDlg::CTeamSelDlg(CFCMDB& oDB, CRow& oRow, bool bEditing)
	: CDialog(IDD_TEAM_SELS)
	, m_oDB(oDB)
	, m_oRow(oRow)
	, m_bEditing(bEditing)
	, m_oPitch(oDB.m_oMembers)
	, m_nTeamFilter(0)
	, m_nPosFilter(0)
	, m_nFormation(0)
{
	m_oPitch.PreRegister();

	DEFINE_CTRL_TABLE
		CTRL(IDC_DATE,				&m_dtpDate)
		CTRL(IDC_OPPONENT,			&m_cbOpponent)
		CTRL(IDC_TEAM_FILTER,		&m_cbTeamFilter)
		CTRL(IDC_POSITION_FILTER,	&m_cbPosFilter)
		CTRL(IDC_PLAYER,			&m_lbPlayer)
		CTRL(IDC_FORMATION,			&m_cbFormation)
		CTRL(IDC_PITCH,				&m_oPitch)
	END_CTRL_TABLE

	DEFINE_GRAVITY_TABLE
		CTRLGRAV(IDC_TEAM_FILTER,     LEFT_EDGE,  TOP_EDGE,    LEFT_EDGE,  TOP_EDGE)
		CTRLGRAV(IDC_POSITION_FILTER, LEFT_EDGE,  TOP_EDGE,    LEFT_EDGE,  TOP_EDGE)
		CTRLGRAV(IDC_PLAYER,	      LEFT_EDGE,  TOP_EDGE,    LEFT_EDGE,  BOTTOM_EDGE)
		CTRLGRAV(IDC_FORMATION_LABEL, LEFT_EDGE,  BOTTOM_EDGE, LEFT_EDGE,  BOTTOM_EDGE)
		CTRLGRAV(IDC_FORMATION,       LEFT_EDGE,  BOTTOM_EDGE, LEFT_EDGE,  BOTTOM_EDGE)
		CTRLGRAV(IDC_PITCH,           LEFT_EDGE,  TOP_EDGE,    RIGHT_EDGE, BOTTOM_EDGE)
		CTRLGRAV(IDOK,                RIGHT_EDGE, TOP_EDGE,    RIGHT_EDGE, TOP_EDGE)
		CTRLGRAV(IDCANCEL,            RIGHT_EDGE, TOP_EDGE,    RIGHT_EDGE, TOP_EDGE)
		CTRLGRAV(IDC_NOTES,           RIGHT_EDGE, TOP_EDGE,    RIGHT_EDGE, TOP_EDGE)
	END_GRAVITY_TABLE

	DEFINE_CTRLMSG_TABLE
		CMD_CTRLMSG(IDC_TEAM_FILTER,     CBN_SELCHANGE, OnSelectTeamFilter)
		CMD_CTRLMSG(IDC_POSITION_FILTER, CBN_SELCHANGE, OnSelectPosFilter)
		CMD_CTRLMSG(IDC_PLAYER,          LBN_SELCHANGE, OnSelectPlayer)
		CMD_CTRLMSG(IDC_FORMATION,       CBN_SELCHANGE, OnSelectFormation)
		CMD_CTRLMSG(IDC_NOTES,           BN_CLICKED,	OnNotes)
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

void CTeamSelDlg::OnInitDialog()
{
	// Set the dialog title.
	Title((m_bEditing == true) ? "Edit Team Selection" : "Add A Team Selection");

	CSize dmDlg = App.m_dmTeamSelDlg;

	// Resize, if last size saved.
	if ( (dmDlg.cx > 0) && (dmDlg.cy > 0) )
	{
		CRect rcDlg = WindowRect();

		rcDlg.right  = rcDlg.left + dmDlg.cx + 1;
		rcDlg.bottom = rcDlg.top  + dmDlg.cy + 1;

		Move(rcDlg, false);
		Centre();
	}

	int i;

	// Fill the opponents combo.
	CTable& oOpponents = App.Doc()->m_oDB.m_oOpponents;

	for (i = 0; i < oOpponents.RowCount(); i++)
		m_cbOpponent.Add(oOpponents[i][COpponents::CLUB_NAME]);

	// Add teams to the filter.
	for (i = 0; i < MAX_CLUB_TEAMS+1; i++)
		m_cbTeamFilter.Add(astrTeams[i]);

	// Add positions to the filter.
	for (i = 0; i < MAX_POSITIONS+1; i++)
		m_cbPosFilter.Add(astrPositions[i]);

	// Add formations to the control.
	for (i = 0; i < MAX_FORMATIONS; i++)
		m_cbFormation.Add(astrFormations[i]);

	// Initialise the controls limits.
	m_dtpDate.Format("ddd' 'dd'/'MM'/'yyyy");
	m_cbOpponent.TextLimit(CTeamSels::OPPONENTS_LEN);

	// Initialise the fields.
	m_dtpDate.SetDate(CDate(m_oRow[CTeamSels::DATE]));

	// Locate or add opponents.
	const char* pszOpponents = m_oRow[CTeamSels::OPPONENTS];
	int         nOpponents   = m_cbOpponent.FindExact(pszOpponents);
	
	if (nOpponents == LB_ERR)
		nOpponents = m_cbOpponent.Add(pszOpponents);

	m_cbOpponent.CurSel(nOpponents);

	// Select the default filters and formation.
	m_cbTeamFilter.CurSel(m_nTeamFilter);
	m_cbPosFilter.CurSel(m_nPosFilter);
	m_cbFormation.CurSel(m_nFormation);

	// Fill the players listbox.
	RefreshPlayerList();

	// Initialise the notes dialog.
	m_oNotesDlg.m_strNotes  = m_oRow[CTeamSels::NOTES];
	m_oNotesDlg.m_nNotesLen = CTeamSels::NOTES_LEN;
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

bool CTeamSelDlg::OnOk()
{
	m_oRow[CTeamSels::DATE]      = m_dtpDate.GetDate();
	m_oRow[CTeamSels::OPPONENTS] = m_cbOpponent.Text();
	m_oRow[CTeamSels::NOTES]     = m_oNotesDlg.m_strNotes;

	// Save current dimensions.
	App.m_dmTeamSelDlg = WindowRect().Size();

	return true;
}

/******************************************************************************
** Method:		OnCancel()
**
** Description:	Save the current dimensions.
**
** Parameters:	None.
**
** Returns:		true or false.
**
*******************************************************************************
*/

bool CTeamSelDlg::OnCancel()
{
	// Save current dimensions.
	App.m_dmTeamSelDlg = WindowRect().Size();

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

void CTeamSelDlg::OnNotes()
{
	m_oNotesDlg.RunModal(*this);
}

/******************************************************************************
** Method:		OnSelectTeamFilter()
**
** Description:	The user has selected a team filter, Re-fill the players list.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CTeamSelDlg::OnSelectTeamFilter()
{
	// Get the new selection and re-list the players.
	m_nTeamFilter = m_cbTeamFilter.CurSel();
	RefreshPlayerList();
}

/******************************************************************************
** Method:		OnSelectPosFilter()
**
** Description:	The user has selected a position filter, Re-fill the players
**				list.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CTeamSelDlg::OnSelectPosFilter()
{
	// Get the new selection and re-list the players.
	m_nPosFilter = m_cbPosFilter.CurSel();
	RefreshPlayerList();
}

/******************************************************************************
** Method:		OnSelectPlayer()
**
** Description:	The user has selected a player. Place the player in the
**				position selected on the pitch.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CTeamSelDlg::OnSelectPlayer()
{
}

/******************************************************************************
** Method:		OnSelectFormation()
**
** Description:	The user has selected a formation. Redisplay the pitch with the
**				new formation.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CTeamSelDlg::OnSelectFormation()
{
	// Get the new selection.
	m_nFormation = m_cbFormation.CurSel();
	m_oPitch.SetFormation(static_cast<Formation>(m_nFormation));
}

/******************************************************************************
** Method:		RefreshPlayerList()
**
** Description:	Refeshes the list of players according the current filter.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CTeamSelDlg::RefreshPlayerList()
{
	// Clear current contents.
	m_lbPlayer.Reset();
	m_lbPlayer.Redraw(false);

	// Add members to the players listbox.
	for (int i = 0; i < m_oDB.m_oMembers.RowCount(); i++)
	{
		CRow& oRow  = m_oDB.m_oMembers[i];
		int   nTeam = oRow[CMembers::USUAL_TEAM];
		int   nPos  = oRow[CMembers::USUAL_POSITION];

		// Ignore, if not part of team filter.
		if ( (nTeam != m_nTeamFilter) && (m_nTeamFilter != 0) && (nTeam != 0) )
			continue;

		// Ignore, if not part of position filter.
		if ( (nPos != m_nPosFilter) && (m_nPosFilter != 0) && (nPos != 0) )
			continue;

		// Add it.
		int n = m_lbPlayer.Add(App.FormatName(oRow, CMembers::FORENAME, CMembers::SURNAME, true));
		m_lbPlayer.ItemPtr(n, &oRow);
	}

	// Redraw.
	m_lbPlayer.Redraw(true);
	m_lbPlayer.Invalidate();
}
