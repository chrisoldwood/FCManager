/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		BALSHEET.HPP
** COMPONENT:	The Application.
** DESCRIPTION:	The CBalSheet class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef BALSHEET_HPP
#define BALSHEET_HPP

#if _MSC_VER > 1000
#pragma once
#endif

#include <MDBL/Table.hpp>

// Forward declarations.
class CBalShtTypes;

/******************************************************************************
** 
** This class is used to hold the balance sheet.
**
*******************************************************************************
*/

class CBalSheet : public CTable
{
public:
	//
	// Constructors/Destructor.
	//
	CBalSheet(CMDB& oDB, CBalShtTypes& oTypes);
	~CBalSheet();
	
	//
	// Column indices.
	//
	enum
	{
		ID,
		NAME,
		DATE,
		TYPE_ID,
		CREDIT_TYPE,
		CREDIT_TOTAL,
		DEBIT_TYPE,
		DEBIT_TOTAL,
		BALANCE,
		NOTES,
	};

	//
	// Column lengths.
	//
	enum
	{
		NAME_LEN  =  50,
		NOTES_LEN = 512,
	};

	//
	// Credit/Debit types.
	//
	enum
	{
		NONE,
		FIXED,
		VARIABLE,
	};

	//
	// Methods.
	//
	void UpdateTotalsRow();

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

#endif //BALSHEET_HPP
