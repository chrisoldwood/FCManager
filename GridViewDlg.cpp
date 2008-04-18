/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		GRIDVIEWDLG.CPP
** COMPONENT:	The Application.
** DESCRIPTION:	CGridViewDlg class definition.
**
*******************************************************************************
*/

#include "Common.hpp"
#include "GridViewDlg.hpp"
#include "PrintViewDlg.hpp"
#include "FCMApp.hpp"
#include <WCL/PrinterDC.hpp>
#include <WCL/File.hpp>
#include <WCL/FileException.hpp>

// The file extension for importing/exporting.
static tchar szExts[] = {	TXT("Data Files (*.dat)\0*.dat\0")
							TXT("All Files (*.*)\0*.*\0")
							TXT("\0\0")							};

static tchar szDefExt[] = { TXT("dat") };

/******************************************************************************
** Method:		Constructor.
**
** Description:	.
**
** Parameters:	iRscID		The dialog resource ID.
**				oTable		The table containing the data.
**				nColumns	The number of columns in the grid.
**				pColumns	The grid column definitions.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

CGridViewDlg::CGridViewDlg(uint iRscID, CFCMDB& oDB, CTable& oTable, size_t nColumns, GridColumn* pColumns)
	: CViewDlg(iRscID)
	, m_oDB(oDB)
	, m_oTable(oTable)
	, m_nColumns(nColumns)
	, m_pColumns(pColumns)
{
	DEFINE_CTRL_TABLE
		CTRL(IDC_GRID, &m_lvGrid)
	END_CTRL_TABLE

	DEFINE_GRAVITY_TABLE
		CTRLGRAV(IDC_GRID, LEFT_EDGE, TOP_EDGE, RIGHT_EDGE, BOTTOM_EDGE)
	END_GRAVITY_TABLE

	DEFINE_CTRLMSG_TABLE
		NFY_CTRLMSG(IDC_GRID, NM_DBLCLK, &CGridViewDlg::OnDblClick)
	END_CTRLMSG_TABLE
}

/******************************************************************************
** Method:		Destructor.
**
** Description:	.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

CGridViewDlg::~CGridViewDlg()
{
}

/******************************************************************************
** Method:		OnInitDialog()
**
** Description:	Initialise the dialog.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CGridViewDlg::OnInitDialog()
{
	// Set the grid style.
	m_lvGrid.GridLines(true);
	m_lvGrid.FullRowSelect(true);

	// Setup the grid columns.
	for (size_t c = 0; c < m_nColumns; c++)
		m_lvGrid.InsertColumn(c, m_pColumns[c].m_pszName, m_pColumns[c].m_nWidth, m_pColumns[c].m_nFormat);

	// Fill the grid with data.
	for (size_t r = 0; r < m_oTable.RowCount(); r++)
		AddRow(m_oTable[r], false);

	SortGrid();

	// Select first item by default.
	if (m_lvGrid.ItemCount())
		m_lvGrid.Select(0);

	OnUIUpdate();
}

/******************************************************************************
** Method:		OnCommand()
**
** Description:	Executes the command.
**
** Parameters:	iCmdID		The command to execute.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CGridViewDlg::OnCommand(uint iCmdID)
{
	switch (iCmdID)
	{
		case ID_OPTIONS_ADD:		OnAdd();		break;
		case ID_OPTIONS_EDIT:		OnEdit();		break;
		case ID_OPTIONS_DELETE:		OnDelete();		break;
		case ID_OPTIONS_DELETEALL:	OnDeleteAll();	break;
		case ID_OPTIONS_PRINT:		OnPrint();		break;
		case ID_OPTIONS_IMPORT:		OnImport();		break;
		case ID_OPTIONS_EXPORT:		OnExport();		break;
		case ID_OPTIONS_MISC_1:		OnMiscCmd1();	break;
		case ID_OPTIONS_MISC_2:		OnMiscCmd2();	break;
		default:					ASSERT_FALSE();	break;
	}
}

/******************************************************************************
** Method:		OnUIUpdate()
**
** Description:	Updates the UI for the options menu.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CGridViewDlg::OnUIUpdate()
{
	bool bRows = (m_oTable.RowCount() != 0);

	App.m_AppWnd.m_Menu.EnableCmd(ID_OPTIONS_ADD,       true);
	App.m_AppWnd.m_Menu.EnableCmd(ID_OPTIONS_EDIT,      bRows);
	App.m_AppWnd.m_Menu.EnableCmd(ID_OPTIONS_DELETE,    bRows);
	App.m_AppWnd.m_Menu.EnableCmd(ID_OPTIONS_DELETEALL, bRows);
	App.m_AppWnd.m_Menu.EnableCmd(ID_OPTIONS_PRINT,     bRows);
	App.m_AppWnd.m_Menu.EnableCmd(ID_OPTIONS_IMPORT,    true);
	App.m_AppWnd.m_Menu.EnableCmd(ID_OPTIONS_EXPORT,    bRows);

	App.m_AppWnd.m_ToolBar.m_AddBtn.Enable(true);
	App.m_AppWnd.m_ToolBar.m_EditBtn.Enable(bRows);
	App.m_AppWnd.m_ToolBar.m_DeleteBtn.Enable(bRows);
	App.m_AppWnd.m_ToolBar.m_PrintBtn.Enable(bRows);
	App.m_AppWnd.m_ToolBar.m_ImportBtn.Enable(true);
	App.m_AppWnd.m_ToolBar.m_ExportBtn.Enable(bRows);
}

/******************************************************************************
** Method:		On"Command"()
**
** Description:	Default command handlers.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CGridViewDlg::OnAdd()
{
	ASSERT_FALSE();
}

void CGridViewDlg::OnEdit()
{
	ASSERT_FALSE();
}

void CGridViewDlg::OnDelete()
{
	ASSERT_FALSE();
}

void CGridViewDlg::OnDeleteAll()
{
	ASSERT_FALSE();
}

void CGridViewDlg::OnPrint()
{
	ASSERT_FALSE();
}

void CGridViewDlg::OnImport()
{
	ASSERT_FALSE();
}

void CGridViewDlg::OnExport()
{
	ASSERT_FALSE();
}

void CGridViewDlg::OnMiscCmd1()
{
	ASSERT_FALSE();
}

void CGridViewDlg::OnMiscCmd2()
{
	ASSERT_FALSE();
}

/******************************************************************************
** Method:		OnDblClick()
**
** Description:	Edit the row.
**
** Parameters:	rMsgHdr		The message details.
**
** Returns:		0.
**
*******************************************************************************
*/

