/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		PRINTVIEWDLG.CPP
** COMPONENT:	The Application.
** DESCRIPTION:	CPrintViewDlg class definition.
**
*******************************************************************************
*/

#include "Common.hpp"
#include "PrintViewDlg.hpp"
#include "FCMApp.hpp"
#include <WCL/BusyCursor.hpp>

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
		CMD_CTRLMSG(IDC_SELECT,		BN_CLICKED,	&CPrintViewDlg::OnSelect  )
		CMD_CTRLMSG(IDC_MOVE_UP,	BN_CLICKED,	&CPrintViewDlg::OnMoveUp  )
		CMD_CTRLMSG(IDC_MOVE_DOWN,	BN_CLICKED,	&CPrintViewDlg::OnMoveDown)
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

CPrintViewDlg::~CPrintViewDlg()
{
	Core::deleteAll(m_aoColumns);
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
	strTitle.Format(TXT("Print %s"), m_strViewName);
	Title(strTitle);

	// Show printer details.
	m_txtPrinter.Text(App.m_oPrinter.m_strName);
	m_txtPort.Text(App.m_oPrinter.m_strPort);

	// Add the single column.
	m_lvColumns.InsertColumn(0, TXT("Column Name"), 100);

	// Add the columns.
	for (size_t i = 0; i < m_aoColumns.size(); i++)
	{
		m_lvColumns.AppendItem(m_aoColumns[i]->m_pszName);
		m_lvColumns.ItemCheck(i, m_aoColumns[i]->m_bShow);
	}

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
	if ( (App.m_oPrinter.m_strName   == TXT(""))
	  || (App.m_oPrinter.m_strDriver == TXT("")) 
	  || (App.m_oPrinter.m_strPort   == TXT("")) )
	{
		AlertMsg(TXT("You must select a printer."));
		return false;
	}

	int nColumns = m_lvColumns.ItemCount();
	int nChecked = 0;

	// Count how many columns to print.
	for (int i = 0; i < nColumns; i++)
	{
		bool bChecked = m_lvColumns.IsItemChecked(i);

		m_aoColumns[i]->m_bShow = bChecked;

		if (bChecked)
			nChecked++;
	}

	// Must have at least 1.
	if (nChecked < 1)
	{
		AlertMsg(TXT("You must include at least one column."));
		return false;
	}

	// Remove unselected columns.
	for (int i = m_aoColumns.size()-1; i >= 0; i--)
	{
		if (!m_aoColumns[i]->m_bShow)
			Core::deleteAt(m_aoColumns, i);
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

	int nSel = m_lvColumns.Selection();

	// If first, can't move up.
	if (nSel <= 0)
		return;

	// Get the item details.
	CString strItem  = m_lvColumns.ItemText(nSel, 0);
	LPARAM  lData    = m_lvColumns.ItemData(nSel);
	bool	bChecked = m_lvColumns.IsItemChecked(nSel);

	// Delete and re-add.
	m_lvColumns.DeleteItem(nSel);
	m_lvColumns.InsertItem(nSel-1, strItem);
	m_lvColumns.ItemData(nSel-1, lData);
	m_lvColumns.ItemCheck(nSel-1, bChecked);
	m_lvColumns.Select(nSel-1);

	// Swap array items.
	std::swap(m_aoColumns[nSel], m_aoColumns[nSel-1]);
}

void CPrintViewDlg::OnMoveDown()
{
	// Ignore if no selection.
	if (!m_lvColumns.IsSelection())
		return;

	size_t nSel = m_lvColumns.Selection();

	// If last, can't move down.
	if (nSel >= (m_lvColumns.ItemCount() - 1))
		return;

	// Get the item details.
	CString strItem  = m_lvColumns.ItemText(nSel, 0);
	LPARAM  lData    = m_lvColumns.ItemData(nSel);
	bool	bChecked = m_lvColumns.IsItemChecked(nSel);

	// Delete and re-add.
	m_lvColumns.DeleteItem(nSel);
	m_lvColumns.InsertItem(nSel+1, strItem);
	m_lvColumns.ItemData(nSel+1, lData);
	m_lvColumns.ItemCheck(nSel+1, bChecked);
	m_lvColumns.Select(nSel+1);

	// Swap array items.
	std::swap(m_aoColumns[nSel], m_aoColumns[nSel+1]);
}
