/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		MEMSTATUSPAGE.HPP
** COMPONENT:	The Application.
** DESCRIPTION:	The CMemStatusPage class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef MEMSTATUSPAGE_HPP
#define MEMSTATUSPAGE_HPP

#if _MSC_VER > 1000
#pragma once
#endif

#include <WCL/CommonUI.hpp>

/******************************************************************************
** 
** This is the property page used to display the members status.
**
*******************************************************************************
*/

class CMemStatusPage : public CPropertyPage
{
public:
	//
	// Constructors/Destructor.
	//
	CMemStatusPage(CRow& oRow);
	
protected:
	//
	// Members.
	//
	CRow&		m_oRow;

	bool		m_bIsRegistered;
	bool		m_bIsSenior;
	int			m_nTeam;
	int			m_nPosition;
	bool		m_bIsAvailable;
	int			m_nReason;

	CCheckBox	m_ckIsRegistered;
	CCheckBox	m_ckIsSenior;
	CComboBox	m_cbTeam;
	CComboBox	m_cbPosition;
	CCheckBox	m_ckIsAvailable;
	CComboBox	m_cbReason;

	//
	// Message processors.
	//
	virtual void OnInitDialog();
	virtual bool OnValidate();
	virtual bool OnOk();
			void OnAvailable();
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

#endif //MEMSTATUSPAGE_HPP
