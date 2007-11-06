/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		EXPENSETYPEDLG.HPP
** COMPONENT:	The Application.
** DESCRIPTION:	The CExpenseTypeDlg class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef EXPENSETYPEDLG_HPP
#define EXPENSETYPEDLG_HPP

#if _MSC_VER > 1000
#pragma once
#endif

#include <WCL/CommonUI.hpp>

/******************************************************************************
** 
** This dialog is used to add/edit an expense type.
**
*******************************************************************************
*/

class CExpenseTypeDlg : public CDialog
{
public:
	//
	// Constructors/Destructor.
	//
	CExpenseTypeDlg(CRow& oRow);
	
protected:
	//
	// Members.
	//
	CRow&		m_oRow;

	CEditBox	m_ebName;
	CDecimalBox	m_ebDefault;
	
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

#endif //EXPENSETYPEDLG_HPP
