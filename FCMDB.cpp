/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		FCMDB.CPP
** COMPONENT:	The Application.
** DESCRIPTION:	CFCMDB class definition.
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

CFCMDB::CFCMDB()
	: m_oDetails(*this)
	, m_oMembers(*this)
	, m_oFixtures(*this)
	, m_oBalSheet(*this)
	, m_oSubs(*this, m_oBalSheet, m_oMembers)
	, m_oExpenseTypes(*this)
	, m_oExpenses(*this, m_oBalSheet, m_oExpenseTypes)
	, m_oAccounts(*this)
	, m_oAcctTrans(*this)
	, m_oTeamSels(*this, m_oMembers)
	, m_oOpponents(*this)
	, m_oReferees(*this)
	, m_oMemStatTypes(*this)
	, m_oMemStats(*this, m_oMemStatTypes)
	, m_oFixStatTypes(*this)
	, m_oFixStats(*this, m_oFixStatTypes)
	, m_oOppStatTypes(*this)
	, m_oOppStats(*this, m_oOppStatTypes)
	, m_oRefStatTypes(*this)
	, m_oRefStats(*this, m_oRefStatTypes)
{
	// Create the database schema.
	AddTable(m_oDetails);
	AddTable(m_oMembers);
	AddTable(m_oFixtures);
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
