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

	// Reports menu.
	void OnReportMembers();
	void OnReportFixtures();
	void OnReportOpponents();
	void OnReportReferees();

	// Debug menu.
	void OnDebugClipboard();
	void OnDebugFile();

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

	// Reports menu.
	void OnUIReportMembers();
	void OnUIReportFixtures();
	void OnUIReportOpponents();
	void OnUIReportReferees();

	// Debug menu.
	void OnUIDebugClipboard();
	void OnUIDebugFile();

	// Help menu.

	//
	// View management.
	//
	void SelectView(DataView eView);
	void SetFocus();

	//
	// Command property methods.
	//
	virtual int CmdBmpIndex(uint iCmdID) const;
	virtual int CmdHintID(uint iCmdID) const;
	virtual int CmdToolTipID(uint iCmdID) const;

protected:
	//
	// Members.
	//

	//
	// Template methods..
	//
	virtual void OnFileCreated(CSDIDoc& oDoc);
	virtual void OnFileOpened(CSDIDoc& oDoc);
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

#endif //FCMCMDS_HPP
