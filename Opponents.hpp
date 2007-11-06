/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		OPPONENTS.HPP
** COMPONENT:	The Application.
** DESCRIPTION:	The COpponents class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef OPPONENTS_HPP
#define OPPONENTS_HPP

#if _MSC_VER > 1000
#pragma once
#endif

#include <MDBL/Table.hpp>

/******************************************************************************
** 
** This class is used to hold the details of a league opponent (club).
**
*******************************************************************************
*/

class COpponents : public CTable
{
public:
	//
	// Constructors/Destructor.
	//
	COpponents(CMDB& oDB);
	~COpponents();
	
	//
	// Column indices.
	//
	enum
	{
		ID              =  0,
		CLUB_NAME       =  1,
		GROUND          =  2,
		STANDARD_CLRS   =  3,
		ALTERNATE_CLRS  =  4,
		SURNAME         =  5,
		FORENAME        =  6,
		POSTAL_ADDRESS  =  7,
		STANDARD_PHONE  =  8,
		ALTERNATE_PHONE =  9,
		EMAIL_ADDRESS   = 10,
		NOTES           = 11,
	};

	//
	// Column lengths.
	//
	enum
	{
		CLUB_NAME_LEN =  50,
		GROUND_LEN    =  50,
		COLOURS_LEN   =  25,
		SURNAME_LEN   =  25,
		FORENAME_LEN  =  25,
		POSTAL_LEN    = 100,
		PHONE_LEN     =  30,
		EMAIL_LEN     =  50,
		NOTES_LEN     = 512,
	};

	//
	// Persistance data.
	//
	enum
	{
		FILE_FORMAT  = 0x4F4D4346,		// "FCMO"
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

#endif //OPPONENTS_HPP
