/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		ACCOUNTSVIEW.HPP
** COMPONENT:	The Application.
** DESCRIPTION:	The CAccountsView class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef ACCOUNTSVIEW_HPP
#define ACCOUNTSVIEW_HPP

/******************************************************************************
** 
** This is the data view used to display and edit the clubs accounts.
**
*******************************************************************************
*/

class CAccountsView : public CGridViewDlg
{
public:
	//
	// Constructors/Destructor.
	//
	CAccountsView(CFCMDoc& rDoc);
	
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
	// The grid columns.
	enum
	{
		NAME,
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

#endif //ACCOUNTSVIEW_HPP
