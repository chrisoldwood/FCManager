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
		BALSHEET,
		SUBS,
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
	CBalSheet		m_oBalSheet;		// The table of the balance sheet.
	CSubs			m_oSubs;			// The table of members subs.
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
