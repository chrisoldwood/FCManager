/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		STATTYPEDLG.HPP
** COMPONENT:	The Application.
** DESCRIPTION:	The CStatTypeDlg class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef STATTYPEDLG_HPP
#define STATTYPEDLG_HPP

#if _MSC_VER > 1000
#pragma once
#endif

#include <WCL/CommonUI.hpp>

/******************************************************************************
** 
** This dialog is used to add/edit a statistic type.
**
*******************************************************************************
*/

class CStatTypeDlg : public CDialog
{
public:
	//
	// Constructors/Destructor.
	//
	CStatTypeDlg(CRow& oRow);
	
protected:
	//
	// Members.
	//
	CRow&		m_oRow;

	CEditBox	m_ebName;
	
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

#endif //STATTYPEDLG_HPP
