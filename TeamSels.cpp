/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		TEAMSELS.CPP
** COMPONENT:	The Application.
** DESCRIPTION:	CTeamSels class definition.
**
*******************************************************************************
*/

#include "Common.hpp"
#include "TeamSels.hpp"
#include "Members.hpp"
#include <time.h>

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
	: CTable(oDB, TXT("TeamSels"))
{
	// Create the table schema.
	AddColumn(TXT("ID"),        MDCT_IDENTITY, 0,             CColumn::IDENTITY);
	AddColumn(TXT("Date"),      MDCT_DATETIME, 0,             CColumn::DEFAULTS);
	AddColumn(TXT("Opponents"), MDCT_FXDSTR,   OPPONENTS_LEN, CColumn::DEFAULTS);
	AddColumn(TXT("Player1"),   oMembers,      CMembers::ID,  CColumn::FOREIGN_KEY | CColumn::NULLABLE);
	AddColumn(TXT("Player2"),   oMembers,      CMembers::ID,  CColumn::FOREIGN_KEY | CColumn::NULLABLE);
	AddColumn(TXT("Player3"),   oMembers,      CMembers::ID,  CColumn::FOREIGN_KEY | CColumn::NULLABLE);
	AddColumn(TXT("Player4"),   oMembers,      CMembers::ID,  CColumn::FOREIGN_KEY | CColumn::NULLABLE);
	AddColumn(TXT("Player5"),   oMembers,      CMembers::ID,  CColumn::FOREIGN_KEY | CColumn::NULLABLE);
	AddColumn(TXT("Player6"),   oMembers,      CMembers::ID,  CColumn::FOREIGN_KEY | CColumn::NULLABLE);
	AddColumn(TXT("Player7"),   oMembers,      CMembers::ID,  CColumn::FOREIGN_KEY | CColumn::NULLABLE);
	AddColumn(TXT("Player8"),   oMembers,      CMembers::ID,  CColumn::FOREIGN_KEY | CColumn::NULLABLE);
	AddColumn(TXT("Player9"),   oMembers,      CMembers::ID,  CColumn::FOREIGN_KEY | CColumn::NULLABLE);
	AddColumn(TXT("Player10"),  oMembers,      CMembers::ID,  CColumn::FOREIGN_KEY | CColumn::NULLABLE);
	AddColumn(TXT("Player11"),  oMembers,      CMembers::ID,  CColumn::FOREIGN_KEY | CColumn::NULLABLE);
	AddColumn(TXT("Subs1"),     oMembers,      CMembers::ID,  CColumn::FOREIGN_KEY | CColumn::NULLABLE);
	AddColumn(TXT("Subs2"),     oMembers,      CMembers::ID,  CColumn::FOREIGN_KEY | CColumn::NULLABLE);
	AddColumn(TXT("Subs3"),     oMembers,      CMembers::ID,  CColumn::FOREIGN_KEY | CColumn::NULLABLE);
	AddColumn(TXT("Subs4"),     oMembers,      CMembers::ID,  CColumn::FOREIGN_KEY | CColumn::NULLABLE);
	AddColumn(TXT("Subs5"),     oMembers,      CMembers::ID,  CColumn::FOREIGN_KEY | CColumn::NULLABLE);
	AddColumn(TXT("Notes"),     MDCT_VARSTR,   NOTES_LEN,     CColumn::DEFAULTS);
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
	oRow[OPPONENTS] = TXT("");
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
	oRow[NOTES]     = TXT("");
	
	return oRow;
}
