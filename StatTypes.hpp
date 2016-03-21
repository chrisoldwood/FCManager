/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		STATTYPES.HPP
** COMPONENT:	The Application.
** DESCRIPTION:	The CStatTypes class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef STATTYPES_HPP
#define STATTYPES_HPP

#if _MSC_VER > 1000
#pragma once
#endif

#include <MDBL/Table.hpp>

/******************************************************************************
** 
** This is the table used to store all statistic types.
**
*******************************************************************************
*/

class CStatTypes : public CTable
{
public:
	//
	// Constructors/Destructor.
	//
	CStatTypes(const tchar* pszName);
	~CStatTypes();
	
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
	// Methods (overriden).
	//
	virtual CRow& CreateRow();

protected:
	//
	// Internal methods.
	//
	void AddPredefined(const tchar* pszName);
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

#endif //STATTYPES_HPP
