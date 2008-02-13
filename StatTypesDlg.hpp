/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		STATTYPESDLG.HPP
** COMPONENT:	The Application.
** DESCRIPTION:	The CStatTypesDlg class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef STATTYPESDLG_HPP
#define STATTYPESDLG_HPP

#if _MSC_VER > 1000
#pragma once
#endif

#include <WCL/CommonUI.hpp>

// Forward declarations.
class CStatTypes;

/******************************************************************************
** 
** This dialog is used to maintain the statistic types.
**
*******************************************************************************
*/

class CStatTypesDlg : public CDialog
{
public:
	//
	// Constructors/Destructor.
	//
	CStatTypesDlg(const CString& strType, CStatTypes& oTypes, CValueSet& oUsed);
	
protected:
	//
	// Members.
	//
	CListBox		m_lbTypes;

	CString			m_strType;
	CStatTypes&		m_oTypes;
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

inline CRow& CStatTypesDlg::ItemData(size_t nItem)
{
	ASSERT(nItem < m_lbTypes.Count());

	return *(static_cast<CRow*>(m_lbTypes.ItemPtr(nItem)));
}

#endif //STATTYPESDLG_HPP
