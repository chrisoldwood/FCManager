/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		TMPEXPS.HPP
** COMPONENT:	The Application.
** DESCRIPTION:	The CTmpExps class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef TMPEXPS_HPP
#define TMPEXPS_HPP

/******************************************************************************
** 
** This is a temporay table for holding the expenses during editing.
**
*******************************************************************************
*/

class CTmpExps : public CTable
{
public:
	//
	// Constructors/Destructor.
	//
	CTmpExps(CMDB& oDB, CExpenseTypes& oTypes);
	~CTmpExps();
	
	//
	// Column indices.
	//
	enum
	{
		ITEM_ID,
		TYPE_ID,
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

#endif //TMPEXPS_HPP
