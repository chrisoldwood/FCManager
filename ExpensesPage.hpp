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

/******************************************************************************
** 
** This dialog is used to enter/edit a balance sheet items details.
**
*******************************************************************************
*/

class CExpensesPage : public CPropertyPage
{
public:
	//
	// Constructors/Destructor.
	//
	CExpensesPage(CRow& oRow);
	
protected:
	//
	// Members.
	//
	CRow&			m_oRow;

	int				m_nType;
	int				m_nTotal;

	CRadioBtn		m_rbNoDebit;
	CRadioBtn		m_rbFxdDebit;
	CRadioBtn		m_rbVarDebit;
	CDecimalBox		m_ebDebit;
	CListBox		m_lbDebits;

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
