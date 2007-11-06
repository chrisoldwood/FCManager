/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		FCMDB.HPP
** COMPONENT:	The Application.
** DESCRIPTION:	The CFCMDB class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef FCMDB_HPP
#define FCMDB_HPP

#if _MSC_VER > 1000
#pragma once
#endif

#include <MDBL/MDB.hpp>
#include "ClubDetails.hpp"		
#include "Members.hpp"
#include "Fixtures.hpp"
#include "BalShtTypes.hpp"
#include "BalSheet.hpp"
#include "Subs.hpp"
#include "ExpenseTypes.hpp"
#include "Expenses.hpp"
#include "Accounts.hpp"
#include "AcctTrans.hpp"
#include "TeamSels.hpp"
#include "Opponents.hpp"
#include "Referees.hpp"
#include "MemStatTypes.hpp"
#include "MemStats.hpp"
#include "FixStatTypes.hpp"
#include "FixStats.hpp"
#include "OppStatTypes.hpp"
#include "OppStats.hpp"
#include "RefStatTypes.hpp"
#include "RefStats.hpp"

/******************************************************************************
** 
** This is the database for the application.
**
*******************************************************************************
*/

class CFCMDB : public CMDB
{
public:
	//
	// Constructors/Destructor.
	//
	CFCMDB();
	~CFCMDB();
	
	//
	// Table numbers,
	//
/*	enum
	{
		DETAILS,
		MEMBERS,
		FIXTURES,
		BALSHEET_TYPES,
		BALSHEET,
		SUBS,
		EXPENSE_TYPES,
		EXPENSES,
		ACCOUNTS,
		ACCTTRANS,
		TEAMSELS,
		OPPONENTS,
		REFEREES,
		MEM_STAT_TYPES,
		MEM_STATS,
		FIX_STAT_TYPES,
		FIX_STATS,
		OPP_STAT_TYPES,
		OPP_STATS,
		REF_STAT_TYPES,
		REF_STATS,
	};
*/
	//
	// Tables.
	//
	CClubDetails	m_oDetails;			// The clubs basic details.
	CMembers		m_oMembers;			// The table of club members.
	CFixtures		m_oFixtures;		// The table of club fixtures.
	CBalShtTypes 	m_oBalShtTypes;		// The table of the balance sheet item types.
	CBalSheet		m_oBalSheet;		// The table of the balance sheet.
	CSubs			m_oSubs;			// The table of members subs.
	CExpenseTypes	m_oExpenseTypes;	// The table of expense types.
	CExpenses		m_oExpenses;		// The table of expenses.
	CAccounts		m_oAccounts;		// The table of accounts.
	CAcctTrans		m_oAcctTrans;		// The table of account transactions.
	CTeamSels		m_oTeamSels;		// The table of team sheets.
	COpponents		m_oOpponents;		// The table of league opponents.
	CReferees		m_oReferees;		// The table of league referees.
	CMemStatTypes	m_oMemStatTypes;	// The table of member statistic types.
	CMemStats		m_oMemStats;		// The table of member statistics.
	CFixStatTypes	m_oFixStatTypes;	// The table of fixture statistic types.
	CFixStats		m_oFixStats;		// The table of fixture statistics.
	COppStatTypes	m_oOppStatTypes;	// The table of opponent statistic types.
	COppStats		m_oOppStats;		// The table of opponent statistics.
	CRefStatTypes	m_oRefStatTypes;	// The table of referee statistic types.
	CRefStats		m_oRefStats;		// The table of referee statistics.
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

#endif //FCMDB_HPP
