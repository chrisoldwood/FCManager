/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		STATS.CPP
** COMPONENT:	The Application.
** DESCRIPTION:	CStats class definition.
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

CStats::CStats(CMDB& oDB, const char* pszName, CStatTypes& oTypes)
	: CTable(oDB, pszName)
{
	// Create the table schema.
	AddColumn("OwnerID", MDCT_INT,    0,              CColumn::DEFAULTS   );
	AddColumn("Date",    MDCT_DATE,   0,              CColumn::DEFAULTS   );
	AddColumn("TypeID",  oTypes,      CStatTypes::ID, CColumn::FOREIGN_KEY);
	AddColumn("Value",   MDCT_DOUBLE, 0,              CColumn::DEFAULTS   );
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

CStats::~CStats()
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

CRow& CStats::CreateRow()
{
	CRow& oRow = CTable::CreateRow();

	oRow[OWNER_ID] = 0;
	oRow[DATE]     = time(NULL);
//	oRow[TYPE_ID]  = 0;
	oRow[VALUE]    = 0.0;
	
	return oRow;
}
