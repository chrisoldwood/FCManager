/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		EXPENSESPAGE.HPP
** COMPONENT:	The Application.
** DESCRIPTION:	The CExpensesPage class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef EXPENSESPAGE_HPP
#define EXPENSESPAGE_HPP

#if _MSC_VER > 1000
#pragma once
#endif

#include <WCL/CommonUI.hpp>

// Forward declarations.
class CTmpExps;
class CExpenseTypes;

/******************************************************************************
** 
** This dialog is used to enter/edit balance sheet item expense details.
**
*******************************************************************************
*/

class CExpensesPage : public CPropertyPage
{
public:
	//
	// Constructors/Destructor.
	//
	CExpensesPage(CRow& oRow, CTmpExps& oTmpExps, CExpenseTypes& oTypes);
	
protected:
	//
	// Members.
	//
	CRow&			m_oRow;
	CTmpExps&		m_oTmpExps;
	CExpenseTypes&	m_oTypes;

	int				m_nType;
	int				m_nTotal;

	CRadioBtn		m_rbNoDebit;
	CRadioBtn		m_rbFxdDebit;
	CRadioBtn		m_rbVarDebit;
	CDecimalBox		m_ebDebit;
	CListView		m_lvDebits;

	//
	// Message processors.
	//
	virtual void OnInitDialog();
	virtual bool OnValidate();
	virtual bool OnOk();
	
	void OnNoDebit();
	void OnFxdDebit();
	void OnVarDebit();
	void OnAddDebit();
	void OnEditDebit();
	void OnDelDebit();
	LRESULT OnDblClick(NMHDR&);

	//
	// Internal methods.
	//
	void RefreshDebits();
	void UpdateDebitBtns();
	void UpdateDebitsTotal();
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

#endif //EXPENSESPAGE_HPP
