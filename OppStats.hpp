/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		OPPSTATS.HPP
** COMPONENT:	The Application.
** DESCRIPTION:	The COppStats class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef OPPSTATS_HPP
#define OPPSTATS_HPP

#if _MSC_VER > 1000
#pragma once
#endif

/******************************************************************************
** 
** This is the table used to store all opponents statistics.
**
*******************************************************************************
*/

class COppStats : public CStats
{
public:
	//
	// Constructors/Destructor.
	//
	COppStats(CMDB& oDB, COppStatTypes& oTypes);
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

inline COppStats::COppStats(CMDB& oDB, COppStatTypes& oTypes)
	: CStats(oDB, "OppStats", oTypes)
{
}

#endif //OPPSTATS_HPP
