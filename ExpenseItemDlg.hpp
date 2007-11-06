/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		EXPENSEITEMDLG.HPP
** COMPONENT:	The Application.
** DESCRIPTION:	The CExpenseItemDlg class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef EXPENSEITEMDLG_HPP
#define EXPENSEITEMDLG_HPP

#if _MSC_VER > 1000
#pragma once
#endif

#include <WCL/CommonUI.hpp>

// Forward declarations.
class CExpenseTypes;

/******************************************************************************
** 
** This dialog is used to add/edit an expense item.
**
*******************************************************************************
*/

class CExpenseItemDlg : public CDialog
{
public:
	//
	// Constructors/Destructor.
	//
	CExpenseItemDlg(CExpenseTypes& oTypes, CRow& oRow, bool bEditing);
	
	//
	// Members.
	//
	CRow&		m_oRow;
	
protected:
	//
	// Members.
	//
	bool			m_bEditing;

	CComboBox		m_cbTypes;
	CDecimalBox		m_ebPaid;

	CExpenseTypes&	m_oTypes;

	//
	// Message processors.
	//
	virtual void OnInitDialog();
	virtual bool OnOk();
			void OnSelectType();
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

#endif //EXPENSEITEMDLG_HPP