LRESULT CGridViewDlg::OnDblClick(NMHDR&)
{
	// User double-clicked an item?
	if (m_lvGrid.IsSelection())
		OnEdit();

	return 0;
}

/******************************************************************************
** Method:		AddRow()
**
** Description:	Add a row to the grid.
**
** Parameters:	oRow		The row to add.
**				bReSort		Re-sort the grid after?
**
** Returns:		The grid row index.
**
*******************************************************************************
*/

size_t CGridViewDlg::AddRow(CRow& oRow, bool bReSort)
{
	size_t nGridRow = m_lvGrid.AppendItem(GetCellData(0, oRow, m_pColumns[0].m_nField));

	m_lvGrid.ItemPtr(nGridRow, &oRow);

	return UpdateRow(nGridRow, bReSort);
}

/******************************************************************************
** Method:		UpdateRow()
**
** Description:	Update a row in the grid.
**
** Parameters:	nGridRow	The grid row to update.
**				bReSort		Re-sort the grid after?
**
** Returns:		The row index, if resorted.
**
*******************************************************************************
*/

size_t CGridViewDlg::UpdateRow(size_t nGridRow, bool bReSort)
{
	CRow& oRow = Row(nGridRow);

	// For all grid columns.
	for (size_t i = 0; i < m_nColumns; i++)
		m_lvGrid.ItemText(nGridRow, i, GetCellData(i, oRow, m_pColumns[i].m_nField));

	if (bReSort)
	{
		SortGrid();
		nGridRow = m_lvGrid.FindItem(&oRow);
	}

	return nGridRow;
}

