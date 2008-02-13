/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		FCMCMDS.CPP
** COMPONENT:	The Application.
** DESCRIPTION:	CFCMCmds class definition.
**
*******************************************************************************
*/

#include "Common.hpp"
#include "FCMCmds.hpp"
#include "FCMApp.hpp"
#include "AboutDlg.hpp"
#include "ClubDetailsDlg.hpp"
#include <WCL/Clipboard.hpp>
#include <WCL/StreamException.hpp>
#include <WCL/File.hpp>

// The cmd ID range of the views.
const int ID_VIEW_FIRST = ID_VIEW_MEMBERS;
const int ID_VIEW_LAST  = ID_VIEW_REFEREES;

// Range of data view commands.
const int ID_VIEW_POPUP_CMD = ID_OPTIONS_POPUP;
const int ID_VIEW_FIRST_CMD = ID_OPTIONS_POPUP + 1;
const int ID_VIEW_LAST_CMD  = ID_OPTIONS_POPUP + 90;

// Start index of view specific icons.
const int VIEW_ICONS_BASE = 3;

// View specific hints offsets.
const int VIEW_HINTS_BASE  = 10000;
const int VIEW_HINTS_DELTA = 100;

// Range of MRU commands.
const int ID_MRU_FIRST = ID_FILE_MRU_1;
const int ID_MRU_LAST  = ID_FILE_MRU_4;

// Position of top level menu items.
const int FILE_MENU_POS    = 0;
const int VIEW_MENU_POS    = 1;
const int CLUB_MENU_POS    = 2;
const int OPTIONS_MENU_POS = 3;
const int REPORTS_MENU_POS = 4;
const int DEBUG_MENU_POS   = 5;
const int HELP_MENU_POS    = 6;

