/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		TMPEXPS.CPP
** COMPONENT:	The Application.
** DESCRIPTION:	CTmpExps class definition.
**
*******************************************************************************
*/

#include "Common.hpp"
#include "TmpExps.hpp"
#include "ExpenseTypes.hpp"
#include "BalSheet.hpp"

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

CTmpExps::CTmpExps(CMDB& oDB, CExpenseTypes& oTypes)
	: CTable(oDB, "#TmpExps")
{
	// Create the table schema.
	AddColumn("ItemID",   MDCT_INT,    0,                   CColumn::DEFAULTS   );
	AddColumn("TypeID",   oTypes,      CExpenseTypes::ID,   CColumn::FOREIGN_KEY);
	AddColumn("Paid",     MDCT_INT,    0,                   CColumn::DEFAULTS   );
	AddColumn("ItemDate", MDCT_DATE,   0,                   CColumn::DEFAULTS | CColumn::NULLABLE);
	AddColumn("ItemName", MDCT_FXDSTR, CBalSheet::NAME_LEN, CColumn::DEFAULTS | CColumn::NULLABLE);
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

CTmpExps::~CTmpExps()
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

CRow& CTmpExps::CreateRow()
{
	CRow& oRow = CTable::CreateRow();

//	oRow[ITEM_ID]   = 0;
//	oRow[TYPE_ID]   = 0;
	oRow[PAID]      = 0;
	oRow[ITEM_DATE] = null;
	oRow[ITEM_NAME] = null;
	
	return oRow;
}
