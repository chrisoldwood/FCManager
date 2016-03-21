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
	CRefStats(CRefStatTypes& oTypes);
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

inline CRefStats::CRefStats(CRefStatTypes& oTypes)
	: CStats(TXT("RefStats"), oTypes)
{
}

#endif //REFSTATS_HPP
