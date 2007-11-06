/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		TMPSUBS.HPP
** COMPONENT:	The Application.
** DESCRIPTION:	The CTmpSubs class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef TMPSUBS_HPP
#define TMPSUBS_HPP

#if _MSC_VER > 1000
#pragma once
#endif

#include <MDBL/Table.hpp>

// Forward declarations.
class CMembers;

/******************************************************************************
** 
** This class is used to temporarily store the subs for a member.
**
*******************************************************************************
*/

class CTmpSubs : public CTable
{
public:
	//
	// Constructors/Destructor.
	//
	CTmpSubs(CMDB& oDB, CMembers& oMembers, bool bSameMember);
	~CTmpSubs();
	
	//
	// Column indices.
	//
	enum
	{
		ITEM_ID,
		MEMBER_ID,
		FEE,
		PAID,
		ITEM_DATE,
		ITEM_NAME,
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

#endif //TMPSUBS_HPP
