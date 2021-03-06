/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		EXPENSES.CPP
** COMPONENT:	The Application.
** DESCRIPTION:	CExpenses class definition.
**
*******************************************************************************
*/

#include "Common.hpp"
#include "Expenses.hpp"
#include "BalSheet.hpp"
#include "ExpenseTypes.hpp"

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

CExpenses::CExpenses(CBalSheet& oBalSheet, CExpenseTypes& oTypes)
	: CTable(TXT("Expenses"))
{
	// Create the table schema.
	AddColumn(TXT("ItemID"), oBalSheet, CBalSheet::ID,     CColumn::FOREIGNKEY);
	AddColumn(TXT("TypeID"), oTypes,    CExpenseTypes::ID, CColumn::FOREIGNKEY);
	AddColumn(TXT("Paid"),   MDCT_INT,  0,                 CColumn::DEFAULTS  );
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

CExpenses::~CExpenses()
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

CRow& CExpenses::CreateRow()
{
	CRow& oRow = CTable::CreateRow();

//	oRow[ITEM_ID] = 0;
//	oRow[TYPE_ID] = 0;
	oRow[PAID]    = 0;
	
	return oRow;
}
