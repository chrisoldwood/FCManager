/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		MEMBERS.CPP
** COMPONENT:	The Application.
** DESCRIPTION:	CMembers class definition.
**
*******************************************************************************
*/

#include "Common.hpp"
#include "Members.hpp"
#include <MDBL/ResultSet.hpp>
#include <MDBL/WhereCmp.hpp>
#include "Subs.hpp"

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
	AddColumn("ID",            MDCT_IDENTITY,	0,            CColumn::IDENTITY);
	AddColumn("Surname",       MDCT_FXDSTR,		SURNAME_LEN,  CColumn::DEFAULTS);
	AddColumn("Forename",      MDCT_FXDSTR,		FORENAME_LEN, CColumn::DEFAULTS);
	AddColumn("PostalAddr",    MDCT_VARSTR,		POSTAL_LEN,   CColumn::DEFAULTS);
	AddColumn("StdPhone",      MDCT_FXDSTR,		PHONE_LEN,    CColumn::DEFAULTS);
	AddColumn("AltPhone",      MDCT_FXDSTR,		PHONE_LEN,    CColumn::DEFAULTS);
	AddColumn("EmailAddr",     MDCT_FXDSTR,		EMAIL_LEN,    CColumn::DEFAULTS);
	AddColumn("IsRegistered",  MDCT_BOOL,		0,            CColumn::DEFAULTS);
	AddColumn("IsSenior",      MDCT_BOOL,		0,            CColumn::DEFAULTS);
	AddColumn("UsualTeam",     MDCT_INT,		0,            CColumn::DEFAULTS);
	AddColumn("UsualPosition", MDCT_INT,		0,            CColumn::DEFAULTS);
	AddColumn("IsAvailable",   MDCT_BOOL,		0,            CColumn::DEFAULTS);
	AddColumn("UnavailReason", MDCT_INT,		0,            CColumn::DEFAULTS);
	AddColumn("Notes",         MDCT_VARSTR,		NOTES_LEN,    CColumn::DEFAULTS);
	AddColumn("Balance",       MDCT_INT,	    0,            CColumn::DEFAULTS);
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

//	oRow[ID]              = 0;
	oRow[SURNAME]         = "";
	oRow[FORENAME]        = "";
	oRow[POSTAL_ADDRESS]  = "";
	oRow[STANDARD_PHONE]  = "";
	oRow[ALTERNATE_PHONE] = "";
	oRow[EMAIL_ADDRESS]   = "";
	oRow[IS_REGISTERED]   = false;
	oRow[IS_SENIOR]       = false;
	oRow[USUAL_TEAM]      = 0;
	oRow[USUAL_POSITION]  = 0;
	oRow[IS_AVAILABLE]    = true;
	oRow[UNAVAIL_REASON]  = 0;
	oRow[NOTES]           = "";
	oRow[BALANCE]         = 0;
	
	return oRow;
}

/******************************************************************************
** Method:		UpdateBalances()
**
** Description:	Updates the balances for all members, if changed.
**
** Parameters:	oSubs		The members subs table.
**				aoModified	The vector used to return to the rows modified.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CMembers::UpdateBalances(CSubs& oSubs, TRefArray<CRow>& aoModified)
{
	// Clear the output vector.	
	aoModified.RemoveAll();

	// For all members.
	for (int i = 0; i < RowCount(); i++)
	{
		// Find all subs for the member.
		CRow&		oRow = Row(i);
		CResultSet	oRS  = oSubs.Select(CWhereCmp(CSubs::MEMBER_ID, CWhereCmp::EQUALS, oRow[ID]));

		// Calculate the fees, paid and balance.
		int nFees   = oRS.Sum(CSubs::FEE ).m_iValue;
		int nPaid   = oRS.Sum(CSubs::PAID).m_iValue;
		int nNewBal = nPaid - nFees;
		int nCurBal = oRow[BALANCE];

		// Modified?
		if (nNewBal != nCurBal)
		{
			oRow[BALANCE] = nNewBal;
			aoModified.Add(oRow);
		}
	}
}
