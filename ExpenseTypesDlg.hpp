/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		EXPENSETYPESDLG.HPP
** COMPONENT:	The Application.
** DESCRIPTION:	The CExpenseTypesDlg class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef EXPENSETYPESDLG_HPP
#define EXPENSETYPESDLG_HPP

#if _MSC_VER > 1000
#pragma once
#endif

#include <WCL/CommonUI.hpp>

// Forward declarations.
class CExpenseTypes;

/******************************************************************************
** 
** This dialog is used to maintain the expense types.
**
*******************************************************************************
*/

class CExpenseTypesDlg : public CDialog
{
public:
	//
	// Constructors/Destructor.
	//
	CExpenseTypesDlg(CExpenseTypes& oTypes, CValueSet& oUsed);
	
protected:
	//
	// Members.
	//
	CListBox		m_lbTypes;

	CExpenseTypes&	m_oTypes;
	CValueSet&		m_oUsed;
	
	//
	// Message processors.
	//
	virtual void OnInitDialog();
	virtual bool OnCancel();

	void OnAdd();
	void OnEdit();
	void OnDelete();
	void OnSelectType();

	//
	// Internal methods.
	//
	void  UpdateUI();
	CRow& ItemData(size_t nItem);
	bool  IsTypeInUse(int nID);
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

inline CRow& CExpenseTypesDlg::ItemData(size_t nItem)
{
	ASSERT(nItem < m_lbTypes.Count());

	return *(static_cast<CRow*>(m_lbTypes.ItemPtr(nItem)));
}

#endif //EXPENSETYPESDLG_HPP
