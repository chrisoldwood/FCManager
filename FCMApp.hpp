/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		FCMAPP.HPP
** COMPONENT:	The Application.
** DESCRIPTION:	The CFCMApp class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef FCMAPP_HPP
#define FCMAPP_HPP

/******************************************************************************
** 
** The application class.
**
*******************************************************************************
*/

class CFCMApp : public CSDIApp
{
public:
	//
	// Constructors/Destructor.
	//
	CFCMApp();
	~CFCMApp();

	//
	// Typed access to the doc and view.
	//
	CFCMDoc*  Doc();
	CFCMView* View();

	//
	// Members
	//
	CFCMMainWnd	m_AppWnd;			// Main window.
	CFCMCmds	m_AppCmds;			// Cmd controller.
	CIniFile	m_oIniFile;			// Ini file.
	CPrinter	m_oPrinter;			// Default printer.
	CRect		m_rcAppWnd;			// Last position of main window.
	CSize		m_dmTeamSelDlg;		// Last size of team selection dialog.

	//
	// Template methods for getting doc and view specifics.
	//
	virtual CSDIDoc*    CreateDoc() const;
	virtual CView*      CreateView(CDoc& rDoc) const;
	virtual const char* FileExts() const;
	virtual const char* DefFileExt() const;

	//
	// Misc helper functions.
	//
	CString FormatName(CRow& rRow, int nForename, int nSurname, bool bReverse = false) const;
	CString FormatMoney(CRow& rRow, int nColumn) const;
	CString FormatMoney(int nAmount) const;
	CString FormatDate(CRow& rRow, int nColumn) const;
	CString FormatDecimal(CRow& rRow, int nColumn, int nDecDigits) const;

protected:
	//
	// Members
	//

	//
	// Startup and Shutdown template methods.
	//
	virtual	bool OnOpen();
	virtual	bool OnClose();

	//
	// Internal methods.
	//
	void LoadDefaults();
	void SaveDefaults();
};

/******************************************************************************
**
** Global variables.
**
*******************************************************************************
*/

//The application object.
extern CFCMApp App;

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

inline CFCMDoc* CFCMApp::Doc()
{
	return static_cast<CFCMDoc*>(m_pDoc);
}

inline CFCMView* CFCMApp::View()
{
	return static_cast<CFCMView*>(m_pView);
}

inline CSDIDoc* CFCMApp::CreateDoc() const
{
	return new CFCMDoc;
}

inline CView* CFCMApp::CreateView(CDoc& rDoc) const
{
	return new CFCMView(static_cast<CFCMDoc&>(rDoc));
}

inline const char* CFCMApp::FileExts() const
{
	static char szExts[] = {	"F.C. Manager Files (*.fcm)\0*.fcm\0"
								"All Files (*.*)\0*.*\0"
								"\0\0"							};

	return szExts;
}

inline const char* CFCMApp::DefFileExt() const
{
	static char szDefExt[] = { "fcm" };

	return szDefExt;
}

#endif //FCMAPP_HPP
