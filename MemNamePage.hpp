/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		MEMNAMEPAGE.HPP
** COMPONENT:	The Application.
** DESCRIPTION:	The CMemNamePage class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef MEMNAMEPAGE_HPP
#define MEMNAMEPAGE_HPP

#include "NamePage.hpp"

/******************************************************************************
** 
** This is the property page used to display the members name and address.
**
*******************************************************************************
*/

class CMemNamePage : public CNamePage
{
public:
	//
	// Constructors/Destructor.
	//
	CMemNamePage(CRow& oRow);

protected:
	//
	// Members.
	//
	CRow&	m_oRow;

	//
	// Message processors.
	//
	virtual bool OnValidate();
	virtual bool OnOk();
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

#endif //MEMNAMEPAGE_HPP
