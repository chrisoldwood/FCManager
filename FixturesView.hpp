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
	virtual void OnPrint();
	virtual void OnImport();
	virtual void OnExport();

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
		AWAY_TEAM,
		REFEREE,
		RESULT,
		NUM_COLUMNS
	};

	static GridColumn Columns[NUM_COLUMNS];

	//
	// Overidable data methods.
	//
	virtual CString GetCellData(int nColumn, CRow& oRow, int nField);
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

#endif //FIXTURESVIEW_HPP
