/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		CLUBDETAILS.CPP
** COMPONENT:	The Application.
** DESCRIPTION:	CClubDetails class definition.
**
*******************************************************************************
*/

#include "Common.hpp"
#include "ClubDetails.hpp"
#include <WCL/Date.hpp>
#include <stdio.h>
#include <tchar.h>

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

CClubDetails::CClubDetails(CMDB& oDB)
	: CTable(oDB, TXT("ClubDetails"))
{
	// Create the table schema.
	AddColumn(TXT("Name"),   MDCT_FXDSTR, NAME_LEN,   CColumn::DEFAULTS);
	AddColumn(TXT("Season"), MDCT_FXDSTR, SEASON_LEN, CColumn::DEFAULTS);
	AddColumn(TXT("League"), MDCT_FXDSTR, LEAGUE_LEN, CColumn::DEFAULTS);

	// Add the single row.
	CRow& oRow = CreateRow();

	InsertRow(oRow, false);
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

CClubDetails::~CClubDetails()
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

CRow& CClubDetails::CreateRow()
{
	// Create current season.
	CDate tToday = CDate::Current();
	int   nYear  = (tToday.Month() > 6) ? tToday.Year() : (tToday.Year()-1);
	tchar szSeason[10];

	_sntprintf(szSeason, ARRAYSIZE(szSeason)-1, TXT("%04d/%02d"), nYear, ((nYear+1) % 10));

	// Create and initialise row.
	CRow& oRow = CTable::CreateRow();

	oRow[NAME]   = TXT("Your Club F.C.");
	oRow[SEASON] = szSeason;
	oRow[LEAGUE] = TXT("Your League");
	
	return oRow;
}
