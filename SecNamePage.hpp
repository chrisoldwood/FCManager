/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		SECNAMEPAGE.HPP
** COMPONENT:	The Application.
** DESCRIPTION:	The CSecNamePage class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef SECNAMEPAGE_HPP
#define SECNAMEPAGE_HPP

#if _MSC_VER > 1000
#pragma once
#endif

#include <WCL/CommonUI.hpp>
#include "NamePage.hpp"

/******************************************************************************
** 
** This is the property page used to display the secretarys name and address.
**
*******************************************************************************
*/

class CSecNamePage : public CNamePage
{
public:
	//
	// Constructors/Destructor.
	//
	CSecNamePage(CRow& oRow);

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

#endif //SECNAMEPAGE_HPP
