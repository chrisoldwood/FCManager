/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		EXPENSETYPES.CPP
** COMPONENT:	The Application.
** DESCRIPTION:	CExpenseTypes class definition.
**
*******************************************************************************
*/

#include "Common.hpp"
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

CExpenseTypes::CExpenseTypes(CMDB& oDB)
	: CTable(oDB, "ExpenseTypes")
{
	// Create the table schema.
	AddColumn("ID",      MDCT_IDENTITY, 0,        CColumn::IDENTITY);
	AddColumn("Name",    MDCT_FXDSTR,   NAME_LEN, CColumn::DEFAULTS);
	AddColumn("Default", MDCT_INT,      0,        CColumn::DEFAULTS);

	// Add the predfined types.
	AddPredefined("Pitch Hire",   0);
	AddPredefined("Referees Fee", 0);
	AddPredefined("Clean Kit",    0);
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

CExpenseTypes::~CExpenseTypes()
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

CRow& CExpenseTypes::CreateRow()
{
	CRow& oRow = CTable::CreateRow();

//	oRow[ID]      = 0;
	oRow[NAME]    = "";
	oRow[DEFAULT] = 0;
	
	return oRow;
}

/******************************************************************************
** Method:		AddPredefined()
**
** Description:	Internal method to add a predefined expense type.
**
** Parameters:	pszName		The name of the expense.
**				nDefault	The default fee.
**
** Returns:		The new row.
**
*******************************************************************************
*/

void CExpenseTypes::AddPredefined(const char* pszName, int nDefault)
{
	CRow& oRow = CreateRow();

	oRow[NAME]    = pszName;
	oRow[DEFAULT] = nDefault;

	InsertRow(oRow, false);
}
