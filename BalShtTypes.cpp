/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		BALSHTTYPES.CPP
** COMPONENT:	The Application.
** DESCRIPTION:	CBalShtTypes class definition.
**
*******************************************************************************
*/

#include "Common.hpp"
#include "BalShtTypes.hpp"

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

CBalShtTypes::CBalShtTypes(CMDB& oDB)
	: CTable(oDB, TXT("BalanceSheetItemTypes"))
{
	// Create the table schema.
	AddColumn(TXT("ID"),    MDCT_IDENTITY, 0,        CColumn::IDENTITY);
	AddColumn(TXT("Name"),  MDCT_FXDSTR,   NAME_LEN, CColumn::DEFAULTS);

	// Add the predfined types.
	AddPredefined(TXT("Other"));
	AddPredefined(TXT("Match"));
	AddPredefined(TXT("Training"));
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

CBalShtTypes::~CBalShtTypes()
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

CRow& CBalShtTypes::CreateRow()
{
	CRow& oRow = CTable::CreateRow();

//	oRow[ID]    = 0;
	oRow[NAME]  = TXT("");
	
	return oRow;
}

/******************************************************************************
** Method:		AddPredefined()
**
** Description:	Internal method to add a predefined statistic type.
**
** Parameters:	pszName	The name of the statistic.
**
** Returns:		The new row.
**
*******************************************************************************
*/

void CBalShtTypes::AddPredefined(const tchar* pszName)
{
	CRow& oRow = CreateRow();

	oRow[NAME]  = pszName;

	InsertRow(oRow, false);
}
