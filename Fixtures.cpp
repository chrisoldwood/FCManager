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
	AddColumn("ID",            MDCT_IDENTITY,	0,          CColumn::IDENTITY);		// ID
	AddColumn("Date",          MDCT_DATETIME,	0,          CColumn::DEFAULTS);		// DATE
	AddColumn("Type",          MDCT_FXDSTR,		TYPE_LEN,   CColumn::DEFAULTS);		// TYPE
	AddColumn("HomeTeam",      MDCT_FXDSTR,		TEAM_LEN,   CColumn::DEFAULTS);		// HOME_TEAM
	AddColumn("AwayTeam",      MDCT_FXDSTR,		TEAM_LEN,   CColumn::DEFAULTS);		// AWAY_TEAM
	AddColumn("Referee",       MDCT_FXDSTR,		NAME_LEN,   CColumn::DEFAULTS);		// REFEREE
	AddColumn("Result",        MDCT_FXDSTR,		RESULT_LEN, CColumn::DEFAULTS);		// RESULT
	AddColumn("PitchCfmd",     MDCT_BOOL,		0,          CColumn::DEFAULTS);		// PITCH_CFMD
	AddColumn("OpponentsCfmd", MDCT_BOOL,		0,          CColumn::DEFAULTS);		// OPPONENTS_CFMD
	AddColumn("RefereeCfmd",   MDCT_BOOL,		0,          CColumn::DEFAULTS);		// REFEREE_CFMD
	AddColumn("Notes",         MDCT_VARSTR,		NOTES_LEN,  CColumn::DEFAULTS);		// NOTES

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
