/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		OPPONENTSVIEW.HPP
** COMPONENT:	The Application.
** DESCRIPTION:	The COpponentsView class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef OPPONENTSVIEW_HPP
#define OPPONENTSVIEW_HPP

#if _MSC_VER > 1000
#pragma once
#endif

#include <WCL/CommonUI.hpp>
#include "GridViewDlg.hpp"

/******************************************************************************
** 
** This is the data view used to display the league opponents.
**
*******************************************************************************
*/

class COpponentsView : public CGridViewDlg
{
public:
	//
	// Constructors/Destructor.
	//
	COpponentsView(CFCMDoc& rDoc);
	
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
		GROUND,
		SECRETARY,
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

#endif //OPPONENTSVIEW_HPP
