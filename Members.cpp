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
	AddColumn("ID",            MDT_IDENTITY,	0);				// ID             
	AddColumn("Surname",       MDT_FXDSTR,		SURNAME_LEN);	// SURNAME        
	AddColumn("Forename",      MDT_FXDSTR,		FORENAME_LEN);	// FORENAME       
	AddColumn("PostalAddr",    MDT_FXDSTR,		POSTAL_LEN);	// POSTAL_ADDRESS 
	AddColumn("StdPhone",      MDT_FXDSTR,		PHONE_LEN);		// STANDARD_PHONE 
	AddColumn("AltPhone",      MDT_FXDSTR,		PHONE_LEN);		// ALTERNATE_PHONE
	AddColumn("EmailAddr",     MDT_FXDSTR,		EMAIL_LEN);		// EMAIL_ADDRESS  
	AddColumn("IsRegistered",  MDT_BOOL,		0);				// IS_REGISTERED  
	AddColumn("IsSenior",      MDT_BOOL,		0);				// IS_SENIOR      
	AddColumn("UsualTeam",     MDT_INT,			0);				// USUAL_TEAM     
	AddColumn("UsualPosition", MDT_INT,			0);				// USUAL_POSITION  
	AddColumn("Notes",         MDT_FXDSTR,		NOTES_LEN);		// NOTES           

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
