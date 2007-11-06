/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		OPPSTATTYPES.HPP
** COMPONENT:	The Application.
** DESCRIPTION:	The COppStatTypes class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef OPPSTATTYPES_HPP
#define OPPSTATTYPES_HPP

#if _MSC_VER > 1000
#pragma once
#endif

/******************************************************************************
** 
** This is the table used to store all opponents statistic types.
**
*******************************************************************************
*/

class COppStatTypes : public CStatTypes
{
public:
	//
	// Constructors/Destructor.
	//
	COppStatTypes(CMDB& oDB);
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

inline COppStatTypes::COppStatTypes(CMDB& oDB)
	: CStatTypes(oDB, "OppStatTypes")
{
	// Add the pre-defined statistics.
}

#endif //OPPSTATTYPES_HPP
