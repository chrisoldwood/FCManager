/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		REFEREESVIEW.HPP
** COMPONENT:	The Application.
** DESCRIPTION:	The CRefereesView class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef REFEREESVIEW_HPP
#define REFEREESVIEW_HPP

#if _MSC_VER > 1000
#pragma once
#endif

#include <WCL/CommonUI.hpp>
#include "GridViewDlg.hpp"

/******************************************************************************
** 
** This is the data view used to display and edit the league referees.
**
*******************************************************************************
*/

class CRefereesView : public CGridViewDlg
{
public:
	//
	// Constructors/Destructor.
	//
	CRefereesView(CFCMDoc& rDoc);
	
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

protected:
	//
	// Members.
	//
	
	// The list view columns.
	enum
	{
		NAME,
		PHONE_ONE,
		PHONE_TWO,
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

#endif //REFEREESVIEW_HPP
