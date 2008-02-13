/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		BALSHEET.CPP
** COMPONENT:	The Application.
** DESCRIPTION:	CBalSheet class definition.
**
*******************************************************************************
*/

#include "Common.hpp"
#include "BalSheet.hpp"
#include "BalShtTypes.hpp"
#include <time.h>
#include <WCL/Date.hpp>

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

CBalSheet::CBalSheet(CMDB& oDB, CBalShtTypes& oTypes)
	: CTable(oDB, TXT("BalanceSheet"))
{
	// Create the table schema.
	AddColumn(TXT("ID"),          MDCT_IDENTITY, 0,					CColumn::IDENTITY);
	AddColumn(TXT("Name"),        MDCT_FXDSTR,   NAME_LEN,			CColumn::DEFAULTS);
	AddColumn(TXT("Date"),        MDCT_DATETIME, 0,					CColumn::DEFAULTS);
	AddColumn(TXT("TypeID"),      oTypes,		CBalShtTypes::ID,	CColumn::FOREIGNKEY);
	AddColumn(TXT("CreditType"),  MDCT_INT,		0,					CColumn::DEFAULTS);
	AddColumn(TXT("CreditTotal"), MDCT_INT,	    0,					CColumn::DEFAULTS);
	AddColumn(TXT("DebitType"),   MDCT_INT,		0,					CColumn::DEFAULTS);
	AddColumn(TXT("DebitTotal"),  MDCT_INT,      0,					CColumn::DEFAULTS);
	AddColumn(TXT("Balance"),     MDCT_INT,      0,					CColumn::DEFAULTS);
	AddColumn(TXT("Notes"),       MDCT_VARSTR,   NOTES_LEN,			CColumn::DEFAULTS);

	// Add the "TOTAL" row.
	CRow& oRow = CreateRow();

	oRow[NAME]        = TXT("TOTAL");
	oRow[DATE]        = CDate::Max().GetDateInSecs();
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
	oRow[NAME]          = TXT("");
	oRow[DATE]          = time(NULL);
	oRow[TYPE_ID]       = CBalShtTypes::OTHER;
	oRow[CREDIT_TYPE]   = NONE;
	oRow[CREDIT_TOTAL]  = 0;
	oRow[DEBIT_TYPE]    = NONE;
	oRow[DEBIT_TOTAL]   = 0;
	oRow[BALANCE]       = 0;
	oRow[NOTES]         = TXT("");
	
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
	for (size_t i  = 0; i < RowCount(); i++)
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
