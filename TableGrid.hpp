/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		TABLEGRID.HPP
** COMPONENT:	The Application.
** DESCRIPTION:	The CTableGrid class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef TABLEGRID_HPP
#define TABLEGRID_HPP


// Forward declarations.
class IRowHandler;

/******************************************************************************
** 
** This ListView derived class is used for displaying MDB tables.
**
*******************************************************************************
*/

class CTableGrid : public CListView
{
public:
	/////////////////////////////////////////////////////
	// 
	// The structure used to hold the column definitions.
	//
	/////////////////////////////////////////////////////

	struct Column
	{
		const char*	m_pszName;		// The name.
		int			m_nWidth;		// The width in pixels.
		int			m_nAlign;		// The alignment of the text.
		int			m_nField;		// The row field.
		const char*	m_pszFormat;	// The field format.
	};

	//
	// Constructors/Destructor.
	//
	CTableGrid(IRowHandler* pRowHandler = NULL);
	~CTableGrid();

	void  Columns(int nColumns, Column* pColumns);

	int   RowCount();
	CRow& Row(int nRow);

	void  AddRows  (CTable& oTable,  bool bReSort = true, int nSel = 0);
	void  AddRows  (CResultSet& oRS, bool bReSort = true, int nSel = 0);
	int   AddRow   (CRow& oRow,      bool bReSort = true, bool bSelect = true);
	int   UpdateRow(int nRow,        bool bReSort = true, bool bSelect = true);
	void  DeleteRow(int nRow);

	void  Sort();

protected:
	//
	// Members.
	//
	int				m_nColumns;
	Column*			m_pColumns;
	IRowHandler*	m_pRowHandler;

	//
	// Message processors.
	//
	virtual void OnCreate(const CRect& rcClient);

	//
	// Internal methods.
	//
	friend int  CALLBACK TableGridCmpRows(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);
	virtual int CompareRows(CRow& oRow1, CRow& oRow2);
	virtual CString FieldValue(int nColumn, CRow& oRow);
};

/******************************************************************************
** 
** This interface class is used to handle row events from the CTableGrid class.
**
*******************************************************************************
*/

class IRowHandler
{
public:
	virtual int     CompareRows(CRow& oRow1, CRow& oRow2) = 0;
	virtual CString RowFieldValue(CRow& oRow, int nField) = 0;
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

inline int CTableGrid::RowCount()
{
	return ItemCount();
}

inline CRow& CTableGrid::Row(int nRow)
{
	ASSERT((nRow >= 0) && (nRow < RowCount()));

	return *((CRow*)ItemPtr(nRow));
}

#endif //TABLEGRID_HPP
