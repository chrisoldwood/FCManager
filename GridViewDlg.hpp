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

#if _MSC_VER > 1000
#pragma once
#endif

#include <WCL/CommonUI.hpp>
#include "ViewDlg.hpp"

/******************************************************************************
** 
** The structure used to hold the column definitions.
**
*******************************************************************************
*/

struct GridColumn
{
	const tchar*	m_pszName;		// The name.
	uint			m_nWidth;		// The width in pixels (screen) / percentage (printer).
	uint			m_nFormat;		// The alignment of the text.
	size_t			m_nField;		// The data field.
	bool			m_bShow;		// Display column.
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
	CGridViewDlg(uint iRscID, CFCMDB& oDB, CTable& oTable, size_t nColumns, GridColumn* pColumns);
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
	virtual void OnDeleteAll();
	virtual void OnPrint();
	virtual void OnImport();
	virtual void OnExport();
	virtual void OnMiscCmd1();
	virtual void OnMiscCmd2();

	//
	// Data methods.
	//
	CRow& Row(size_t n);
	size_t AddRow(CRow& oRow, bool bReSort);
	size_t UpdateRow(size_t nGridRow, bool bReSort);
	void  DeleteRow(size_t nGridRow);
	void  DeleteAllRows();
	size_t FindRow(CRow& oRow);

protected:
	//
	// Members.
	//
	CFCMDB&		m_oDB;
	CTable&		m_oTable;
	CListView	m_lvGrid;
	size_t		m_nColumns;
	GridColumn*	m_pColumns;

	//
	// Message handlers.
	//
	virtual void    OnInitDialog();
	        LRESULT OnDblClick(NMHDR& rMsgHdr);

	//
	// Overidable data methods.
	//
	virtual CString GetCellData(size_t nColumn, CRow& oRow, size_t nField);
	virtual int     CompareRows(CRow& oRow1, CRow& oRow2);

	//
	// View helpers.
	//
	void PrintView(const CString& strViewName, size_t nColumns, GridColumn* pColumns);
	void PrintCell(CDC& oDC, const CRect& rcCell, const tchar* pszText, uint nAlignment, bool bBorder);
	bool ImportTable(uint32 iFormat, uint32 iVersion);
	bool ExportTable(uint32 iFormat, uint32 iVersion);
	void SortGrid();

	//
	// Friends.
	//
	friend int CALLBACK GridCompareRows(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

inline CRow& CGridViewDlg::Row(size_t n)
{
	ASSERT(n < m_lvGrid.ItemCount());

	return *(static_cast<CRow*>(m_lvGrid.ItemPtr(n)));
}

inline size_t CGridViewDlg::FindRow(CRow& oRow)
{
	return m_lvGrid.FindItem(&oRow);
}

#endif //GRIDVIEWDLG_HPP
