/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		PRINTVIEWDLG.CPP
** COMPONENT:	The Application.
** DESCRIPTION:	CPrintViewDlg class definition.
**
*******************************************************************************
*/

#include "AppHeaders.hpp"
#include "PrintViewDlg.hpp"

/******************************************************************************
** Method:		Default constructor.
**
** Description:	.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

CPrintViewDlg::CPrintViewDlg(const CString& strViewName)
	: CDialog(IDD_PRINT_VIEW)
	, m_strViewName(strViewName)
{
	DEFINE_CTRL_TABLE
		CTRL(IDC_PRINTER,	&m_txtPrinter)
		CTRL(IDC_PORT,		&m_txtPort)
		CTRL(IDC_COLUMNS,	&m_lvColumns)
	END_CTRL_TABLE

	DEFINE_CTRLMSG_TABLE
		CMD_CTRLMSG(IDC_SELECT,		BN_CLICKED,	OnSelect  )
		CMD_CTRLMSG(IDC_MOVE_UP,	BN_CLICKED,	OnMoveUp  )
		CMD_CTRLMSG(IDC_MOVE_DOWN,	BN_CLICKED,	OnMoveDown)
	END_CTRLMSG_TABLE
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

void CPrintViewDlg::OnInitDialog()
{
	CString strTitle;

	// Set the dialogs title.
	strTitle.Format("Print %s", m_strViewName);
	Title(strTitle);

	// Show printer details.
	m_txtPrinter.Text(App.m_oPrinter.m_strName);
	m_txtPort.Text(App.m_oPrinter.m_strPort);

	// Add the single column.
	m_lvColumns.InsertColumn(0, "Column Name", 100);

	// Add the columns.
	m_lvColumns.AppendItem("Name");
	m_lvColumns.AppendItem("Phone #1");
	m_lvColumns.AppendItem("Phone #2");
	m_lvColumns.AppendItem("Registered?");
	m_lvColumns.AppendItem("Senior?");

	m_lvColumns.Select(0);
}

/******************************************************************************
** Method:		OnOk()
**
** Description:	Check if the user can okay the dialog.
**
** Parameters:	None.
**
** Returns:		true or false.
**
*******************************************************************************
*/

bool CPrintViewDlg::OnOk()
{
	// Check printer selection.
	if ( (App.m_oPrinter.m_strName   == "")
	  || (App.m_oPrinter.m_strDriver == "") 
	  || (App.m_oPrinter.m_strPort   == "") )
	{
		AlertMsg("You must select a printer.");
		return false;
	}

	int nColumns = m_lvColumns.ItemCount();
	int nChecked = 0;

	// Count how many columns to print.
	for (int i = 0; i < nColumns; i++)
	{
		if (m_lvColumns.IsItemChecked(i))
			nChecked++;
	}

	// Must have at least 1.
	if (nChecked < 1)
	{
		AlertMsg("You must include at least one column.");
		return false;
	}

	return true;
}

/******************************************************************************
** Method:		OnSelect()
**
** Description:	Show the print dialog to select a printer.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CPrintViewDlg::OnSelect()
{
	CBusyCursor BusyCursor;

	// Select a new printer.
	if (App.m_oPrinter.Select(*this))
	{
		// Update printer details.
		m_txtPrinter.Text(App.m_oPrinter.m_strName);
		m_txtPort.Text(App.m_oPrinter.m_strPort);
	}
}

/******************************************************************************
** Methods:		OnMoveUp()
**				OnMoveDown()
**
** Description:	Move the column up or down the ordering in the list view.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CPrintViewDlg::OnMoveUp()
{
	// Ignore if no selection.
	if (!m_lvColumns.IsSelection())
		return;

	int nSel = m_lvColumns.Selected();

	// If first, can't move up.
	if (nSel <= 0)
		return;

	// Get the item details.
	CString strItem  = m_lvColumns.ItemText(nSel, 0);
	LPARAM  lData    = m_lvColumns.ItemData(nSel);
	bool	bChecked = m_lvColumns.IsItemChecked(nSel);

	// Delete and re-add.
	m_lvColumns.DeleteItem(nSel);
	m_lvColumns.InsertItem(nSel-1, strItem, lData, -1);
	m_lvColumns.ItemCheck(nSel-1, bChecked);
	m_lvColumns.Select(nSel-1);
}

void CPrintViewDlg::OnMoveDown()
{
	// Ignore if no selection.
	if (!m_lvColumns.IsSelection())
		return;

	int nSel = m_lvColumns.Selected();

	// If last, can't move down.
	if (nSel >= (m_lvColumns.ItemCount() - 1))
		return;

	// Get the item details.
	CString strItem  = m_lvColumns.ItemText(nSel, 0);
	LPARAM  lData    = m_lvColumns.ItemData(nSel);
	bool	bChecked = m_lvColumns.IsItemChecked(nSel);

	// Delete and re-add.
	m_lvColumns.DeleteItem(nSel);
	m_lvColumns.InsertItem(nSel+1, strItem, lData, -1);
	m_lvColumns.ItemCheck(nSel+1, bChecked);
	m_lvColumns.Select(nSel+1);
}
