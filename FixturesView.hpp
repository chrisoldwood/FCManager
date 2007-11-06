/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		FIXTURESVIEW.HPP
** COMPONENT:	The Application.
** DESCRIPTION:	The CFixturesView class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef FIXTURESVIEW_HPP
#define FIXTURESVIEW_HPP

#if _MSC_VER > 1000
#pragma once
#endif

#include <WCL/CommonUI.hpp>
#include "GridViewDlg.hpp"

/******************************************************************************
** 
** This is the data view used to display the clubs fixtures.
**
*******************************************************************************
*/

class CFixturesView : public CGridViewDlg
{
public:
	//
	// Constructors/Destructor.
	//
	CFixturesView(CFCMDoc& rDoc);
	
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
		DATE,
		TYPE,
		HOME_TEAM,
		RESULT,
		AWAY_TEAM,
		REFEREE,
		NUM_COLUMNS
	};

	static GridColumn Columns[NUM_COLUMNS];

	//
	// Overidable data methods.
	//
	virtual CString GetCellData(int nColumn, CRow& oRow, int nField);
	virtual int     CompareRows(CRow& oRow1, CRow& oRow2);
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

#endif //FIXTURESVIEW_HPP