/******************************************************************************
** Method:		Constructor.
**
** Description:	.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

CFCMCmds::CFCMCmds()
{
	// Define the command table.
	DEFINE_CMD_TABLE
		// File menu.
		CMD_ENTRY(ID_FILE_NEW,							&CFCMCmds::OnFileNew,			NULL,								 0)
		CMD_ENTRY(ID_FILE_OPEN,							&CFCMCmds::OnFileOpen,			NULL,								 1)
		CMD_ENTRY(ID_FILE_SAVE,							&CFCMCmds::OnFileSave,			&CFCMCmds::OnUIFileSave,			 2)
		CMD_ENTRY(ID_FILE_SAVEAS,						&CFCMCmds::OnFileSaveAs,		&CFCMCmds::OnUIFileSaveAs,			-1)
		CMD_ENTRY(ID_FILE_CLOSE,						&CFCMCmds::OnFileClose,			&CFCMCmds::OnUIFileClose,			 1)
		CMD_RANGE(ID_MRU_FIRST,	ID_MRU_LAST,			&CFCMCmds::OnFileOpenMRU,		&CFCMCmds::OnUIFileOpenMRU,			-1)
		CMD_ENTRY(ID_FILE_EXIT,							&CFCMCmds::OnFileExit,			NULL,								-1)
		// View menu.
		CMD_RANGE(ID_VIEW_FIRST, ID_VIEW_LAST,			&CFCMCmds::OnViewDataView,		&CFCMCmds::OnUIViewDataView,		-1)
		// Club menu.
		CMD_ENTRY(ID_CLUB_DETAILS,						&CFCMCmds::OnClubDetails,		&CFCMCmds::OnUIClubDetails,			-1)
		// Data View menu.
		CMD_RANGE(ID_VIEW_FIRST_CMD, ID_VIEW_LAST_CMD,	&CFCMCmds::OnDataViewCmd,		&CFCMCmds::OnUIDataViewCmds,		-1)
		// Report menu.
		CMD_ENTRY(ID_REPORTS_MEMBERS,					&CFCMCmds::OnReportMembers,		&CFCMCmds::OnUIReportMembers,		-1)
		CMD_ENTRY(ID_REPORTS_FIXTURES,					&CFCMCmds::OnReportFixtures,	&CFCMCmds::OnUIReportFixtures,		-1)
		CMD_ENTRY(ID_REPORTS_OPPONENTS,					&CFCMCmds::OnReportOpponents,	&CFCMCmds::OnUIReportOpponents,		-1)
		CMD_ENTRY(ID_REPORTS_REFEREES,					&CFCMCmds::OnReportReferees,	&CFCMCmds::OnUIReportReferees,		-1)
		// Debug menu.
		CMD_ENTRY(ID_DEBUG_DBCLIPBOARD,					&CFCMCmds::OnDebugClipboard,	&CFCMCmds::OnUIDebugClipboard,		-1)
		CMD_ENTRY(ID_DEBUG_DBFILE,						&CFCMCmds::OnDebugFile,			&CFCMCmds::OnUIDebugFile,			-1)
		// Help menu.
		CMD_ENTRY(ID_HELP_ABOUT,						&CFCMCmds::OnHelpAbout,			NULL,								10)
	END_CMD_TABLE
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

CFCMCmds::~CFCMCmds()
{
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

void CFCMCmds::OnFileNew()
{
	NewFile();
}

/******************************************************************************
** Method:		OnFileCreated()
**
** Description:	New file created.
**
** Parameters:	oDoc	The doc affected.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CFCMCmds::OnFileCreated(CSDIDoc& oDoc)
{
	OnFileOpened(oDoc);
	OnClubDetails();
}

/******************************************************************************
** Method:		OnFileOpen()
**
** Description:	Open a new file, saving the current one first if necessary.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CFCMCmds::OnFileOpen()
{
	OpenFile();
}

/******************************************************************************
** Method:		OnFileOpened()
**
** Description:	File opened.
**
** Parameters:	oDoc	The doc affected.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CFCMCmds::OnFileOpened(CSDIDoc&)
{
	// Select a default view.
	SelectView(MEMBERS_VIEW);
}

/******************************************************************************
** Method:		OnFileSave()
**
** Description:	Save the current file, asking the user for a file name if
**				it has not being set yet.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CFCMCmds::OnFileSave()
{
	SaveFile();
}

/******************************************************************************
** Method:		OnFileSaveAs()
**
** Description:	Save the file to a new file name.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CFCMCmds::OnFileSaveAs()
{
	SaveFileAs();
}

/******************************************************************************
** Method:		OnFileClose()
**
** Description:	Close the current file, saving it if necessary.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CFCMCmds::OnFileClose()
{
	CloseFile();
}

/******************************************************************************
** Method:		OnFileOpenMRU()
**
** Description:	Open a MRU file from the MRU list.
**
** Parameters:	iCmdID		The ID of the command.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CFCMCmds::OnFileOpenMRU(uint iCmdID)
{
	if (OpenMRUFile(iCmdID - ID_MRU_FIRST))
	{
		// Select a default view.
		SelectView(MEMBERS_VIEW);
	}
}

/******************************************************************************
** Method:		OnFileExit()
**
** Description:	Terminate the app.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CFCMCmds::OnFileExit()
{
	ExitApp();
}

/******************************************************************************
** Method:		OnViewDataView()
**
** Description:	Selects one of the views in the view bar.
**
** Parameters:	iCmdID		The ID of the command.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CFCMCmds::OnViewDataView(uint iCmdID)
{
	SelectView(static_cast<DataView>(iCmdID - ID_VIEW_FIRST));
}

/******************************************************************************
** Method:		OnClubDetails()
**
** Description:	Show the dialog used to edit the clubs core details.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CFCMCmds::OnClubDetails()
{
	ASSERT(App.Doc() != NULL);

	CClubDetailsDlg Dlg(App.Doc()->m_oDB.m_oDetails[0]);

	if (Dlg.RunModal(App.m_rMainWnd) == IDOK)
		UpdateUI();
}

/******************************************************************************
** Method:		OnDataViewCmd()
**
** Description:	Forwards the command to the current data view.
**
** Parameters:	iCmdID		The ID of the command to execute.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CFCMCmds::OnDataViewCmd(uint iCmdID)
{
	ASSERT(App.View() != NULL);

	App.View()->m_ViewsMgr.OnCommand(iCmdID);
}

/******************************************************************************
** Method:		OnReport*()
**
** Description:	Execute a report.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CFCMCmds::OnReportMembers()
{
}

void CFCMCmds::OnReportFixtures()
{
}

void CFCMCmds::OnReportOpponents()
{
}

void CFCMCmds::OnReportReferees()
{
}

/******************************************************************************
** Method:		OnDebugClipboard()
**
** Description:	Dump the database to the clipboard.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CFCMCmds::OnDebugClipboard()
{
	try
	{
		CClipboard oStream;

		oStream.Open(GENERIC_WRITE, CF_TEXT);

		App.Doc()->m_oDB.Dump(oStream);

		oStream.Close();
	}
	catch(CStreamException& e)
	{
		// Notify user.
		App.m_AppWnd.AlertMsg(TXT("%s"), e.ErrorText());
	}
}

/******************************************************************************
** Method:		OnDebugFile()
**
** Description:	Dump the database to a text file.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CFCMCmds::OnDebugFile()
{
	CPath strPath;

	// The file extensions.
	static tchar szExts[]   = {	TXT("Text Files (*.txt)\0*.txt\0")
								TXT("All Files (*.*)\0*.*\0")
								TXT("\0\0")							};

	static tchar szDefExt[] = {	TXT("txt")							};


	// Get the output filename.
	if (strPath.Select(App.m_AppWnd, CPath::SaveFile, szExts, szDefExt))
	{
		try
		{
			CFile oStream;

			oStream.Create(strPath);

			App.Doc()->m_oDB.Dump(oStream);
/*
			CResultSet oRS = App.Doc()->m_oDB.m_oMembers.SelectAll();

			CSortColumns oCols;

			oCols.Add(1, CSortColumns::ASC);
			oCols.Add(2, CSortColumns::DESC);

			oRS.OrderBy(oCols);
			oRS.Dump(oStream);
  */
			oStream.Close();
		}
		catch(CStreamException& e)
		{
			// Notify user.
			App.m_AppWnd.AlertMsg(TXT("%s"), e.ErrorText());
		}
	}
}

