/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		BALSHTTYPES.HPP
** COMPONENT:	The Application.
** DESCRIPTION:	The CBalShtTypes class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef BALSHTTYPES_HPP
#define BALSHTTYPES_HPP

#if _MSC_VER > 1000
#pragma once
#endif

#include <MDBL/Table.hpp>

/******************************************************************************
** 
** This is the table used to store the balance sheet item types.
**
*******************************************************************************
*/

class CBalShtTypes : public CTable
{
public:
	//
	// Constructors/Destructor.
	//
	CBalShtTypes(CMDB& oDB);
	~CBalShtTypes();
	
	//
	// Column indices.
	//
	enum
	{
		ID,
		NAME,
	};

	//
	// Column lengths.
	//
	enum
	{
		NAME_LEN = 50,
	};

	//
	// Predefined types.
	//
	enum
	{
		OTHER    = 1,
		MATCH    = 2,
		TRAINING = 3,
	};

	//
	// Methods (overriden).
	//
	virtual CRow& CreateRow();

protected:
	//
	// Internal methods.
	//
	void AddPredefined(const char* pszName);
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

#endif //BALSHTTYPES_HPP
