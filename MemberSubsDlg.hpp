/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		MEMBERSUBSDLG.HPP
** COMPONENT:	The Application.
** DESCRIPTION:	The CMemberSubsDlg class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef MEMBERSUBSDLG_HPP
#define MEMBERSUBSDLG_HPP

#if _MSC_VER > 1000
#pragma once
#endif

#include <WCL/CommonUI.hpp>
#include <vector>

// Forward declarations.
class CMembers;

/******************************************************************************
** 
** This dialog is used to add/edit a members subs.
**
*******************************************************************************
*/

class CMemberSubsDlg : public CDialog
{
public:
	//
	// Constructors/Destructor.
	//
	CMemberSubsDlg(CMembers& oMembers, std::vector<int>& oExclusions, CRow& oRow, bool bEditing);
	
	//
	// Members.
	//
	CRow&		m_oRow;
	
protected:
	//
	// Members.
	//
	bool			m_bEditing;

	CComboBox		m_cbMembers;
	CDecimalBox		m_ebFee;
	CDecimalBox		m_ebPaid;

	CMembers&		m_oMembers;
	std::vector<int>&	m_oExclusions;

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

#endif //MEMBERSUBSDLG_HPP
