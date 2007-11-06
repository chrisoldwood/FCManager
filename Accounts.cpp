/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		ACCOUNTS.CPP
** COMPONENT:	The Application.
** DESCRIPTION:	CAccounts class definition.
**
*******************************************************************************
*/

#include "Common.hpp"
#include "Accounts.hpp"

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

CAccounts::CAccounts(CMDB& oDB)
	: CTable(oDB, "Accounts")
{
	// Create the table schema.
	AddColumn("ID",      MDCT_IDENTITY, 0,         CColumn::IDENTITY);
	AddColumn("Name",    MDCT_FXDSTR,   NAME_LEN,  CColumn::DEFAULTS);
	AddColumn("Type",    MDCT_INT,      0,         CColumn::DEFAULTS);
	AddColumn("Balance", MDCT_INT,	    0,         CColumn::DEFAULTS);
	AddColumn("Notes",   MDCT_VARSTR,   NOTES_LEN, CColumn::DEFAULTS);

	// Add the "TOTAL" row.
	CRow& oRow = CreateRow();

	oRow[NAME] = "TOTAL";

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

CAccounts::~CAccounts()
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

CRow& CAccounts::CreateRow()
{
	CRow& oRow = CTable::CreateRow();

//	oRow[ID]      = 0;
	oRow[NAME]    = "";
	oRow[TYPE]    = FIXED;
	oRow[BALANCE] = 0;
	oRow[NOTES]   = "";
	
	return oRow;
}

/******************************************************************************
** Method:		UpdateTotalsRow()
**
** Description:	Calculates the total and updates it.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CAccounts::UpdateTotalRow()
{
	CRow* pTotal = NULL;
	int   nTotal = 0;

	// For all rows...
	for (int i  = 0; i < RowCount(); i++)
	{
		CRow& oRow = Row(i);

		// Ignore totals row.
		if (oRow[ID].GetInt() == 1)
		{
			pTotal = &oRow;
			continue;
		}

		nTotal += oRow[BALANCE].GetInt();
	}

	ASSERT(pTotal != NULL);

	// Save total.
	pTotal->Field(BALANCE) = nTotal;
}
