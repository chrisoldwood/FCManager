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
	AddColumn("ID",         MDCT_IDENTITY, 0,             CColumn::IDENTITY);	// ID
	AddColumn("Ground",     MDCT_FXDSTR,   GROUND_LEN,    CColumn::DEFAULTS);	// GROUND
	AddColumn("StdColours", MDCT_FXDSTR,   COLOURS_LEN,   CColumn::DEFAULTS);	// STANDARD_CLRS
	AddColumn("AltColours", MDCT_FXDSTR,   COLOURS_LEN,   CColumn::DEFAULTS);	// ALTERNATE_CLRS
	AddColumn("Name",       MDCT_FXDSTR,   CLUB_NAME_LEN, CColumn::DEFAULTS);	// CLUB_NAME
	AddColumn("Surname",    MDCT_FXDSTR,   SURNAME_LEN,   CColumn::DEFAULTS);	// SURNAME
	AddColumn("Forename",   MDCT_FXDSTR,   FORENAME_LEN,  CColumn::DEFAULTS);	// FORENAME
	AddColumn("PostalAddr", MDCT_VARSTR,   POSTAL_LEN,    CColumn::DEFAULTS);	// POSTAL_ADDRESS
	AddColumn("StdPhone",   MDCT_FXDSTR,   PHONE_LEN,     CColumn::DEFAULTS);	// STANDARD_PHONE
	AddColumn("AltPhone",   MDCT_FXDSTR,   PHONE_LEN,     CColumn::DEFAULTS);	// ALTERNATE_PHONE
	AddColumn("EmailAddr",  MDCT_FXDSTR,   EMAIL_LEN,     CColumn::DEFAULTS);	// EMAIL_ADDRESS
	AddColumn("Notes",      MDCT_VARSTR,   NOTES_LEN,     CColumn::DEFAULTS);	// NOTES           

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
