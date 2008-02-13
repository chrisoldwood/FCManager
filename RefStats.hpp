/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		REFSTATS.HPP
** COMPONENT:	The Application.
** DESCRIPTION:	The CRefStats class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef REFSTATS_HPP
#define REFSTATS_HPP

#if _MSC_VER > 1000
#pragma once
#endif

/******************************************************************************
** 
** This is the table used to store all referee statistics.
**
*******************************************************************************
*/

class CRefStats : public CStats
{
public:
	//
	// Constructors/Destructor.
	//
	CRefStats(CMDB& oDB, CRefStatTypes& oTypes);
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

inline CRefStats::CRefStats(CMDB& oDB, CRefStatTypes& oTypes)
	: CStats(oDB, TXT("RefStats"), oTypes)
{
}

#endif //REFSTATS_HPP
