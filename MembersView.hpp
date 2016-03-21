/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		MEMBERSVIEW.HPP
** COMPONENT:	The Application.
** DESCRIPTION:	The CMembersView class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef MEMBERSVIEW_HPP
#define MEMBERSVIEW_HPP

#if _MSC_VER > 1000
#pragma once
#endif

#include <WCL/CommonUI.hpp>
#include "GridViewDlg.hpp"
#include <Legacy/TArray.hpp>
#include "Members.hpp"

/******************************************************************************
** 
** This is the data view used to display the club members.
**
*******************************************************************************
*/

class CMembersView : public CGridViewDlg
{
public:
	//
	// Constructors/Destructor.
	//
	CMembersView(CFCMDoc& rDoc);

	//
	// Methods (Overriden from base class).
	//
	virtual void OnUIUpdate();

	//
	// Commands.
	//
	virtual void OnAdd();
	virtual void OnEdit();
	virtual void OnDelete();
	virtual void OnDeleteAll();
	virtual void OnPrint();
	virtual void OnImport();
	virtual void OnExport();
	virtual void OnMiscCmd1();

	void RefreshRows(const CMembers::RowList& aoRows);

protected:
	//
	// Members.
	//

	// The grid columns.
	enum
	{
		NAME,
		PHONE_ONE,
		PHONE_TWO,
		IS_REGISTERED,
		IS_SENIOR,
		IS_AVAILABLE,
		BALANCE,

		NUM_COLUMNS
	};

	static GridColumn Columns[NUM_COLUMNS];

	//
	// Overriden data methods.
	//
	virtual CString GetCellData(size_t nColumn, CRow& oRow, size_t nField);
	virtual int     CompareRows(CRow& oRow1, CRow& oRow2);
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

#endif //MEMBERSVIEW_HPP
