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

	// The grid columns.
	enum
	{
		NAME,
		PHONE_ONE,
		PHONE_TWO,
		IS_REGISTERED,
		IS_SENIOR,
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

#endif //MEMBERSVIEW_HPP
