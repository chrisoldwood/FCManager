/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		ACCOUNTS.HPP
** COMPONENT:	The Application.
** DESCRIPTION:	The CAccounts class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef ACCOUNTS_HPP
#define ACCOUNTS_HPP

/******************************************************************************
** 
** The table used to store the clubs accounts.
**
*******************************************************************************
*/

class CAccounts : public CTable
{
public:
	//
	// Constructors/Destructor.
	//
	CAccounts(CMDB& oDB);
	~CAccounts();

	//
	// Column indices.
	//
	enum
	{
		ID,
		NAME,
		TYPE,
		BALANCE,
		NOTES,
	};

	//
	// Column lengths.
	//
	enum
	{
		NAME_LEN  = 50,
		NOTES_LEN = 512,
	};

	//
	// Account types.
	//
	enum
	{
		FIXED,
		VARIABLE,
	};

	//
	// Methods.
	//
	void UpdateTotalRow();

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

#endif //ACCOUNTS_HPP
