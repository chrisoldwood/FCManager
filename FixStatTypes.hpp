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
	: CStatTypes(oDB, "FixStatTypes")
{
	// Add the pre-defined statistics.
	AddPredefined("Goals For");
	AddPredefined("Goals Against");
}

#endif //FIXSTATTYPES_HPP
