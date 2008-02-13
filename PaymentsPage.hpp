/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		PAYMENTSPAGE.HPP
** COMPONENT:	The Application.
** DESCRIPTION:	The CPaymentsPage class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef PAYMENTSPAGE_HPP
#define PAYMENTSPAGE_HPP

#if _MSC_VER > 1000
#pragma once
#endif

#include <WCL/CommonUI.hpp>
#include "TableGrid.hpp"
#include "TmpSubs.hpp"

/******************************************************************************
** 
** This is the property page used to display the members payments.
**
*******************************************************************************
*/

class CPaymentsPage : public CPropertyPage, public IRowHandler
{
public:
	//
	// Constructors/Destructor.
	//
	CPaymentsPage(CFCMDB& oDB, int nMemberID);
	
	//
	// Members.
	//

protected:
	//
	// Members.
	//
	CFCMDB&		m_oDB;
	int			m_nMemberID;
	CTmpSubs	m_oTmpSubs;

	CTableGrid 	m_lvGrid;
	
	// The list view columns.
	enum
	{
		DATE,
		ITEM,
		FEE,
		PAID,
		NUM_COLUMNS
	};

	static CTableGrid::Column Columns[NUM_COLUMNS];

	//
	// Message processors.
	//
	virtual void OnInitDialog();

	//
	// From IRowHandler.
	//
	virtual int     CompareRows(CRow& oRow1, CRow& oRow2);
	virtual CString RowFieldValue(CRow& oRow, size_t nField);
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

#endif //PAYMENTSPAGE_HPP
