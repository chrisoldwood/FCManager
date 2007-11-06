/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		TMPSTATS.CPP
** COMPONENT:	The Application.
** DESCRIPTION:	CTmpStats class definition.
**
*******************************************************************************
*/

#include "Common.hpp"
#include "TmpStats.hpp"
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

CTmpStats::CTmpStats(CMDB& oDB, CStatTypes& oTypes)
	: CTable(oDB, "#TmpStats")
{
	// Create the table schema.
	AddColumn("OwnerID", MDCT_INT,    0,              CColumn::DEFAULTS   );
	AddColumn("Date",    MDCT_DATE,   0,              CColumn::DEFAULTS   );
	AddColumn("TypeID",  oTypes,      CStatTypes::ID, CColumn::FOREIGN_KEY);
	AddColumn("Value",   MDCT_DOUBLE, 0,              CColumn::DEFAULTS   );
	AddColumn("Name",    MDCT_FXDSTR, NAME_LEN,       CColumn::DEFAULTS   );
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

CTmpStats::~CTmpStats()
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

CRow& CTmpStats::CreateRow()
{
	CRow& oRow = CTable::CreateRow();

//	oRow[OWNER_ID] = 0;
	oRow[DATE]     = time(NULL);
//	oRow[TYPE_ID]  = 0;
	oRow[VALUE]    = 0.0;
	oRow[NAME]     = "";
	
	return oRow;
}
