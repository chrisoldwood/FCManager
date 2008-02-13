/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		SUBS.CPP
** COMPONENT:	The Application.
** DESCRIPTION:	CSubs class definition.
**
*******************************************************************************
*/

#include "Common.hpp"
#include "Subs.hpp"
#include "BalSheet.hpp"
#include "Members.hpp"

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

CSubs::CSubs(CMDB& oDB, CBalSheet& oBalSheet, CMembers& oMembers)
	: CTable(oDB, TXT("Subs"))
{
	// Create the table schema.
	AddColumn(TXT("ItemID"),   oBalSheet, CBalSheet::ID);		// ITEM_ID
	AddColumn(TXT("MemberID"), oMembers,  CMembers::ID );		// MEMBER_ID
	AddColumn(TXT("Fee"),      MDCT_INT,	 0            );		// FEE
	AddColumn(TXT("Paid"),     MDCT_INT,  0            );		// PAID
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

CSubs::~CSubs()
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

CRow& CSubs::CreateRow()
{
	CRow& oRow = CTable::CreateRow();

//	oRow[ITEM_ID  ] = 0;
//	oRow[MEMBER_ID] = 0;
	oRow[FEE ]      = 0;
	oRow[PAID]      = 0;
	
	return oRow;
}
