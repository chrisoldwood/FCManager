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
	AddColumn("ID",     MDT_IDENTITY, 0);				// ID
	AddColumn("Name",   MDT_FXDSTR,   NAME_LEN);		// NAME
	AddColumn("Date",   MDT_DATE,     0);				// DATE
	AddColumn("Credit", MDT_INT,	  0);				// CREDIT
	AddColumn("Debit",  MDT_INT,      0);				// DEBIT
	AddColumn("Total",  MDT_INT,      0);				// TOTAL
	AddColumn("Notes",  MDT_FXDSTR,   NOTES_LEN);		// NOTES

	// Add the "TOTAL" row.
	CRow& oRow = CreateRow();

	oRow[NAME] = "TOTALS";

	InsertRow(oRow);

	// Reset modified flags.
	oRow.Status(CRow::ORIGINAL);
	m_bInserted = false;
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

//	oRow[ID    ] = 0;
	oRow[NAME  ] = "";
	oRow[DATE  ] = CDate::Current();
	oRow[CREDIT] = 0;
	oRow[DEBIT ] = 0;
	oRow[TOTAL ] = 0;
	oRow[NOTES ] = "";
	
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

		nCredit += oRow[CREDIT].GetInt();
		nDebit  += oRow[DEBIT].GetInt();
		nTotal  += oRow[TOTAL].GetInt();
	}

	ASSERT(pTotals != NULL);
	ASSERT((nCredit - nDebit) == nTotal);

	// Save totals.
	pTotals->Field(CREDIT) = nCredit;
	pTotals->Field(DEBIT)  = nDebit;
	pTotals->Field(TOTAL)  = nTotal;
}
