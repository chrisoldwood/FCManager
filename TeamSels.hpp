/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		TEAMSELS.HPP
** COMPONENT:	The Application.
** DESCRIPTION:	The CTeamSels class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef TEAMSELS_HPP
#define TEAMSELS_HPP

#if _MSC_VER > 1000
#pragma once
#endif

#include <MDBL/Table.hpp>

// Forward declarations.
class CMembers;

/******************************************************************************
** 
** The table used to store the team selections.
**
*******************************************************************************
*/

class CTeamSels : public CTable
{
public:
	//
	// Constructors/Destructor.
	//
	CTeamSels(CMDB& oDB, CMembers& oMembers);
	~CTeamSels();
	
	//
	// Column indices.
	//
	enum
	{
		ID,
		DATE,
		OPPONENTS,
		PLAYER_1,
		PLAYER_2,
		PLAYER_3,
		PLAYER_4,
		PLAYER_5,
		PLAYER_6,
		PLAYER_7,
		PLAYER_8,
		PLAYER_9,
		PLAYER_10,
		PLAYER_11,
		SUB_1,
		SUB_2,
		SUB_3,
		SUB_4,
		SUB_5,
		NOTES,
	};

	//
	// Column lengths.
	//
	enum
	{
		OPPONENTS_LEN =  50,
		NOTES_LEN     = 512,
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

#endif //TEAMSELS_HPP
