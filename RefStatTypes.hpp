/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		REFSTATTYPES.HPP
** COMPONENT:	The Application.
** DESCRIPTION:	The CRefStatTypes class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef REFSTATTYPES_HPP
#define REFSTATTYPES_HPP

#if _MSC_VER > 1000
#pragma once
#endif

/******************************************************************************
** 
** This is the table used to store all referee statistic types.
**
*******************************************************************************
*/

class CRefStatTypes : public CStatTypes
{
public:
	//
	// Constructors/Destructor.
	//
	CRefStatTypes(CMDB& oDB);
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

inline CRefStatTypes::CRefStatTypes(CMDB& oDB)
	: CStatTypes(oDB, "RefStatTypes")
{
	// Add the pre-defined statistics.
}

#endif //REFSTATTYPES_HPP
