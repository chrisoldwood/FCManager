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
	: CStatTypes(oDB, "MemStatTypes")
{
	// Add the pre-defined statistics.
	AddPredefined("Played");
	AddPredefined("Trained");
	AddPredefined("Goals");
	AddPredefined("Own Goals");
	AddPredefined("Bookings");
	AddPredefined("Dismisals");
	AddPredefined("Substitutions");
	AddPredefined("Man o/t Match");
}

#endif //MEMSTATTYPES_HPP
