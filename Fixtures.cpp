/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		FIXTURES.CPP
** COMPONENT:	The Application.
** DESCRIPTION:	CFixtures class definition.
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

CFixtures::CFixtures(CMDB& oDB)
	: CTable(oDB, "Fixtures")
{
	// Create the table schema.
	AddColumn("ID",            MDT_IDENTITY,	0);				// ID
	AddColumn("Date",          MDT_DATE,		0);				// DATE
	AddColumn("Type",          MDT_FXDSTR,		TYPE_LEN);		// TYPE
	AddColumn("HomeTeam",      MDT_FXDSTR,		TEAM_LEN);		// HOME_TEAM
	AddColumn("AwayTeam",      MDT_FXDSTR,		TEAM_LEN);		// AWAY_TEAM
	AddColumn("Referee",       MDT_FXDSTR,		NAME_LEN);		// REFEREE
	AddColumn("Result",        MDT_FXDSTR,		RESULT_LEN);	// RESULT
	AddColumn("PitchCfmd",     MDT_BOOL,		0);				// PITCH_CFMD
	AddColumn("OpponentsCfmd", MDT_BOOL,		0);				// OPPONENTS_CFMD
	AddColumn("RefereeCfmd",   MDT_BOOL,		0);				// REFEREE_CFMD
	AddColumn("Notes",         MDT_FXDSTR,		NOTES_LEN);		// NOTES

	// Add the indexes.
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

CFixtures::~CFixtures()
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

CRow& CFixtures::CreateRow()
{
	CRow& oRow = CTable::CreateRow();

//	oRow[ID            ] = 0;
	oRow[DATE          ] = CDate::Current();
	oRow[TYPE          ] = "";
	oRow[HOME_TEAM     ] = "";
	oRow[AWAY_TEAM     ] = "";
	oRow[REFEREE       ] = "";
	oRow[RESULT        ] = "";
	oRow[PITCH_CFMD    ] = false;
	oRow[OPPONENTS_CFMD] = false;
	oRow[REFEREE_CFMD  ] = false;
	oRow[NOTES         ] = "";
	
	return oRow;
}