/******************************************************************************
** Method:		OnHelpAbout()
**
** Description:	Show the about dialog.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CFCMCmds::OnHelpAbout()
{
	CAboutDlg Dlg;

	Dlg.RunModal(App.m_rMainWnd);
}

/******************************************************************************
** Method:		OnUI...()
**
** Description:	UI update handlers.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CFCMCmds::OnUIFileSave()
{
	bool bDocOpen  = (App.m_pDoc != NULL);
	bool bModified = (bDocOpen && App.m_pDoc->Modified());

	App.m_AppWnd.m_Menu.EnableCmd(ID_FILE_SAVE, (bDocOpen && bModified));
	App.m_AppWnd.m_ToolBar.m_SaveBtn.Enable(bDocOpen && bModified);
}

void CFCMCmds::OnUIFileSaveAs()
{
	bool bDocOpen = (App.m_pDoc != NULL);

	App.m_AppWnd.m_Menu.EnableCmd(ID_FILE_SAVEAS, bDocOpen);
}

void CFCMCmds::OnUIFileClose()
{
	bool bDocOpen = (App.m_pDoc != NULL);

	App.m_AppWnd.m_Menu.EnableCmd(ID_FILE_CLOSE, bDocOpen);
}

void CFCMCmds::OnUIFileOpenMRU()
{
	App.m_MRUList.UpdateMenu(App.m_AppWnd.m_Menu, ID_MRU_FIRST);
}

void CFCMCmds::OnUIViewDataView()
{
	bool bDocOpen = (App.m_pDoc != NULL);

	App.m_AppWnd.m_Menu.EnableItem(VIEW_MENU_POS, bDocOpen);

	if (!bDocOpen)
	{
		for (int i = ID_VIEW_FIRST; i <= ID_VIEW_LAST; i++)
			App.m_AppWnd.m_Menu.CheckCmd(i, false);
	}
}

void CFCMCmds::OnUIClubDetails()
{
	bool bDocOpen = (App.m_pDoc != NULL);

	App.m_AppWnd.m_Menu.EnableItem(CLUB_MENU_POS, bDocOpen);
}

void CFCMCmds::OnUIDataViewCmds()
{
	bool bDocOpen = (App.m_pDoc != NULL);

	App.m_AppWnd.m_Menu.EnableItem(OPTIONS_MENU_POS, bDocOpen);


	if (bDocOpen)
	{
		App.View()->m_ViewsMgr.OnUIUpdate();
	}
	else
	{
		App.m_AppWnd.m_ToolBar.m_AddBtn.Enable(false);
		App.m_AppWnd.m_ToolBar.m_EditBtn.Enable(false);
		App.m_AppWnd.m_ToolBar.m_DeleteBtn.Enable(false);
		App.m_AppWnd.m_ToolBar.m_PrintBtn.Enable(false);
		App.m_AppWnd.m_ToolBar.m_ImportBtn.Enable(false);
		App.m_AppWnd.m_ToolBar.m_ExportBtn.Enable(false);
	}
}

void CFCMCmds::OnUIReportMembers()
{
	bool bDocOpen = (App.m_pDoc != NULL);

	App.m_AppWnd.m_Menu.EnableItem(REPORTS_MENU_POS, bDocOpen);
}

void CFCMCmds::OnUIReportFixtures()
{
}

void CFCMCmds::OnUIReportOpponents()
{
}

void CFCMCmds::OnUIReportReferees()
{
}

void CFCMCmds::OnUIDebugClipboard()
{
	bool bDocOpen = (App.m_pDoc != NULL);

	App.m_AppWnd.m_Menu.EnableItem(DEBUG_MENU_POS, bDocOpen);
}

void CFCMCmds::OnUIDebugFile()
{
}

/******************************************************************************
** Method:		SelectView()
**
** Description:	Selects one of the data views.
**
** Parameters:	eNewView	The view to select.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CFCMCmds::SelectView(DataView eNewView)
{
	ASSERT(eNewView > NO_VIEW);
	ASSERT(eNewView < NUM_DATAVIEWS);

	CFCMView* pView = App.View();
	ASSERT(pView != NULL);

	// Get the current view.
	DataView eOldView = pView->m_ViewsMgr.CurrentView();

	// Ignore if not changing.
	if (eNewView == eOldView)
		return;

	// Change the check mark from the old view to the new one.
	App.m_AppWnd.m_Menu.CheckCmd(ID_VIEW_FIRST + eOldView, false);
	App.m_AppWnd.m_Menu.CheckCmd(ID_VIEW_FIRST + eNewView, true);

	// Switch the view dialogs.
	pView->m_ViewsMgr.SelectView(eNewView);
}

/******************************************************************************
** Method:		CmdBmpIndex()
**
** Description:	Get the commands' bitmap index.
**
** Parameters:	iCmdID		The command.
**
** Returns:		The index or -1 if there isn't one.
**
*******************************************************************************
*/

