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
	CBalSheet(CMDB& oDB);
	~CBalSheet();
	
	//
	// Column indices.
	//
	enum
	{
		ID     = 0,
		NAME   = 1,
		DATE   = 2,
		CREDIT = 3,
		DEBIT  = 4,
		TOTAL  = 5,
		NOTES  = 6,
	};

	//
	// Column lengths.
	//
	enum
	{
		NAME_LEN  =  20,
		NOTES_LEN = 100,
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
