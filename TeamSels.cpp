/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		TEAMSELS.CPP
** COMPONENT:	The Application.
** DESCRIPTION:	CTeamSels class definition.
**
*******************************************************************************
*/

#include "AppHeaders.hpp"

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

CTeamSels::CTeamSels(CMDB& oDB, CMembers& oMembers)
	: CTable(oDB, "TeamSels")
{
	// Create the table schema.
	AddColumn("ID",        MDCT_IDENTITY, 0,             CColumn::IDENTITY);
	AddColumn("Date",      MDCT_DATETIME, 0,             CColumn::DEFAULTS);
	AddColumn("Opponents", MDCT_FXDSTR,   OPPONENTS_LEN, CColumn::DEFAULTS);
	AddColumn("Player1",   oMembers,      CMembers::ID,  CColumn::FOREIGN_KEY | CColumn::NULLABLE);
	AddColumn("Player2",   oMembers,      CMembers::ID,  CColumn::FOREIGN_KEY | CColumn::NULLABLE);
	AddColumn("Player3",   oMembers,      CMembers::ID,  CColumn::FOREIGN_KEY | CColumn::NULLABLE);
	AddColumn("Player4",   oMembers,      CMembers::ID,  CColumn::FOREIGN_KEY | CColumn::NULLABLE);
	AddColumn("Player5",   oMembers,      CMembers::ID,  CColumn::FOREIGN_KEY | CColumn::NULLABLE);
	AddColumn("Player6",   oMembers,      CMembers::ID,  CColumn::FOREIGN_KEY | CColumn::NULLABLE);
	AddColumn("Player7",   oMembers,      CMembers::ID,  CColumn::FOREIGN_KEY | CColumn::NULLABLE);
	AddColumn("Player8",   oMembers,      CMembers::ID,  CColumn::FOREIGN_KEY | CColumn::NULLABLE);
	AddColumn("Player9",   oMembers,      CMembers::ID,  CColumn::FOREIGN_KEY | CColumn::NULLABLE);
	AddColumn("Player10",  oMembers,      CMembers::ID,  CColumn::FOREIGN_KEY | CColumn::NULLABLE);
	AddColumn("Player11",  oMembers,      CMembers::ID,  CColumn::FOREIGN_KEY | CColumn::NULLABLE);
	AddColumn("Subs1",     oMembers,      CMembers::ID,  CColumn::FOREIGN_KEY | CColumn::NULLABLE);
	AddColumn("Subs2",     oMembers,      CMembers::ID,  CColumn::FOREIGN_KEY | CColumn::NULLABLE);
	AddColumn("Subs3",     oMembers,      CMembers::ID,  CColumn::FOREIGN_KEY | CColumn::NULLABLE);
	AddColumn("Subs4",     oMembers,      CMembers::ID,  CColumn::FOREIGN_KEY | CColumn::NULLABLE);
	AddColumn("Subs5",     oMembers,      CMembers::ID,  CColumn::FOREIGN_KEY | CColumn::NULLABLE);
	AddColumn("Notes",     MDCT_VARSTR,   NOTES_LEN,     CColumn::DEFAULTS);
}

/******************************************************************************
** Method:		Destructor.
**
** Description:	.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

CTeamSels::~CTeamSels()
{
}

/******************************************************************************
** Method:		CreateRow()
**
** Description:	Creates a new row and initialises it.
**
** Parameters:	None.
**
** Returns:		The new row.
**
*******************************************************************************
*/

CRow& CTeamSels::CreateRow()
{
	CRow& oRow = CTable::CreateRow();

//	oRow[ID]        = 0;
	oRow[DATE]      = time(NULL);
	oRow[OPPONENTS] = "";
	oRow[PLAYER_1]  = null;
	oRow[PLAYER_2]  = null;
	oRow[PLAYER_3]  = null;
	oRow[PLAYER_4]  = null;
	oRow[PLAYER_5]  = null;
	oRow[PLAYER_6]  = null;
	oRow[PLAYER_7]  = null;
	oRow[PLAYER_8]  = null;
	oRow[PLAYER_9]  = null;
	oRow[PLAYER_10] = null;
	oRow[PLAYER_11] = null;
	oRow[SUB_1]     = null;
	oRow[SUB_2]     = null;
	oRow[SUB_3]     = null;
	oRow[SUB_4]     = null;
	oRow[SUB_5]     = null;
	oRow[NOTES]     = "";
	
	return oRow;
}
