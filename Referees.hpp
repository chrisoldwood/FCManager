/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		REFEREES.HPP
** COMPONENT:	The Application.
** DESCRIPTION:	The CReferees class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef REFEREES_HPP
#define REFEREES_HPP

/******************************************************************************
** 
** The table used to store the league referees.
**
*******************************************************************************
*/

class CReferees : public CTable
{
public:
	//
	// Constructors/Destructor.
	//
	CReferees(CMDB& oDB);
	~CReferees();
	
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
		NOTES           = 7,
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
		FILE_FORMAT  = 0x00000000,		// "REFT"
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

#endif //REFEREES_HPP
