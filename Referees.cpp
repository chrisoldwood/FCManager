/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		REFEREES.CPP
** COMPONENT:	The Application.
** DESCRIPTION:	CReferees class definition.
**
*******************************************************************************
*/

#include "Common.hpp"
#include "Referees.hpp"

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

CReferees::CReferees(CMDB& oDB)
	: CTable(oDB, TXT("Referees"))
{
	// Create the table schema.
	AddColumn(TXT("ID"),         MDCT_IDENTITY,	0);				// ID             
	AddColumn(TXT("Surname"),    MDCT_FXDSTR,		SURNAME_LEN);	// SURNAME        
	AddColumn(TXT("Forename"),   MDCT_FXDSTR,		FORENAME_LEN);	// FORENAME       
	AddColumn(TXT("PostalAddr"), MDCT_VARSTR,		POSTAL_LEN);	// POSTAL_ADDRESS 
	AddColumn(TXT("StdPhone"),   MDCT_FXDSTR,		PHONE_LEN);		// STANDARD_PHONE 
	AddColumn(TXT("AltPhone"),   MDCT_FXDSTR,		PHONE_LEN);		// ALTERNATE_PHONE
	AddColumn(TXT("EmailAddr"),  MDCT_FXDSTR,		EMAIL_LEN);		// EMAIL_ADDRESS  
	AddColumn(TXT("Notes"),      MDCT_VARSTR,		NOTES_LEN);		// NOTES           

	// Add the indexes.
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

CReferees::~CReferees()
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

CRow& CReferees::CreateRow()
{
	CRow& oRow = CTable::CreateRow();

//	oRow[ID              ] = 0;
	oRow[SURNAME         ] = TXT("");
	oRow[FORENAME        ] = TXT("");
	oRow[POSTAL_ADDRESS  ] = TXT("");
	oRow[STANDARD_PHONE  ] = TXT("");
	oRow[ALTERNATE_PHONE ] = TXT("");
	oRow[EMAIL_ADDRESS   ] = TXT("");
	oRow[NOTES           ] = TXT("");
	
	return oRow;
}
