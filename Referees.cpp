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
	AddColumn("ID",         MDT_IDENTITY,	0);				// ID             
	AddColumn("Surname",    MDT_FXDSTR,		SURNAME_LEN);	// SURNAME        
	AddColumn("Forename",   MDT_FXDSTR,		FORENAME_LEN);	// FORENAME       
	AddColumn("PostalAddr", MDT_FXDSTR,		POSTAL_LEN);	// POSTAL_ADDRESS 
	AddColumn("StdPhone",   MDT_FXDSTR,		PHONE_LEN);		// STANDARD_PHONE 
	AddColumn("AltPhone",   MDT_FXDSTR,		PHONE_LEN);		// ALTERNATE_PHONE
	AddColumn("EmailAddr",  MDT_FXDSTR,		EMAIL_LEN);		// EMAIL_ADDRESS  
	AddColumn("Notes",      MDT_FXDSTR,		NOTES_LEN);		// NOTES           

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
