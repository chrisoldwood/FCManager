/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		FCMAPP.CPP
** COMPONENT:	The Application.
** DESCRIPTION:	The CFCMApp class definition.
**
*******************************************************************************
*/

#include "AppHeaders.hpp"

/******************************************************************************
**
** Global variables.
**
*******************************************************************************
*/

// "The" application object.
CFCMApp App;

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
	: CSDIApp(m_AppWnd, m_AppCmds)
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
	m_strTitle = "F.C. Manager";

	// Load the toolbar bitmap.
	m_rCmdControl.CmdBitmap().LoadRsc(IDR_APPTOOLBAR);

	// Set the .INI file path.
	m_IniFile.m_Path  = CPath::AppDir();
	m_IniFile.m_Path += "FCManager.ini";

	// Load the MRUList.
	m_MRUList.Load(m_IniFile);

	// Create the main window.
	if (!m_AppWnd.Create())
		return false;

	// Show it.
	m_AppWnd.Show(m_iCmdShow);

	// Initialise UI.
	m_AppCmds.UpdateUI();

	return true;
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
	// Save the MRUList.
	m_MRUList.Save(m_IniFile);

	return true;
}

/******************************************************************************
** Method:		MakeFullName()
**
** Description:	Helper function to create a persons full name from two columns
**				in a row.
**
** Parameters:	rRow		The row data.
**				nForename	The column containing the Forename.
**				nSurname	The column containing the Surname.
**				bReverse	Supply surname then forename?
**
** Returns:		true or false.
**
*******************************************************************************
*/

CString CFCMApp::MakeFullName(CRow& rRow, int nForename, int nSurname, bool bReverse)
{
	const char* pszForename = rRow[nForename];
	const char* pszSurname  = rRow[nSurname];

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
		strFullName += ", ";
		strFullName += pszForename;
	}

	return strFullName;
}
