/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		REFNAMEPAGE.HPP
** COMPONENT:	The Application.
** DESCRIPTION:	The CRefNamePage class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef REFNAMEPAGE_HPP
#define REFNAMEPAGE_HPP

#include "NamePage.hpp"

/******************************************************************************
** 
** This is the property page used to display the referees name and address.
**
*******************************************************************************
*/

class CRefNamePage : public CNamePage
{
public:
	//
	// Constructors/Destructor.
	//
	CRefNamePage(CRow& oRow);

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

#endif //REFNAMEPAGE_HPP
