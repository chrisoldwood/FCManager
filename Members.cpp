/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		MEMBERS.CPP
** COMPONENT:	The Application.
** DESCRIPTION:	CMembers class definition.
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

CMembers::CMembers(CMDB& oDB)
	: CTable(oDB, "Members")
{
	// Create the table schema.
	AddColumn("ID",            MDCT_IDENTITY,	0,            CColumn::IDENTITY);	// ID             
	AddColumn("Surname",       MDCT_FXDSTR,		SURNAME_LEN,  CColumn::DEFAULTS);	// SURNAME        
	AddColumn("Forename",      MDCT_FXDSTR,		FORENAME_LEN, CColumn::DEFAULTS);	// FORENAME       
	AddColumn("PostalAddr",    MDCT_VARSTR,		POSTAL_LEN,   CColumn::DEFAULTS);	// POSTAL_ADDRESS 
	AddColumn("StdPhone",      MDCT_FXDSTR,		PHONE_LEN,    CColumn::DEFAULTS);	// STANDARD_PHONE 
	AddColumn("AltPhone",      MDCT_FXDSTR,		PHONE_LEN,    CColumn::DEFAULTS);	// ALTERNATE_PHONE
	AddColumn("EmailAddr",     MDCT_FXDSTR,		EMAIL_LEN,    CColumn::DEFAULTS);	// EMAIL_ADDRESS  
	AddColumn("IsRegistered",  MDCT_BOOL,		0,            CColumn::DEFAULTS);	// IS_REGISTERED  
	AddColumn("IsSenior",      MDCT_BOOL,		0,            CColumn::DEFAULTS);	// IS_SENIOR      
	AddColumn("UsualTeam",     MDCT_INT,		0,            CColumn::DEFAULTS);	// USUAL_TEAM     
	AddColumn("UsualPosition", MDCT_INT,		0,            CColumn::DEFAULTS);	// USUAL_POSITION  
	AddColumn("Notes",         MDCT_VARSTR,		NOTES_LEN,    CColumn::DEFAULTS);	// NOTES           

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

CMembers::~CMembers()
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

CRow& CMembers::CreateRow()
{
	CRow& oRow = CTable::CreateRow();

//	oRow[ID              ] = 0;
	oRow[SURNAME         ] = "";
	oRow[FORENAME        ] = "";
	oRow[POSTAL_ADDRESS  ] = "";
	oRow[STANDARD_PHONE  ] = "";
	oRow[ALTERNATE_PHONE ] = "";
	oRow[EMAIL_ADDRESS   ] = "";
	oRow[IS_REGISTERED   ] = false;
	oRow[IS_SENIOR       ] = false;
	oRow[USUAL_TEAM      ] = 0;
	oRow[USUAL_POSITION  ] = 0;
	oRow[NOTES           ] = "";
	
	return oRow;
}
