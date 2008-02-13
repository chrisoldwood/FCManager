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
	: CTable(oDB, TXT("Accounts"))
{
	// Create the table schema.
	AddColumn(TXT("ID"),      MDCT_IDENTITY, 0,         CColumn::IDENTITY);
	AddColumn(TXT("Name"),    MDCT_FXDSTR,   NAME_LEN,  CColumn::DEFAULTS);
	AddColumn(TXT("Type"),    MDCT_INT,      0,         CColumn::DEFAULTS);
	AddColumn(TXT("Balance"), MDCT_INT,	    0,         CColumn::DEFAULTS);
	AddColumn(TXT("Notes"),   MDCT_VARSTR,   NOTES_LEN, CColumn::DEFAULTS);

	// Add the "TOTAL" row.
	CRow& oRow = CreateRow();

	oRow[NAME] = TXT("TOTAL");

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
	oRow[NAME]    = TXT("");
	oRow[TYPE]    = FIXED;
	oRow[BALANCE] = 0;
	oRow[NOTES]   = TXT("");
	
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
	for (size_t i  = 0; i < RowCount(); i++)
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
