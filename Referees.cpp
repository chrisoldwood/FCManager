/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		REFEREES.CPP
** COMPONENT:	The Application.
** DESCRIPTION:	CReferees class definition.
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

CReferees::CReferees(CMDB& oDB)
	: CTable(oDB, "Referees")
{
	// Create the table schema.
	AddColumn("ID",         MDCT_IDENTITY,	0);				// ID             
	AddColumn("Surname",    MDCT_FXDSTR,		SURNAME_LEN);	// SURNAME        
	AddColumn("Forename",   MDCT_FXDSTR,		FORENAME_LEN);	// FORENAME       
	AddColumn("PostalAddr", MDCT_VARSTR,		POSTAL_LEN);	// POSTAL_ADDRESS 
	AddColumn("StdPhone",   MDCT_FXDSTR,		PHONE_LEN);		// STANDARD_PHONE 
	AddColumn("AltPhone",   MDCT_FXDSTR,		PHONE_LEN);		// ALTERNATE_PHONE
	AddColumn("EmailAddr",  MDCT_FXDSTR,		EMAIL_LEN);		// EMAIL_ADDRESS  
	AddColumn("Notes",      MDCT_VARSTR,		NOTES_LEN);		// NOTES           

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
	oRow[SURNAME         ] = "";
	oRow[FORENAME        ] = "";
	oRow[POSTAL_ADDRESS  ] = "";
	oRow[STANDARD_PHONE  ] = "";
	oRow[ALTERNATE_PHONE ] = "";
	oRow[EMAIL_ADDRESS   ] = "";
	oRow[NOTES           ] = "";
	
	return oRow;
}
