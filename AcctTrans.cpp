/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		ACCTTRANS.CPP
** COMPONENT:	The Application.
** DESCRIPTION:	CAcctTrans class definition.
**
*******************************************************************************
*/

#include "Common.hpp"
#include "AcctTrans.hpp"

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

CAcctTrans::CAcctTrans()
	: CTable(TXT("AcctTrans"))
{
	// Create the table schema.
	AddColumn(TXT("ID"),      MDCT_IDENTITY, 0,         CColumn::IDENTITY);
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

CAcctTrans::~CAcctTrans()
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

CRow& CAcctTrans::CreateRow()
{
	CRow& oRow = CTable::CreateRow();

//	oRow[ID]      = 0;
	
	return oRow;
}
