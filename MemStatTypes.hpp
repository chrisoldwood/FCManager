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
	AddPredefined("Scored");
	AddPredefined("Scored Own Goal");
	AddPredefined("Booked");
	AddPredefined("Dismissed");
	AddPredefined("Substituted");
	AddPredefined("Man of the Match");
}

#endif //MEMSTATTYPES_HPP
