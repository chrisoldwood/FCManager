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
	virtual void OnPrint();

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
	virtual CString GetCellData(int nColumn, CRow& oRow, int nField);
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

#endif //REFEREESVIEW_HPP
