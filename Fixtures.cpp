/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		FIXTURES.CPP
** COMPONENT:	The Application.
** DESCRIPTION:	CFixtures class definition.
**
*******************************************************************************
*/

#include "Common.hpp"
#include "Fixtures.hpp"
#include <WCL/Date.hpp>

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
	: CTable(oDB, TXT("Fixtures"))
{
	// Create the table schema.
	AddColumn(TXT("ID"),            MDCT_IDENTITY,	0,          CColumn::IDENTITY);		// ID
	AddColumn(TXT("Date"),          MDCT_DATETIME,	0,          CColumn::DEFAULTS);		// DATE
	AddColumn(TXT("Type"),          MDCT_FXDSTR,		TYPE_LEN,   CColumn::DEFAULTS);		// TYPE
	AddColumn(TXT("HomeTeam"),      MDCT_FXDSTR,		TEAM_LEN,   CColumn::DEFAULTS);		// HOME_TEAM
	AddColumn(TXT("AwayTeam"),      MDCT_FXDSTR,		TEAM_LEN,   CColumn::DEFAULTS);		// AWAY_TEAM
	AddColumn(TXT("Referee"),       MDCT_FXDSTR,		NAME_LEN,   CColumn::DEFAULTS);		// REFEREE
	AddColumn(TXT("Result"),        MDCT_FXDSTR,		RESULT_LEN, CColumn::DEFAULTS);		// RESULT
	AddColumn(TXT("PitchCfmd"),     MDCT_BOOL,		0,          CColumn::DEFAULTS);		// PITCH_CFMD
	AddColumn(TXT("OpponentsCfmd"), MDCT_BOOL,		0,          CColumn::DEFAULTS);		// OPPONENTS_CFMD
	AddColumn(TXT("RefereeCfmd"),   MDCT_BOOL,		0,          CColumn::DEFAULTS);		// REFEREE_CFMD
	AddColumn(TXT("Notes"),         MDCT_VARSTR,		NOTES_LEN,  CColumn::DEFAULTS);		// NOTES

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
	oRow[DATE          ] = CDate::Current().GetDateInSecs();
	oRow[TYPE          ] = TXT("");
	oRow[HOME_TEAM     ] = TXT("");
	oRow[AWAY_TEAM     ] = TXT("");
	oRow[REFEREE       ] = TXT("");
	oRow[RESULT        ] = TXT("");
	oRow[PITCH_CFMD    ] = false;
	oRow[OPPONENTS_CFMD] = false;
	oRow[REFEREE_CFMD  ] = false;
	oRow[NOTES         ] = TXT("");
	
	return oRow;
}
