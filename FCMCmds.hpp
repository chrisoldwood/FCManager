/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		FCMCMDS.HPP
** COMPONENT:	The Application.
** DESCRIPTION:	The CFCMCmds class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef FCMCMDS_HPP
#define FCMCMDS_HPP

/******************************************************************************
** 
** Application command controller.
**
*******************************************************************************
*/

class CFCMCmds : public CSDICmds
{
public:
	//
	// Constructors/Destructor.
	//
	CFCMCmds();
	~CFCMCmds();

	//
	// Menu Commands.
	//

	// File menu.
	void OnFileNew();
	void OnFileOpen();
	void OnFileSave();
	void OnFileSaveAs();
	void OnFileClose();
	void OnFileOpenMRU(uint iCmdID);
	void OnFileExit();

	// View menu.
	void OnViewDataView(uint iCmdID);

	// Club menu.
	void OnClubDetails();

	// Data View options menu.
	void OnDataViewCmd(uint iCmdID);

	// Help menu.
	void OnHelpAbout();

	//
	// UI handlers.
	//

	// File menu.
	void OnUIFileSave();
	void OnUIFileSaveAs();
	void OnUIFileClose();
	void OnUIFileOpenMRU();

	// View menu.
	void OnUIViewDataView();

	// Club menu.
	void OnUIClubDetails();

	// Data View options menu.
	void OnUIDataViewCmds();

	// Help menu.

	//
	// Internal commands.
	//
	void SelectView(DataView eView);

protected:
	//
	// Members.
	//
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

#endif //FCMCMDS_HPP
