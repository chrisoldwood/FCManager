/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		FCMCMDS.CPP
** COMPONENT:	The Application.
** DESCRIPTION:	CFCMCmds class definition.
**
*******************************************************************************
*/

#include "AppHeaders.hpp"
#include "AboutDlg.hpp"
#include "ClubDetailsDlg.hpp"

// The cmd ID of the first view.
const int ID_VIEW_FIRST = ID_VIEW_MEMBERS;
const int ID_VIEW_LAST  = ID_VIEW_REFEREES;

// Range of data view commands.
const int ID_DATAVIEW_FIRST = ID_OPTIONS_BASE;
const int ID_DATAVIEW_LAST  = ID_OPTIONS_BASE + 90;

// Range of MRU commands.
const int ID_MRU_FIRST = ID_FILE_MRU_1;
const int ID_MRU_LAST  = ID_FILE_MRU_4;

// Position of top level menu items.
const int FILE_MENU_POS    = 0;
const int VIEW_MENU_POS    = 1;
const int CLUB_MENU_POS    = 2;
const int OPTIONS_MENU_POS = 3;
const int HELP_MENU_POS    = 4;

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
		CMD_ENTRY(ID_FILE_NEW,					OnFileNew,			NULL,				 0)
		CMD_ENTRY(ID_FILE_OPEN,					OnFileOpen,			NULL,				 1)
		CMD_ENTRY(ID_FILE_SAVE,					OnFileSave,			OnUIFileSave,		 2)
		CMD_ENTRY(ID_FILE_SAVEAS,				OnFileSaveAs,		OnUIFileSaveAs,		-1)
		CMD_ENTRY(ID_FILE_CLOSE,				OnFileClose,		OnUIFileClose,		 1)
		CMD_RANGE(ID_MRU_FIRST,	ID_MRU_LAST,	OnFileOpenMRU,		OnUIFileOpenMRU,	-1)
		CMD_ENTRY(ID_FILE_EXIT,					OnFileExit,			NULL,				-1)
		// View menu.
		CMD_RANGE(ID_VIEW_FIRST, ID_VIEW_LAST,	OnViewDataView,		OnUIViewDataView,	-1)
		// Club menu.
		CMD_ENTRY(ID_CLUB_DETAILS,				OnClubDetails,		OnUIClubDetails,	-1)
		// Data View menu.
		CMD_RANGE(ID_DATAVIEW_FIRST, ID_DATAVIEW_LAST,	OnDataViewCmd,		OnUIDataViewCmds,	-1)
		// Help menu.
		CMD_ENTRY(ID_HELP_ABOUT,				OnHelpAbout,		NULL,				-1)
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
	if (NewFile())
	{
		// Select a default view.
		SelectView(MEMBERS_VIEW);
	}
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
	if (OpenFile())
	{
		// Select a default view.
		SelectView(MEMBERS_VIEW);
	}
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

	CClubDetailsDlg Dlg(App.Doc()->m_oDB [CFCMDB::DETAILS][0]);

	if (Dlg.RunModal(App.m_rMainWnd) == IDOK)
	{
	}
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

	if (bDocOpen)
	{
		App.View()->m_ViewsMgr.OnUIUpdate();
	}
	else
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