/******************************************************************************
** Method:		DeleteRow()
**
** Description:	Delete a row from the grid.
**
** Parameters:	nGridRow	The grid row to delete.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CGridViewDlg::DeleteRow(size_t nGridRow)
{
	m_lvGrid.DeleteItem(nGridRow);
}

/******************************************************************************
** Method:		DeleteAllRows()
**
** Description:	Delete all rows from the grid.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CGridViewDlg::DeleteAllRows()
{
	m_lvGrid.DeleteAllItems();
}

/******************************************************************************
** Method:		GetCellData()
**
** Description:	Gets the value for a cell.
**
** Parameters:	nColumn		The grid column.
**				oRow		The table row.
**				nField		The table row field.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

CString CGridViewDlg::GetCellData(size_t /*nColumn*/, CRow& oRow, size_t nField)
{
	return oRow[nField].GetString();
}

/******************************************************************************
** Method:		PrintView()
**
** Description:	Prints the table associated with the view.
**
** Parameters:	strViewName		The name of the view.
**				nColumns		The number of columns to print.
**				pColumns		The column definitions.
**
** Returns:		true or false.
**
*******************************************************************************
*/

void CGridViewDlg::PrintView(const CString& strViewName, size_t nColumns, GridColumn* pColumns)
{
	ASSERT(nColumns >  0);
	ASSERT(pColumns != NULL);

	CPrintViewDlg Dlg(strViewName);

	// Setup the printable columns.
	for (size_t i = 0; i < nColumns; i++)
		Dlg.m_aoColumns.Add(new GridColumn(pColumns[i]));

	// Query for the printer and print parameters.
	if (Dlg.RunModal(*this) == IDOK)
	{
		// Create the printer DC.
		CPrinterDC oDC(App.m_oPrinter);

		// Get printer attributes.
		CRect rcRect = oDC.PrintableArea();
		CSize dmFont = oDC.TextExtents(TXT("Wy"));

		// Calculate number of pages.
		// NB: Page always includes column headers.
		int nPageLines = rcRect.Height() / dmFont.cy;
		int nRows      = m_lvGrid.ItemCount();
		int nRowsPage  = nPageLines - 1;
		int nPages     = nRows / nRowsPage;

		// Doesn't end on a page?
		if ((nRows % nRowsPage) != 0)
			nPages++;

		// Calculate column widths.
		TArray<int>	aiWidths;
		int			nPageWidth = rcRect.Width();
		int			nRatioWidth = 0;

		for (size_t i = 0; i < Dlg.m_aoColumns.Size(); i++)
			nRatioWidth += Dlg.m_aoColumns[i].m_nWidth;

		for (size_t i = 0; i < Dlg.m_aoColumns.Size(); i++)
			aiWidths.Add((nPageWidth * Dlg.m_aoColumns[i].m_nWidth) / nRatioWidth);

		// Create GDI objects.
		CBrush	oHdrBrush(BLACK_BRUSH);
		CPen	oRowBrush(NULL_BRUSH);
		CPen	oRowPen(BLACK_PEN);

		// Initialise DC.
//		oDC.BkMode(TRANSPARENT);

		// Start printing.
//		oDC.Start(strViewName);

		// For all pages.
		for (int p = 0; p < nPages; p++)
		{
//			oDC.StartPage();

			CRect rcCell;

			// Calculate first row rect.
			CRect rcRow  = rcRect;
			rcRow.bottom = rcRow.top + dmFont.cy;

			// Use inverse video for headers.
//			oDC.Fill(rcRow, oHdrBrush);
//			oDC.TextColour(RGB(255, 255, 255));

			// Initialise cell to first in row.
			rcCell = rcRow;
			rcCell.right  = rcRow.left;
			rcCell.bottom = rcCell.top + dmFont.cy;

			// Print column headers.
			for (size_t c = 0; c < Dlg.m_aoColumns.Size(); c++)
			{
				GridColumn& oColumn = Dlg.m_aoColumns[c];

				// Calculate cell border.
				rcCell.left  = rcCell.right;
				rcCell.right = rcCell.left + aiWidths[c];

				PrintCell(oDC, rcCell, oColumn.m_pszName, oColumn.m_nFormat, false);
			}

			// Calculate rows on this page.
			int nFirstRow = p * nRowsPage;
			int nLastRow  = nFirstRow + nRowsPage;

			// Adjust rows, if last page.
			if (nLastRow > nRows)
				nLastRow = nRows;

			// Use normal video for rows.
//			oDC.Select(oRowBrush);
//			oDC.Select(oRowPen);
//			oDC.TextColour(RGB(0, 0, 0));

			// Update row rect to start of next line.
			rcRow.top = rcRow.bottom;
			rcRow.bottom = rcRow.top + dmFont.cy;

			// For all rows on the page.
			for (int r = nFirstRow; r < nLastRow; r++)
			{
				CRow& oRow = *(static_cast<CRow*>(m_lvGrid.ItemPtr(r)));

				// Initialise cell to first in row.
				rcCell = rcRow;
				rcCell.right  = rcRow.left;
				rcCell.bottom = rcCell.top + dmFont.cy;

				// For all columns in the row.
				for (size_t c = 0; c < Dlg.m_aoColumns.Size(); c++)
				{
					GridColumn& oColumn = Dlg.m_aoColumns[c];

					// Calculate cell border.
					rcCell.left  = rcCell.right;
					rcCell.right = rcCell.left + aiWidths[c];

					PrintCell(oDC, rcCell, GetCellData(c, oRow, oColumn.m_nField), oColumn.m_nFormat, true);
				}

				// Update row cell to start of next row.
				rcRow.top = rcRow.bottom;
				rcRow.bottom = rcRow.top + dmFont.cy;
			}

//			oDC.EndPage();
		}

		// Done printing.
//		oDC.End();
	}
}

