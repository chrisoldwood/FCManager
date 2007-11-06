/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		CLUBDETAILS.HPP
** COMPONENT:	The Application.
** DESCRIPTION:	The CClubDetails class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef CLUBDETAILS_HPP
#define CLUBDETAILS_HPP

#if _MSC_VER > 1000
#pragma once
#endif

#include <MDBL/Table.hpp>

/******************************************************************************
** 
** The table used to store the club details.
** NB: The table only contains 1 row.
**
*******************************************************************************
*/

class CClubDetails : public CTable
{
public:
	//
	// Constructors/Destructor.
	//
	CClubDetails(CMDB& oDB);
	~CClubDetails();
	
	//
	// Column indices.
	//
	enum
	{
		NAME,
		SEASON,
		LEAGUE,
	};

	//
	// Column lengths.
	//
	enum
	{
		NAME_LEN   = 50,
		SEASON_LEN = 10,
		LEAGUE_LEN = 50,
	};

	//
	// Methods (overriden).
	//
	virtual CRow& CreateRow();
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

#endif //CLUBDETAILS_HPP
