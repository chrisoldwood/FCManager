/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		FIXSTATTYPES.HPP
** COMPONENT:	The Application.
** DESCRIPTION:	The CFixStatTypes class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef FIXSTATTYPES_HPP
#define FIXSTATTYPES_HPP

#if _MSC_VER > 1000
#pragma once
#endif

/******************************************************************************
** 
** This is the table used to store all fixture statistic types.
**
*******************************************************************************
*/

class CFixStatTypes : public CStatTypes
{
public:
	//
	// Constructors/Destructor.
	//
	CFixStatTypes(CMDB& oDB);
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

inline CFixStatTypes::CFixStatTypes(CMDB& oDB)
	: CStatTypes(oDB, TXT("FixStatTypes"))
{
	// Add the pre-defined statistics.
	AddPredefined(TXT("Goals For"));
	AddPredefined(TXT("Goals Against"));
}

#endif //FIXSTATTYPES_HPP
