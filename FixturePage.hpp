/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		FIXTUREPAGE.HPP
** COMPONENT:	The Application.
** DESCRIPTION:	The CFixturePage class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef FIXTUREPAGE_HPP
#define FIXTUREPAGE_HPP

#if _MSC_VER > 1000
#pragma once
#endif

#include <WCL/CommonUI.hpp>

/******************************************************************************
** 
** This is the property page used to display the fixture details.
**
*******************************************************************************
*/

class CFixturePage : public CPropertyPage
{
public:
	//
	// Constructors/Destructor.
	//
	CFixturePage(CFCMDB& oDB, CRow& oRow);

protected:
	//
	// Members.
	//
	CFCMDB&			m_oDB;
	CRow&			m_oRow;

	CDateTimePicker	m_dtpDate;
	CComboBox		m_cbType;
	CComboBox		m_cbHomeTeam;
	CComboBox		m_cbAwayTeam;
	CComboBox		m_cbReferee;
	CEditBox		m_ebResult;

	//
	// Message processors.
	//
	virtual void OnInitDialog();
	virtual bool OnOk();
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

#endif //FIXTUREPAGE_HPP
