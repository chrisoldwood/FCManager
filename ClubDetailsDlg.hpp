/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		CLUBDETAILSDLG.HPP
** COMPONENT:	The Application.
** DESCRIPTION:	The CClubDetailsDlg class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef CLUBDETAILSDLG_HPP
#define CLUBDETAILSDLG_HPP

#if _MSC_VER > 1000
#pragma once
#endif

#include <WCL/CommonUI.hpp>

/******************************************************************************
** 
** This is the dialog used to edit the basic club details.
**
*******************************************************************************
*/

class CClubDetailsDlg : public CDialog
{
public:
	//
	// Constructors/Destructor.
	//
	CClubDetailsDlg(CRow& oMember);
	
	//
	// Members.
	//
	CRow&	m_oDetails;

protected:
	//
	// Members.
	//
	CEditBox	m_ebName;
	CEditBox	m_ebSeason;
	CEditBox	m_ebLeague;
	
	//
	// Message handlers.
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

#endif //CLUBDETAILSDLG_HPP
