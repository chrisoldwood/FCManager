/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		GRIDVIEWDLG.HPP
** COMPONENT:	The Application.
** DESCRIPTION:	The CGridViewDlg class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef GRIDVIEWDLG_HPP
#define GRIDVIEWDLG_HPP

/******************************************************************************
** 
** The structure used to hold the column definitions.
**
*******************************************************************************
*/

struct GridColumn
{
	const char*	m_pszName;		// The name.
	int			m_nWidth;		// The width in pixels (screen) / percentage (printer).
	int			m_nFormat;		// The alignment of the text.
	int			m_nField;		// The data field.
};

/******************************************************************************
** 
** The base class for all grid based views.
**
*******************************************************************************
*/

class CGridViewDlg : public CViewDlg
{
public:
	//
	// Constructors/Destructor.
	//
	CGridViewDlg(uint iRscID, CTable& oTable, int nColumns, GridColumn* pColumns);
	~CGridViewDlg();
	
	//
	// Methods (Overriden from base class).
	//
	virtual void OnCommand(uint iCmdID);
	virtual void OnUIUpdate();
	
	//
	// Commands.
	//
	virtual void OnAdd();
	virtual void OnEdit();
	virtual void OnDelete();
	virtual void OnPrint();
	virtual void OnImport();
	virtual void OnExport();

	//
	// Data methods.
	//
	CRow& Row(int n);
	int   AddRow(CRow& oRow);
	void  UpdateRow(int nGridRow);
	void  DeleteRow(int nGridRow);

protected:
	//
	// Members.
	//
	CTable&		m_oTable;
	CListView	m_lvGrid;
	int			m_nColumns;
	GridColumn*	m_pColumns;

	//
	// Message handlers.
	//
	virtual void    OnInitDialog();
	        LRESULT OnDblClick(NMHDR& rMsgHdr);

	//
	// Overidable data methods.
	//
	virtual CString GetCellData(int nColumn, CRow& oRow, int nField);

	//
	// View helpers.
	//
	void PrintView(const CString& strViewName, int nColumns, GridColumn* pColumns);
	void PrintCell(CDC& oDC, CRect rcCell, const char* pszText, int nAlignment, bool bBorder);
	bool ImportTable(uint32 iFormat, uint32 iVersion);
	bool ExportTable(uint32 iFormat, uint32 iVersion);
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

inline CRow& CGridViewDlg::Row(int n)
{
	return *((CRow*)m_lvGrid.ItemPtr(n));
}

#endif //GRIDVIEWDLG_HPP
