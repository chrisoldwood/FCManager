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

#if _MSC_VER > 1000
#pragma once
#endif

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
	: CStats(oDB, TXT("FixStats"), oTypes)
{
}

#endif //FIXSTATS_HPP
