/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		MEMSTATS.HPP
** COMPONENT:	The Application.
** DESCRIPTION:	The CMemStats class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef MEMSTATS_HPP
#define MEMSTATS_HPP

/******************************************************************************
** 
** This is the table used to store all members statistics.
**
*******************************************************************************
*/

class CMemStats : public CStats
{
public:
	//
	// Constructors/Destructor.
	//
	CMemStats(CMDB& oDB, CMemStatTypes& oTypes);

	//
	// Methods.
	//
	void DeleteMembersStats(int nMember);
	void DeleteTypesStats(int nType);
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

inline CMemStats::CMemStats(CMDB& oDB, CMemStatTypes& oTypes)
	: CStats(oDB, "MemStats", oTypes)
{
}

inline void CMemStats::DeleteMembersStats(int nMember)
{
	DeleteRows(Select(CWhereEqual(OWNER_ID, nMember)));
}

inline void CMemStats::DeleteTypesStats(int nType)
{
	DeleteRows(Select(CWhereEqual(TYPE_ID, nType)));
}

#endif //MEMSTATS_HPP
