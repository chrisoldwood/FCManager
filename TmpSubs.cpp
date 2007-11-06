/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		TMPSUBS.CPP
** COMPONENT:	The Application.
** DESCRIPTION:	CTmpSubs class definition.
**
*******************************************************************************
*/

#include "Common.hpp"
#include "TmpSubs.hpp"
#include "Members.hpp"
#include "BalSheet.hpp"

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

CTmpSubs::CTmpSubs(CMDB& oDB, CMembers& oMembers, bool bSameMember)
	: CTable(oDB, "#TmpSubs")
{
	int nUniqFlag = (bSameMember) ? CColumn::NOT_UNIQUE : CColumn::UNIQUE;

	// Create the table schema.
	AddColumn("ItemID",   MDCT_INT,    0,                   CColumn::DEFAULTS);
	AddColumn("MemberID", oMembers,    CMembers::ID,        CColumn::FOREIGN_KEY | nUniqFlag);
	AddColumn("Fee",      MDCT_INT,	   0,                   CColumn::DEFAULTS);
	AddColumn("Paid",     MDCT_INT,    0,                   CColumn::DEFAULTS);
	AddColumn("ItemDate", MDCT_DATE,   0,                   CColumn::DEFAULTS | CColumn::NULLABLE);
	AddColumn("ItemName", MDCT_FXDSTR, CBalSheet::NAME_LEN, CColumn::DEFAULTS | CColumn::NULLABLE);
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

CTmpSubs::~CTmpSubs()
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

CRow& CTmpSubs::CreateRow()
{
	CRow& oRow = CTable::CreateRow();

//	oRow[ITEM_ID  ] = 0;
//	oRow[MEMBER_ID] = 0;
	oRow[FEE ]      = 0;
	oRow[PAID]      = 0;
	oRow[ITEM_DATE] = null;
	oRow[ITEM_NAME] = null;
	
	return oRow;
}
