/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		TMPSTATS.HPP
** COMPONENT:	The Application.
** DESCRIPTION:	The CTmpStats class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef TMPSTATS_HPP
#define TMPSTATS_HPP

/******************************************************************************
** 
** This is the table used to temporarily store the statistics for an item.
**
*******************************************************************************
*/

class CTmpStats : public CTable
{
public:
	//
	// Constructors/Destructor.
	//
	CTmpStats(CMDB& oDB, CStatTypes& oTypes);
	~CTmpStats();
	
	//
	// Column indices.
	//
	enum
	{
		OWNER_ID,
		DATE,
		TYPE_ID,
		VALUE,
		NAME,
	};

	//
	// Column lengths.
	//
	enum
	{
		NAME_LEN = CStatTypes::NAME_LEN,
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

#endif //TMPSTATS_HPP
