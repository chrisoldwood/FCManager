/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		OPPONENTS.CPP
** COMPONENT:	The Application.
** DESCRIPTION:	COpponents class definition.
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

COpponents::COpponents(CMDB& oDB)
	: CTable(oDB, "Opponents")
{
	// Create the table schema.
	AddColumn("ID",         MDT_IDENTITY,	0);				// ID
	AddColumn("Ground",     MDT_FXDSTR,		GROUND_LEN);	// GROUND
	AddColumn("StdColours", MDT_FXDSTR,		COLOURS_LEN);	// STANDARD_CLRS
	AddColumn("AltColours", MDT_FXDSTR,		COLOURS_LEN);	// ALTERNATE_CLRS
	AddColumn("Name",       MDT_FXDSTR,		CLUB_NAME_LEN);	// CLUB_NAME
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

COpponents::~COpponents()
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

CRow& COpponents::CreateRow()
{
	CRow& oRow = CTable::CreateRow();

//	oRow[ID             ] = 0;
	oRow[CLUB_NAME      ] = "";
	oRow[GROUND         ] = "";
	oRow[STANDARD_CLRS  ] = "",
	oRow[ALTERNATE_CLRS ] = "",
	oRow[SURNAME        ] = "";
	oRow[FORENAME       ] = "";
	oRow[POSTAL_ADDRESS ] = "";
	oRow[STANDARD_PHONE ] = "";
	oRow[ALTERNATE_PHONE] = "";
	oRow[EMAIL_ADDRESS  ] = "";
	oRow[NOTES          ] = "";
	
	return oRow;
}
