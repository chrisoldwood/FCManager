/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		TEAMSELSVIEW.HPP
** COMPONENT:	The Application.
** DESCRIPTION:	The CTeamSelsView class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef TEAMSELSVIEW_HPP
#define TEAMSELSVIEW_HPP

/******************************************************************************
** 
** This is the data view used to display and edit team selections.
**
*******************************************************************************
*/

class CTeamSelsView : public CGridViewDlg
{
public:
	//
	// Constructors/Destructor.
	//
	CTeamSelsView(CFCMDoc& rDoc);
	
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
	virtual void OnPrint();

protected:
	//
	// Members.
	//

	// The grid columns.
	enum
	{
		DATE,
		OPPONENTS,
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

#endif //TEAMSELSVIEW_HPP
