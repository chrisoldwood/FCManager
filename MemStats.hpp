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

#endif //MEMSTATS_HPP