int CFCMCmds::CmdBmpIndex(uint iCmdID) const
{
	// Is view based command?
	if ( (iCmdID >= ID_VIEW_FIRST_CMD) && (iCmdID <= ID_VIEW_LAST_CMD) )
		return (iCmdID - ID_VIEW_FIRST_CMD) + VIEW_ICONS_BASE;

	// Pass to base class.
	return CCmdControl::CmdBmpIndex(iCmdID);
}

/******************************************************************************
** Method:		CmdHintID()
**
** Description:	Get the commands' hint resource ID.
**
** Parameters:	iCmdID		The command.
**
** Returns:		The hint resource ID.
**
*******************************************************************************
*/

int CFCMCmds::CmdHintID(uint iCmdID) const
{
	// Is view based command?
	if ( (iCmdID >= ID_VIEW_POPUP_CMD) && (iCmdID <= ID_VIEW_LAST_CMD) )
	{
		CFCMView* pView = App.View();

		if (pView != NULL)
		{
			// Get the current view.
			int nCurView = pView->m_ViewsMgr.CurrentView();

			return (nCurView * VIEW_HINTS_DELTA) + (iCmdID - ID_VIEW_POPUP_CMD) + VIEW_HINTS_BASE;
		}
	}

	return CCmdControl::CmdHintID(iCmdID);
}

/******************************************************************************
** Method:		CmdToolTipID()
**
** Description:	Get the commands' tool tip resource ID. This is the same as the
**				hint resource ID.
**
** Parameters:	iCmdID		The command.
**
** Returns:		The tool tip resource ID.
**
*******************************************************************************
*/

int CFCMCmds::CmdToolTipID(uint iCmdID) const
{
	return CFCMCmds::CmdHintID(iCmdID);
}

/******************************************************************************
** Method:		SetFocus()
**
** Description:	Sets the focus to the current view.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CFCMCmds::SetFocus()
{
	// Doc loaded?
	if (App.m_pDoc != NULL)
	{
		CFCMView* pView = App.View();

		// Pass focus to view, if created.
		if (pView != NULL)
			pView->m_ViewsMgr.SetFocus();
	}
}