/******************************************************************************
** Method:		PrintCell()
**
** Description:	Prints a single row cell on the page, both text and border.
**				It assumes that the DC has already been setup.
**
** Parameters:	oDC			The DC to draw on.
**				rcCell		The cells bounding rect.
**				pszText		The cell text.
**				nAlignment	The text alignment (LVCFMT_*)
**				bBorder		Print the cell border.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CGridViewDlg::PrintCell(CDC& /*oDC*/, const CRect& /*rcCell*/, const tchar* pszText, uint nAlignment, bool /*bBorder*/)
{
	ASSERT( (nAlignment == LVCFMT_LEFT) || (nAlignment == LVCFMT_CENTER) || (nAlignment == LVCFMT_RIGHT) );

	// Draw the cell border.
//	if (bBorder)
//		oDC.Rectangle(rcCell);

	// No text to print?
	if ( (pszText == NULL) || (*pszText == '\0') )
		return;

	// Calculate DrawText flags.
	int nFormat = DT_SINGLELINE | DT_VCENTER;

	switch (nAlignment)
	{
		case LVCFMT_LEFT:	nFormat |= DT_LEFT;		break;
		case LVCFMT_CENTER:	nFormat |= DT_CENTER;	break;
		case LVCFMT_RIGHT:	nFormat |= DT_RIGHT;	break;
	}

	// Print it.
//	oDC.DrawText(rcCell, pszText, nFormat);
}

/******************************************************************************
** Method:		ImportTable()
**
** Description:	Imports data into the table.
**
** Parameters:	iFormat		The tables' format.
**				iVersion	The tables' version.
**
** Returns:		true or false.
**
*******************************************************************************
*/

