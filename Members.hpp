/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		MEMBERS.HPP
** COMPONENT:	The Application.
** DESCRIPTION:	The CMembers class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef MEMBERS_HPP
#define MEMBERS_HPP

#if _MSC_VER > 1000
#pragma once
#endif

#include <MDBL/Table.hpp>

// Forward declarations.
class CSubs;

/******************************************************************************
** 
** The table used to store the club members.
**
*******************************************************************************
*/

class CMembers : public CTable
{
public:
	//
	// Constructors/Destructor.
	//
	CMembers(CMDB& oDB);
	~CMembers();

	//
	// Column indices.
	//
	enum
	{
		ID,
		SURNAME,
		FORENAME,
		POSTAL_ADDRESS,
		STANDARD_PHONE,
		ALTERNATE_PHONE,
		EMAIL_ADDRESS,
		IS_REGISTERED,
		IS_SENIOR,
		USUAL_TEAM,
		USUAL_POSITION,
		IS_AVAILABLE,
		UNAVAIL_REASON,
		NOTES,
		BALANCE,
	};

	//
	// Column lengths.
	//
	enum
	{
		SURNAME_LEN  =  25,
		FORENAME_LEN =  25,
		POSTAL_LEN   = 100,
		PHONE_LEN    =  30,
		EMAIL_LEN    =  50,
		NOTES_LEN    = 512,
	};

	//
	// Persistance data.
	//
	enum
	{
		FILE_FORMAT  = 0x4D4D4346,		// "FCMM"
		FILE_VERSION = 0x00000A01,		// Alpha #1
	};

	//
	// Methods.
	//
	void UpdateBalances(CSubs& oSubs, TRefArray<CRow>& aoModified);

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

#endif //MEMBERS_HPP
