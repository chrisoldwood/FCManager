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
		ID              = 0,
		SURNAME         = 1,
		FORENAME        = 2,
		POSTAL_ADDRESS  = 3,
		STANDARD_PHONE  = 4,
		ALTERNATE_PHONE = 5,
		EMAIL_ADDRESS   = 6,
		IS_REGISTERED   = 7,
		IS_SENIOR       = 8,
		USUAL_TEAM      = 9,
		USUAL_POSITION  = 10,
		NOTES           = 11,
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
		NOTES_LEN    = 100,
	};

	//
	// Persistance data.
	//
	enum
	{
		FILE_FORMAT  = 0x00000000,		// "MEMT"
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

#endif //MEMBERS_HPP
