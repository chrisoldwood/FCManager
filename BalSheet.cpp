/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		BALSHEET.CPP
** COMPONENT:	The Application.
** DESCRIPTION:	CBalSheet class definition.
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

CBalSheet::CBalSheet(CMDB& oDB)
	: CTable(oDB, "BalanceSheet")
{
	// Create the table schema.
	AddColumn("ID",          MDCT_IDENTITY, 0,         CColumn::IDENTITY);	// ID
	AddColumn("Name",        MDCT_FXDSTR,   NAME_LEN,  CColumn::DEFAULTS);	// NAME
	AddColumn("Date",        MDCT_DATETIME, 0,         CColumn::DEFAULTS);	// DATE
	AddColumn("Type",        MDCT_INT,      0,         CColumn::DEFAULTS);	// TYPE
	AddColumn("CreditType",  MDCT_INT,		0,         CColumn::DEFAULTS);	// CREDIT_TYPE
	AddColumn("CreditTotal", MDCT_INT,	    0,         CColumn::DEFAULTS);	// CREDIT_TOTAL
	AddColumn("DebitType",   MDCT_INT,		0,         CColumn::DEFAULTS);	// DEBIT_TYPE
	AddColumn("DebitTotal",  MDCT_INT,      0,         CColumn::DEFAULTS);	// DEBIT_TOTAL
	AddColumn("Balance",     MDCT_INT,      0,         CColumn::DEFAULTS);	// BALANCE
	AddColumn("Notes",       MDCT_VARSTR,   NOTES_LEN, CColumn::DEFAULTS);	// NOTES

	// Add the "TOTAL" row.
	CRow& oRow = CreateRow();

	oRow[NAME]        = "TOTAL";
	oRow[DATE]        = CDate::Max();
	oRow[CREDIT_TYPE] = FIXED;
	oRow[DEBIT_TYPE]  = FIXED;

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

CBalSheet::~CBalSheet()
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

CRow& CBalSheet::CreateRow()
{
	CRow& oRow = CTable::CreateRow();

//	oRow[ID]            = 0;
	oRow[NAME]          = "";
	oRow[DATE]          = time(NULL);
	oRow[TYPE]          = OTHER;
	oRow[CREDIT_TYPE]   = NONE;
	oRow[CREDIT_TOTAL]  = 0;
	oRow[DEBIT_TYPE]    = NONE;
	oRow[DEBIT_TOTAL]   = 0;
	oRow[BALANCE]       = 0;
	oRow[NOTES]         = "";
	
	return oRow;
}

/******************************************************************************
** Method:		UpdateTotalsRow()
**
** Description:	Calculates the totals and updates them.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CBalSheet::UpdateTotalsRow()
{
	CRow* pTotals = NULL;
	int   nCredit = 0;
	int   nDebit  = 0;
	int   nTotal  = 0;

	// For all rows...
	for (int i  = 0; i < RowCount(); i++)
	{
		CRow& oRow = Row(i);

		// Ignore totals row.
		if (oRow[ID].GetInt() == 1)
		{
			pTotals = &oRow;
			continue;
		}

		nCredit += oRow[CREDIT_TOTAL].GetInt();
		nDebit  += oRow[DEBIT_TOTAL].GetInt();
		nTotal  += oRow[BALANCE].GetInt();
	}

	ASSERT(pTotals != NULL);
	ASSERT((nCredit - nDebit) == nTotal);

	// Save totals.
	pTotals->Field(CREDIT_TOTAL) = nCredit;
	pTotals->Field(DEBIT_TOTAL)  = nDebit;
	pTotals->Field(BALANCE)      = nTotal;
}