bool CGridViewDlg::ImportTable(uint32 iFormat, uint32 iVersion)
{
	try
	{
		CPath oPath;

		// Select a filename.
		if (!oPath.Select(*this, CPath::OpenFile, szExts, szDefExt))
			return false;

		CFile oFile;

		// Open, read and close.
		oFile.Open(oPath, GENERIC_READ);

		uint32	iFileFormat;
		uint32  iFileVersion;

		// Read the format and version.
		oFile >> iFileFormat;
		oFile >> iFileVersion;

		// Check the format and version.
		if (iFileFormat != iFormat)
			throw CFileException(CStreamException::E_FORMAT_INVALID, oPath, ERROR_FILE_CORRUPT);

		if (iFileVersion != iVersion)
			throw CFileException(CStreamException::E_VERSION_INVALID, oPath, NO_ERROR);

		// Truncate the table and view.
		m_oTable.Truncate();
		m_lvGrid.DeleteAllItems();

		// Read the table data.
		m_oTable.Read(oFile);
		m_oTable.Modified(true);

		oFile.Close();

		// Fill the grid with data.
		for (size_t r = 0; r < m_oTable.RowCount(); r++)
			AddRow(m_oTable[r], false);

		SortGrid();

		// Select first item by default.
		if (m_lvGrid.ItemCount())
			m_lvGrid.Select(0);

		App.m_rCmdControl.UpdateUI();
	}
	catch(CFileException& rException)
	{
		// Notify user.
		AlertMsg(TXT("%s"), rException.ErrorText());
		return false;
	}

	return true;
}

/******************************************************************************
** Method:		ImportTable()
**
** Description:	Imports data into the table.
**
** Parameters:	iFormat		The tables' format.
**				iVersion	The tables' version.
**
** Returns:		true or false.
**
*******************************************************************************
*/

bool CGridViewDlg::ExportTable(uint32 iFormat, uint32 iVersion)
{
	try
	{
		CPath oPath;
		CFile oFile;

		// Select a filename.
		if (!oPath.Select(*this, CPath::SaveFile, szExts, szDefExt))
			return false;

		// Warn user if file exists.
		if ( (oPath.Exists()) && (QueryMsg(TXT("The file already exists:\n\n%s\n\nOverwrite?"), oPath) != IDYES) )
			return false;

		// Open, write and close.
		oFile.Create(oPath);

		// Write the format and version.
		oFile << iFormat;
		oFile << iVersion;

		// Write the table data.
		m_oTable.Write(oFile);

		oFile.Close();
	}
	catch(CFileException& rException)
	{
		// Notify user.
		AlertMsg(TXT("%s"), rException.ErrorText());
		return false;
	}

	return true;
}

/******************************************************************************
** Method:		SortGrid()
**
** Description:	Sorts the rows in the grid.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CGridViewDlg::SortGrid()
{
	m_lvGrid.Sort(GridCompareRows, (LPARAM)this);
}

/******************************************************************************
** Method:		GridCompareRows()
**
** Description:	ListView callback function to compare two rows.
**
** Parameters:	lParam1			Row 1.
**				lParam2			Row 2.
**				lParamSort		Dialog object.
**
** Returns:		As strcmp.
**
*******************************************************************************
*/

int CALLBACK GridCompareRows(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
	CGridViewDlg*	pDlg  = reinterpret_cast<CGridViewDlg*>(lParamSort);
	CRow*			pRow1 = reinterpret_cast<CRow*>(lParam1);
	CRow*			pRow2 = reinterpret_cast<CRow*>(lParam2);

	ASSERT(pDlg  != NULL);
	ASSERT(pRow1 != NULL);
	ASSERT(pRow2 != NULL);

	return pDlg->CompareRows(*pRow1, *pRow2);
}

/******************************************************************************
** Method:		CompareRows()
**
** Description:	View template method to compare two rows.
**
** Parameters:	oRow1			Row 1.
**				oRow2			Row 2.
**
** Returns:		As strcmp.
**
*******************************************************************************
*/

int CGridViewDlg::CompareRows(CRow& /*oRow1*/, CRow& /*oRow2*/)
{
	return 0;
}
