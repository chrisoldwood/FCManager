/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		FCMDB.CPP
** COMPONENT:	The Application.
** DESCRIPTION:	CFCMDB class definition.
**
*******************************************************************************
*/

#include "Common.hpp"
#include "FCMDB.hpp"

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

CFCMDB::CFCMDB()
	: m_oDetails()
	, m_oMembers()
	, m_oFixtures()
	, m_oBalShtTypes()
	, m_oBalSheet(m_oBalShtTypes)
	, m_oSubs(m_oBalSheet, m_oMembers)
	, m_oExpenseTypes()
	, m_oExpenses(m_oBalSheet, m_oExpenseTypes)
	, m_oAccounts()
	, m_oAcctTrans()
	, m_oTeamSels(m_oMembers)
	, m_oOpponents()
	, m_oReferees()
	, m_oMemStatTypes()
	, m_oMemStats(m_oMemStatTypes)
	, m_oFixStatTypes()
	, m_oFixStats(m_oFixStatTypes)
	, m_oOppStatTypes()
	, m_oOppStats(m_oOppStatTypes)
	, m_oRefStatTypes()
	, m_oRefStats(m_oRefStatTypes)
{
	// Create the database schema.
	AddTable(m_oDetails);
	AddTable(m_oMembers);
	AddTable(m_oFixtures);
	AddTable(m_oBalShtTypes);
	AddTable(m_oBalSheet);
	AddTable(m_oSubs);
	AddTable(m_oExpenseTypes);
	AddTable(m_oExpenses);
	AddTable(m_oAccounts);
	AddTable(m_oAcctTrans);
	AddTable(m_oTeamSels);
	AddTable(m_oOpponents);
	AddTable(m_oReferees);
	AddTable(m_oMemStatTypes);
	AddTable(m_oMemStats);
	AddTable(m_oFixStatTypes);
	AddTable(m_oFixStats);
	AddTable(m_oOppStatTypes);
	AddTable(m_oOppStats);
	AddTable(m_oRefStatTypes);
	AddTable(m_oRefStats);
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

CFCMDB::~CFCMDB()
{
}
