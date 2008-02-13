/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		STATTYPES.CPP
** COMPONENT:	The Application.
** DESCRIPTION:	CStatTypes class definition.
**
*******************************************************************************
*/

#include "Common.hpp"
#include "StatTypes.hpp"

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

CStatTypes::CStatTypes(CMDB& oDB, const tchar* pszName)
	: CTable(oDB, pszName)
{
	// Create the table schema.
	AddColumn(TXT("ID"),    MDCT_IDENTITY, 0,        CColumn::IDENTITY);
	AddColumn(TXT("Name"),  MDCT_FXDSTR,   NAME_LEN, CColumn::DEFAULTS);
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

CStatTypes::~CStatTypes()
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

CRow& CStatTypes::CreateRow()
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

void CStatTypes::AddPredefined(const tchar* pszName)
{
	CRow& oRow = CreateRow();

	oRow[NAME]  = pszName;

	InsertRow(oRow, false);
}
