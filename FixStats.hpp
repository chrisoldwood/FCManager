/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		FIXSTATS.HPP
** COMPONENT:	The Application.
** DESCRIPTION:	The CFixStats class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef FIXSTATS_HPP
#define FIXSTATS_HPP

/******************************************************************************
** 
** This is the table used to store all fixture statistics.
**
*******************************************************************************
*/

class CFixStats : public CStats
{
public:
	//
	// Constructors/Destructor.
	//
	CFixStats(CMDB& oDB, CFixStatTypes& oTypes);
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

inline CFixStats::CFixStats(CMDB& oDB, CFixStatTypes& oTypes)
	: CStats(oDB, "FixStats", oTypes)
{
}

#endif //FIXSTATS_HPP
