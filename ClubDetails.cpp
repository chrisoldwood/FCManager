/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		CLUBDETAILS.CPP
** COMPONENT:	The Application.
** DESCRIPTION:	CClubDetails class definition.
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

CClubDetails::CClubDetails(CMDB& oDB)
	: CTable(oDB, "ClubDetails")
{
	// Create the table schema.
	AddColumn("Name", MDCT_FXDSTR, NAME_LEN, CColumn::DEFAULTS);	// NAME

	// Add the single row.
	CRow& oRow = CreateRow();

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

CClubDetails::~CClubDetails()
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

CRow& CClubDetails::CreateRow()
{
	CRow& oRow = CTable::CreateRow();

	oRow[NAME] = "Your Club F.C.";
	
	return oRow;
}
