/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		MEMSTATTYPES.HPP
** COMPONENT:	The Application.
** DESCRIPTION:	The CMemStatTypes class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef MEMSTATTYPES_HPP
#define MEMSTATTYPES_HPP

#if _MSC_VER > 1000
#pragma once
#endif

#include "StatTypes.hpp"

/******************************************************************************
** 
** This is the table used to store all member statistic types.
**
*******************************************************************************
*/

class CMemStatTypes : public CStatTypes
{
public:
	//
	// Constructors/Destructor.
	//
	CMemStatTypes(CMDB& oDB);
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

inline CMemStatTypes::CMemStatTypes(CMDB& oDB)
	: CStatTypes(oDB, TXT("MemStatTypes"))
{
	// Add the pre-defined statistics.
	AddPredefined(TXT("Played"));
	AddPredefined(TXT("Trained"));
	AddPredefined(TXT("Goals"));
	AddPredefined(TXT("Own Goals"));
	AddPredefined(TXT("Bookings"));
	AddPredefined(TXT("Dismisals"));
	AddPredefined(TXT("Substitutions"));
	AddPredefined(TXT("Man o/t Match"));
}

#endif //MEMSTATTYPES_HPP
