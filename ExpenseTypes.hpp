/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		EXPENSETYPES.HPP
** COMPONENT:	The Application.
** DESCRIPTION:	The CExpenseTypes class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef EXPENSETYPES_HPP
#define EXPENSETYPES_HPP

#if _MSC_VER > 1000
#pragma once
#endif

#include <MDBL/Table.hpp>

/******************************************************************************
** 
** This table is used to store the type of expenses defined.
**
*******************************************************************************
*/

class CExpenseTypes : public CTable
{
public:
	//
	// Constructors/Destructor.
	//
	CExpenseTypes(CMDB& oDB);
	~CExpenseTypes();
	
	//
	// Column indices.
	//
	enum
	{
		ID,
		NAME,
		DEFAULT,
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
	void AddPredefined(const tchar* pszName, int nDefault);
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

#endif //EXPENSETYPES_HPP
