/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		STATS.CPP
** COMPONENT:	The Application.
** DESCRIPTION:	CStats class definition.
**
*******************************************************************************
*/

#include "Common.hpp"
#include "Stats.hpp"
#include "StatTypes.hpp"
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

CStats::CStats(const tchar* pszName, CStatTypes& oTypes)
	: CTable(pszName)
{
	// Create the table schema.
	AddColumn(TXT("OwnerID"), MDCT_INT,    0,              CColumn::DEFAULTS   );
	AddColumn(TXT("Date"),    MDCT_DATE,   0,              CColumn::DEFAULTS   );
	AddColumn(TXT("TypeID"),  oTypes,      CStatTypes::ID, CColumn::FOREIGN_KEY);
	AddColumn(TXT("Value"),   MDCT_DOUBLE, 0,              CColumn::DEFAULTS   );
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
