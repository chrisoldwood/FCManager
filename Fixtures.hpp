/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		FIXTURES.HPP
** COMPONENT:	The Application.
** DESCRIPTION:	The CFixtures class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef FIXTURES_HPP
#define FIXTURES_HPP

#if _MSC_VER > 1000
#pragma once
#endif

#include <MDBL/Table.hpp>

/******************************************************************************
** 
** The table used to store the clubs fixtures.
**
*******************************************************************************
*/

class CFixtures : public CTable
{
public:
	//
	// Constructors/Destructor.
	//
	CFixtures(CMDB& oDB);
	~CFixtures();
	
	//
	// Column indices.
	//
	enum
	{
		ID             =  0,
		DATE           =  1,
		TYPE           =  2,
		HOME_TEAM      =  3,
		AWAY_TEAM      =  4,
		REFEREE        =  5,
		RESULT         =  6,
		PITCH_CFMD     =  7,
		OPPONENTS_CFMD =  8,
		REFEREE_CFMD   =  9,
		NOTES          = 10,
	};

	//
	// Column lengths.
	//
	enum
	{
		TYPE_LEN   =  30,
		TEAM_LEN   =  50,
		NAME_LEN   =  50,
		RESULT_LEN =  30,
		NOTES_LEN  = 512,
	};

	//
	// Persistance data.
	//
	enum
	{
		FILE_FORMAT  = 0x584D4346,		// "FCMX"
		FILE_VERSION = 0x00000A01,		// Alpha #1
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

#endif //FIXTURES_HPP
