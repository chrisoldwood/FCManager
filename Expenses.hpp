/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		EXPENSES.HPP
** COMPONENT:	The Application.
** DESCRIPTION:	The CExpenses class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef EXPENSES_HPP
#define EXPENSES_HPP

/******************************************************************************
** 
** This table is used to store the expenses for a balance sheet item.
**
*******************************************************************************
*/

class CExpenses : public CTable
{
public:
	//
	// Constructors/Destructor.
	//
	CExpenses(CMDB& oDB, CBalSheet& oBalSheet, CExpenseTypes& oTypes);
	~CExpenses();
	
	//
	// Column indices.
	//
	enum
	{
		ITEM_ID,
		TYPE_ID,
		PAID,
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

#endif //EXPENSES_HPP
