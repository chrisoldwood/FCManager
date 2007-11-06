/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		STATS.HPP
** COMPONENT:	The Application.
** DESCRIPTION:	The CStats class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef STATS_HPP
#define STATS_HPP

#if _MSC_VER > 1000
#pragma once
#endif

#include <MDBL/Table.hpp>

// Forward declaration.
class CStatTypes;

/******************************************************************************
** 
** This is the table used to store all statistics.
**
*******************************************************************************
*/

class CStats : public CTable
{
public:
	//
	// Constructors/Destructor.
	//
	CStats(CMDB& oDB, const char* pszName, CStatTypes& oTypes);
	~CStats();
	
	//
	// Column indices.
	//
	enum
	{
		OWNER_ID,
		DATE,
		TYPE_ID,
		VALUE,
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

#endif //STATS_HPP
