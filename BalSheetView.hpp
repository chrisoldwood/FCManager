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
	virtual CString GetCellData(int nColumn, CRow& oRow, int nField);
	virtual int     CompareRows(CRow& oRow1, CRow& oRow2);
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

#endif //BALSHEETVIEW_HPP
