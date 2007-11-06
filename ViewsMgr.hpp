/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		VIEWSMGR.HPP
** COMPONENT:	The Application.
** DESCRIPTION:	The CViewsMgr class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef VIEWSMGR_HPP
#define VIEWSMGR_HPP

#if _MSC_VER > 1000
#pragma once
#endif

#include <WCL/SplitWnd.hpp>
#include "MembersView.hpp"
#include "FixturesView.hpp"
#include "BalSheetView.hpp"
#include "AccountsView.hpp"
#include "TeamSelsView.hpp"
#include "OpponentsView.hpp"
#include "RefereesView.hpp"
#include "ViewsBar.hpp"
#include <WCL/FrameMenu.hpp>

// Forward declarations.
class CViewDlg;

/******************************************************************************
**
** The list of data views.
**
*******************************************************************************
*/

enum DataView
{
	NO_VIEW        = -1,	// No data view.
	MEMBERS_VIEW   = 0,		// Club members.
	FIXTURES_VIEW  = 1,		// Team fixtures.
	BALANCE_VIEW   = 2,		// Balance sheet.
	ACCOUNTS_VIEW  = 3,		// Accounts.
	TEAM_SELS_VIEW = 4,		// Team selections.
	OPPONENTS_VIEW = 5,		// League opponents.
	REFEREES_VIEW  = 6,		// League referees

	NUM_DATAVIEWS,			// Number of data views.
};

/******************************************************************************
** 
** This is the main view window which manages the display of the various data
** views. It is a split window with the data view selector on the left and the
** data view on the right.
**
*******************************************************************************
*/

class CViewsMgr : public CSplitWnd
{
public:
	//
	// Constructors/Destructor.
	//
	CViewsMgr(CFCMDoc& rDoc);
	~CViewsMgr();

	//
	// Methods.
	//
	CViewDlg& View(DataView eView) const;
	DataView  CurrentView() const;
	void      SelectView(DataView eView);
	void      SetFocus();

	void     OnCommand(uint iCmdID);
	void     OnUIUpdate();

	//
	// View member.
	//
	CMembersView	m_oMembersView;					// Members data view.
	CFixturesView	m_oFixturesView;				// Fixtures data view.
	CBalSheetView	m_oBalSheetView;				// Balance sheet data view.
	CAccountsView	m_oAccountsView;				// Accounts view.
	CTeamSelsView	m_oTeamSelsView;				// Team selector data view.
	COpponentsView	m_oOpponentsView;				// Opponents data view.
	CRefereesView	m_oRefereesView;				// Referees data view.

protected:
	//
	// Members.
	//
	CViewsBar		m_oViewsBar;					// The views selector bar.
	DataView		m_eCurrView;					// Current view.
	CViewDlg*		m_pDataViews[NUM_DATAVIEWS];	// Array of views.
	CFrameMenu		m_oOptionsMenus;				// Options popup menus.

	// Child window ID.
	enum { IDC_VIEW_BAR = 100 };

	//
	// Message processors (Overriden from the base class).
	//
	virtual void OnCreate(const CRect& rcClient);

	//
	// Control message processors.
	//
	void OnSelectView();
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

inline CViewDlg& CViewsMgr::View(DataView eView) const
{
	ASSERT((eView >= 0) && (eView < NUM_DATAVIEWS));

	return *m_pDataViews[eView];
}

inline DataView CViewsMgr::CurrentView() const
{
	return m_eCurrView;
}

inline void CViewsMgr::OnCommand(uint iCmdID)
{
	if (m_eCurrView != NO_VIEW)
		m_pDataViews[m_eCurrView]->OnCommand(iCmdID);
}

inline void CViewsMgr::OnUIUpdate()
{
	if (m_eCurrView != NO_VIEW)
		m_pDataViews[m_eCurrView]->OnUIUpdate();
}

#endif //VIEWSMGR_HPP
