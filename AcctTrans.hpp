/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		ACCTTRANS.HPP
** COMPONENT:	The Application.
** DESCRIPTION:	The CAcctTrans class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef ACCTTRANS_HPP
#define ACCTTRANS_HPP

#if _MSC_VER > 1000
#pragma once
#endif

#include <MDBL/Table.hpp>

/******************************************************************************
** 
** The table used to store the clubs accounts.
**
*******************************************************************************
*/

class CAcctTrans : public CTable
{
public:
	//
	// Constructors/Destructor.
	//
	CAcctTrans(CMDB& oDB);
	~CAcctTrans();

	//
	// Column indices.
	//
	enum
	{
		ID,
	};

	//
	// Column lengths.
	//
	enum
	{
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

#endif //ACCTTRANS_HPP
