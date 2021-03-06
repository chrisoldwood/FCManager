/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		BALSHEETVIEW.HPP
** COMPONENT:	The Application.
** DESCRIPTION:	The CBalSheetView class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef BALSHEETVIEW_HPP
#define BALSHEETVIEW_HPP

#if _MSC_VER > 1000
#pragma once
#endif

#include <WCL/CommonUI.hpp>
#include "GridViewDlg.hpp"

/******************************************************************************
** 
** This is the data view used to display and edit the balance sheet.
**
*******************************************************************************
*/

class CBalSheetView : public CGridViewDlg
{
public:
	//
	// Constructors/Destructor.
	//
	CBalSheetView(CFCMDoc& rDoc);
	
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
	virtual void OnMiscCmd1();

protected:
	//
	// Members.
	//
	
	// The list view columns.
	enum
	{
		NAME,
		DATE,
		CREDIT,
		DEBIT,
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

#endif //BALSHEETVIEW_HPP
