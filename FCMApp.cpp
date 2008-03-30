/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		FCMAPP.CPP
** COMPONENT:	The Application.
** DESCRIPTION:	The CFCMApp class definition.
**
*******************************************************************************
*/

#include "Common.hpp"
#include "FCMApp.hpp"
#include <stdio.h>
#include <time.h>
#include <tchar.h>

/******************************************************************************
**
** Global variables.
**
*******************************************************************************
*/

// "The" application object.
CFCMApp App;

/******************************************************************************
**
** Class constants.
**
*******************************************************************************
*/

#ifdef _DEBUG
const tchar* CFCMApp::VERSION = TXT("v1.0 Alpha #3 [Debug]");
#else
const tchar* CFCMApp::VERSION = TXT("v1.0 Alpha #3");
#endif

/******************************************************************************
** Method:		Constructor
**
** Description:	.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

CFCMApp::CFCMApp()
	: CSDIApp(m_AppWnd, m_AppCmds, ID_FILE_MRU_4-ID_FILE_MRU_1+1)
{
}

/******************************************************************************
** Method:		Destructor
**
** Description:	.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

CFCMApp::~CFCMApp()
{
}

/******************************************************************************
** Method:		OnOpen()
**
** Description:	Initialises the application.
**
** Parameters:	None.
**
** Returns:		true or false.
**
*******************************************************************************
*/

bool CFCMApp::OnOpen()
{
	// Set the app title.
	m_strTitle = TXT("F.C. Manager");

	// Load the toolbar bitmap.
	m_rCmdControl.CmdBitmap().LoadRsc(IDR_APPTOOLBAR);

	// Set the .INI file path.
	m_oIniFile.m_strPath = CPath::ApplicationDir() / TXT("FCManager.ini");

	// Load the MRUList and default settings.
	m_MRUList.Load(m_oIniFile);
	LoadDefaults();

	// Create the main window.
	if (!m_AppWnd.Create())
		return false;

	// Show it.
	if (ShowNormal() && !m_rcAppWnd.Empty())
		m_AppWnd.Move(m_rcAppWnd);

	m_AppWnd.Show(m_iCmdShow);

	// Initialise UI.
	m_AppCmds.UpdateUI();

	return CSDIApp::OnOpen();
}

/******************************************************************************
** Method:		OnClose()
**
** Description:	Terminate the application.
**
** Parameters:	None.
**
** Returns:		true or false.
**
*******************************************************************************
*/

bool CFCMApp::OnClose()
{
	CSDIApp::OnClose();

	// Save the MRUList and defaults.
	m_MRUList.Save(m_oIniFile);
	SaveDefaults();

	return true;
}

/******************************************************************************
** Method:		FormatName()
**
** Description:	Helper function to format a persons full name from two columns
**				in a row.
**
** Parameters:	rRow		The row data.
**				nForename	The column containing the Forename.
**				nSurname	The column containing the Surname.
**				bReverse	Supply surname then forename?
**
** Returns:		The string.
**
*******************************************************************************
*/

CString CFCMApp::FormatName(CRow& rRow, int nForename, int nSurname, bool bReverse) const
{
	const tchar* pszForename = rRow[nForename];
	const tchar* pszSurname  = rRow[nSurname];

	// If one part supplied return it.
	if (pszForename[0] == '\0')		return pszSurname;
	if (pszSurname[0]  == '\0')		return pszForename;

	CString	strFullName;

	// Forename/Surname?
	if (bReverse == false)
	{
		strFullName  = pszForename;
		strFullName += ' ';
		strFullName += pszSurname;
	}
	// Surname/Forename
	else
	{
		strFullName  = pszSurname;
		strFullName += TXT(", ");
		strFullName += pszForename;
	}

	return strFullName;
}

/******************************************************************************
** Method:		FormatMoney()
**
** Description:	Helper function to format a value from pence to pounds.
**
** Parameters:	rRow		The row data.
**				nColumn		The column containing the value.
**
** Returns:		The string.
**
*******************************************************************************
*/

CString CFCMApp::FormatMoney(CRow& rRow, int nColumn) const
{
	double dValue = rRow[nColumn].GetInt() / 100.0;
	tchar  szValue[10];

	_stprintf(szValue, TXT("%.2f"), dValue);

	return szValue;
}

/******************************************************************************
** Method:		FormatMoney()
**
** Description:	Helper function to format a value from pence to pounds.
**
** Parameters:	nAmount		The amount in pence.
**
** Returns:		The string.
**
*******************************************************************************
*/

CString CFCMApp::FormatMoney(int nAmount) const
{
	double dValue = nAmount / 100.0;
	tchar  szValue[10];

	_stprintf(szValue, TXT("%.2f"), dValue);

	return szValue;
}

/******************************************************************************
** Method:		FormatDate()
**
** Description:	Helper function to format a time_t as just a date.
**
** Parameters:	rRow		The row data.
**				nColumn		The column containing the value.
**
** Returns:		The string.
**
*******************************************************************************
*/

CString CFCMApp::FormatDate(CRow& rRow, int nColumn) const
{
	tchar szDate[20];

	time_t tDate = rRow[nColumn];

	_tcsftime(szDate, sizeof(szDate), TXT("%d/%m/%y"), localtime(&tDate));

	return szDate;
}

/******************************************************************************
** Method:		FormatDecimal()
**
** Description:	Helper function to format a double as a value.
**
** Parameters:	rRow		The row data.
**				nColumn		The column containing the value.
**				nDecDigits	The number of decimal places.
**
** Returns:		The string.
**
*******************************************************************************
*/

CString CFCMApp::FormatDecimal(CRow& rRow, int nColumn, int nDecDigits) const
{
	double dValue = rRow[nColumn].GetDouble();
	tchar  szValue[10];

	_stprintf(szValue, TXT("%.*f"), nDecDigits, dValue);

	return szValue;
}

/******************************************************************************
** Method:		LoadDefaults()
**
** Description:	Load the default settings.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CFCMApp::LoadDefaults()
{
	m_rcAppWnd.left   = m_oIniFile.ReadInt(TXT("Main"), TXT("Left"),   0);
	m_rcAppWnd.top    = m_oIniFile.ReadInt(TXT("Main"), TXT("Top"),    0);
	m_rcAppWnd.right  = m_oIniFile.ReadInt(TXT("Main"), TXT("Right"),  0);
	m_rcAppWnd.bottom = m_oIniFile.ReadInt(TXT("Main"), TXT("Bottom"), 0);

	m_dmTeamSelDlg.cx = m_oIniFile.ReadInt(TXT("TeamDlg"), TXT("Width"),  0);
	m_dmTeamSelDlg.cy = m_oIniFile.ReadInt(TXT("TeamDlg"), TXT("Height"), 0);
}

/******************************************************************************
** Method:		SaveDefaults()
**
** Description:	Save the default settings.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CFCMApp::SaveDefaults()
{
	m_oIniFile.WriteInt(TXT("Main"), TXT("Left"),   m_rcAppWnd.left);
	m_oIniFile.WriteInt(TXT("Main"), TXT("Top"),    m_rcAppWnd.top);
	m_oIniFile.WriteInt(TXT("Main"), TXT("Right"),  m_rcAppWnd.right);
	m_oIniFile.WriteInt(TXT("Main"), TXT("Bottom"), m_rcAppWnd.bottom);

	m_oIniFile.WriteInt(TXT("TeamDlg"), TXT("Width"),  m_dmTeamSelDlg.cx);
	m_oIniFile.WriteInt(TXT("TeamDlg"), TXT("Height"), m_dmTeamSelDlg.cy);
}
