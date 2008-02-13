/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		OPPONENTS.CPP
** COMPONENT:	The Application.
** DESCRIPTION:	COpponents class definition.
**
*******************************************************************************
*/

#include "Common.hpp"
#include "Opponents.hpp"

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
	: CTable(oDB, TXT("Opponents"))
{
	// Create the table schema.
	AddColumn(TXT("ID"),         MDCT_IDENTITY, 0,             CColumn::IDENTITY);	// ID
	AddColumn(TXT("Ground"),     MDCT_FXDSTR,   GROUND_LEN,    CColumn::DEFAULTS);	// GROUND
	AddColumn(TXT("StdColours"), MDCT_FXDSTR,   COLOURS_LEN,   CColumn::DEFAULTS);	// STANDARD_CLRS
	AddColumn(TXT("AltColours"), MDCT_FXDSTR,   COLOURS_LEN,   CColumn::DEFAULTS);	// ALTERNATE_CLRS
	AddColumn(TXT("Name"),       MDCT_FXDSTR,   CLUB_NAME_LEN, CColumn::DEFAULTS);	// CLUB_NAME
	AddColumn(TXT("Surname"),    MDCT_FXDSTR,   SURNAME_LEN,   CColumn::DEFAULTS);	// SURNAME
	AddColumn(TXT("Forename"),   MDCT_FXDSTR,   FORENAME_LEN,  CColumn::DEFAULTS);	// FORENAME
	AddColumn(TXT("PostalAddr"), MDCT_VARSTR,   POSTAL_LEN,    CColumn::DEFAULTS);	// POSTAL_ADDRESS
	AddColumn(TXT("StdPhone"),   MDCT_FXDSTR,   PHONE_LEN,     CColumn::DEFAULTS);	// STANDARD_PHONE
	AddColumn(TXT("AltPhone"),   MDCT_FXDSTR,   PHONE_LEN,     CColumn::DEFAULTS);	// ALTERNATE_PHONE
	AddColumn(TXT("EmailAddr"),  MDCT_FXDSTR,   EMAIL_LEN,     CColumn::DEFAULTS);	// EMAIL_ADDRESS
	AddColumn(TXT("Notes"),      MDCT_VARSTR,   NOTES_LEN,     CColumn::DEFAULTS);	// NOTES           

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
	oRow[CLUB_NAME      ] = TXT("");
	oRow[GROUND         ] = TXT("");
	oRow[STANDARD_CLRS  ] = TXT(""),
	oRow[ALTERNATE_CLRS ] = TXT(""),
	oRow[SURNAME        ] = TXT("");
	oRow[FORENAME       ] = TXT("");
	oRow[POSTAL_ADDRESS ] = TXT("");
	oRow[STANDARD_PHONE ] = TXT("");
	oRow[ALTERNATE_PHONE] = TXT("");
	oRow[EMAIL_ADDRESS  ] = TXT("");
	oRow[NOTES          ] = TXT("");
	
	return oRow;
}
