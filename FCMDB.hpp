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
	enum
	{
		DETAILS,
		MEMBERS,
		FIXTURES,
		BALSHEET,
		SUBS,
		TEAMSELS,
		OPPONENTS,
		REFEREES,
	};

protected:
	//
	// Tables.
	//
	CClubDetails	m_oDetails;		// The clubs basic details.
	CMembers		m_oMembers;		// The list of club members.
	CFixtures		m_oFixtures;	// The list of club fixtures.
	CBalSheet		m_oBalSheet;	// The balance sheet.
	CSubs			m_oSubs;		// The members subs.
	CTeamSels		m_oTeamSels;	// The team selections.
	COpponents		m_oOpponents;	// The list of league opponents.
	CReferees		m_oReferees;	// The list of league referees.
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

#endif //FCMDB_HPP
