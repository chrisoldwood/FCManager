/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		GRIDVIEWDLG.CPP
** COMPONENT:	The Application.
** DESCRIPTION:	CGridViewDlg class definition.
**
*******************************************************************************
*/

#include "AppHeaders.hpp"
#include "PrintViewDlg.hpp"

// The file extension for importing/exporting.
static char szExts[] = {	"Data Files (*.dat)\0*.dat\0"
							"All Files (*.*)\0*.*\0"
							"\0\0"							};

static char szDefExt[] = { "dat" };

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

CGridViewDlg::CGridViewDlg(uint iRscID, CTable& oTable, int nColumns, GridColumn* pColumns)
	: CViewDlg(iRscID)
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
		NFY_CTRLMSG(IDC_GRID, NM_DBLCLK, OnDblClick)
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
	// Setup the grid columns.
	for (int c = 0; c < m_nColumns; c++)
		m_lvGrid.InsertColumn(c, m_pColumns[c].m_pszName, m_pColumns[c].m_nWidth, m_pColumns[c].m_nFormat);

	// Fill the grid with data.
	for (int r = 0; r < m_oTable.RowCount(); r++)
		AddRow(m_oTable[r]);

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
		case ID_OPTIONS_ADD:	OnAdd();		break;
		case ID_OPTIONS_EDIT:	OnEdit();		break;
		case ID_OPTIONS_DELETE:	OnDelete();		break;
		case ID_OPTIONS_PRINT:	OnPrint();		break;
		case ID_OPTIONS_IMPORT:	OnImport();		break;
		case ID_OPTIONS_EXPORT:	OnExport();		break;
		default:				ASSERT(false);	break;
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

	App.m_AppWnd.m_Menu.EnableCmd(ID_OPTIONS_ADD,    true);
	App.m_AppWnd.m_Menu.EnableCmd(ID_OPTIONS_EDIT,   bRows);
	App.m_AppWnd.m_Menu.EnableCmd(ID_OPTIONS_DELETE, bRows);
	App.m_AppWnd.m_Menu.EnableCmd(ID_OPTIONS_PRINT,  bRows);
	App.m_AppWnd.m_Menu.EnableCmd(ID_OPTIONS_IMPORT, true);
	App.m_AppWnd.m_Menu.EnableCmd(ID_OPTIONS_EXPORT, bRows);

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
	ASSERT(false);
}

void CGridViewDlg::OnEdit()
{
	ASSERT(false);
}

void CGridViewDlg::OnDelete()
{
	ASSERT(false);
}

void CGridViewDlg::OnPrint()
{
	ASSERT(false);
}

void CGridViewDlg::OnImport()
{
	ASSERT(false);
}

void CGridViewDlg::OnExport()
{
	ASSERT(false);
}

/******************************************************************************
** Method:		OnDblClick()
**
** Description:	Allow the user to edit the member.
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
	if (m_lvGrid.SelectionMark() != -1)
		OnEdit();

	return 0;
}

/******************************************************************************
** Method:		AddRow()
**
** Description:	Add a row to the grid.
**
** Parameters:	oRow	The row to add.
**
** Returns:		The grid row index.
**
*******************************************************************************
*/

int CGridViewDlg::AddRow(CRow& oRow)
{
	int nGridRow = m_lvGrid.AddItem(GetCellData(0, oRow, m_pColumns[0].m_nField), &oRow, -1);

	UpdateRow(nGridRow);

	return nGridRow;
}

/******************************************************************************
** Method:		UpdateRow()
**
** Description:	Update a row in the grid.
**
** Parameters:	nGridRow	The grid row to update.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CGridViewDlg::UpdateRow(int nGridRow)
{
	CRow& oRow = Row(nGridRow);

	// For all grid columns.
	for (int i = 0; i < m_nColumns; i++)
		m_lvGrid.ItemText(nGridRow, i, GetCellData(i, oRow, m_pColumns[i].m_nField));
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

void CGridViewDlg::DeleteRow(int nGridRow)
{
	m_lvGrid.DeleteItem(nGridRow);
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

CString CGridViewDlg::GetCellData(int nColumn, CRow& oRow, int nField)
{
	return oRow[nField];
}

/******************************************************************************
** Method:		PrintView()
**
** Description:	Prints the table associated with the view.
**
** Parameters:	strViewName		The name of the view.
**
** Returns:		true or false.
**
*******************************************************************************
*/

void CGridViewDlg::PrintView(const CString& strViewName)
{
	CPrintViewDlg Dlg(strViewName);

	// Query for the printer and print parameters.
	if (Dlg.RunModal(*this) == IDOK)
	{


	}
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
		oFile.Open(oPath, CStream::ReadOnly);

		uint32	iFileFormat;
		uint32  iFileVersion;

		// Read the format and version.
		oFile >> iFileFormat;
		oFile >> iFileVersion;

		// Check the format and version.
		if (iFileFormat != iFormat)
			throw CFileException(CStreamException::E_FORMAT_INVALID, oFile);

		if (iFileVersion != iVersion)
			throw CFileException(CStreamException::E_VERSION_INVALID, oFile);

		// Truncate the table and view.
		m_oTable.Truncate();
		m_lvGrid.DeleteAllItems();

		// Read the table data.
		m_oTable << oFile;

		oFile.Close();

		// Fill the grid with data.
		for (int r = 0; r < m_oTable.RowCount(); r++)
			AddRow(m_oTable[r]);

		// Select first item by default.
		if (m_lvGrid.ItemCount())
			m_lvGrid.Select(0);

		OnUIUpdate();
	}
	catch(CFileException& rException)
	{
		// Notify user.
		AlertMsg(rException.ErrorText());
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
		if ( (oPath.Exists()) && (QueryMsg("The file already exists:\n\n%s\n\nOverwrite?", oPath) != IDYES) )
			return false;

		// Open, write and close.
		oFile.Create(oPath);

		// Write the format and version.
		oFile << iFormat;
		oFile << iVersion;

		// Write the table data.
		m_oTable >> oFile;

		oFile.Close();
	}
	catch(CFileException& rException)
	{
		// Notify user.
		AlertMsg(rException.ErrorText());
		return false;
	}

	return true;
}
