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
	END_CTRL_TABLE

	DEFINE_CTRLMSG_TABLE
		CMD_CTRLMSG(IDC_SELECT,	BN_CLICKED,	OnSelect)
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
