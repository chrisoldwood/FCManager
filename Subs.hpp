/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		SUBS.HPP
** COMPONENT:	The Application.
** DESCRIPTION:	The CSubs class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef SUBS_HPP
#define SUBS_HPP

/******************************************************************************
** 
** This class is used to hold the subs.
**
*******************************************************************************
*/

class CSubs : public CTable
{
public:
	//
	// Constructors/Destructor.
	//
	CSubs(CMDB& oDB, CBalSheet& oBalSheet, CMembers& oMembers);
	~CSubs();
	
	//
	// Column indices.
	//
	enum
	{
		ITEM_ID   = 0,
		MEMBER_ID = 1,
		FEE       = 2,
		PAID      = 3,
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

#endif //SUBS_HPP
