/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		APPHEADERS.HPP
** COMPONENT:	The Application.
** DESCRIPTION:	Wrapper to include all the main application headers.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef APPHEADERS_HPP
#define APPHEADERS_HPP

/******************************************************************************
**
** System headers.
**
*******************************************************************************
*/

#include "wcl.hpp"		// Windows C++ library core headers.
#include "MDBL.hpp"		// Memory Database library core headers.

/******************************************************************************
**
** Application specific headers.
**
*******************************************************************************
*/

#include "Resource.h"

// App data classes.
#include "ClubDetails.hpp"
#include "Members.hpp"
#include "Fixtures.hpp"
#include "BalSheet.hpp"
#include "Subs.hpp"
#include "ExpenseTypes.hpp"
#include "Expenses.hpp"
#include "Accounts.hpp"
#include "AcctTrans.hpp"
#include "TeamSels.hpp"
#include "Opponents.hpp"
#include "Referees.hpp"
#include "StatTypes.hpp"
#include "Stats.hpp"
#include "MemStatTypes.hpp"
#include "MemStats.hpp"
#include "FixStatTypes.hpp"
#include "FixStats.hpp"
#include "OppStatTypes.hpp"
#include "OppStats.hpp"
#include "RefStatTypes.hpp"
#include "RefStats.hpp"
#include "TmpSubs.hpp"
#include "TmpExps.hpp"
#include "TmpStats.hpp"
#include "FCMDB.hpp"
#include "FCMDoc.hpp"

// Common dialog/ctrl classes.
#include "NotesDlg.hpp"
#include "PitchCtrl.hpp"
#include "TableGrid.hpp"

// App view classes.
#include "ViewsBar.hpp"
#include "ViewDlg.hpp"
#include "GridViewDlg.hpp"
#include "MembersView.hpp"
#include "FixturesView.hpp"
#include "BalSheetView.hpp"
#include "AccountsView.hpp"
#include "TeamSelsView.hpp"
#include "OpponentsView.hpp"
#include "RefereesView.hpp"
#include "ViewsMgr.hpp"

// Core app classes.
#include "FCMCmds.hpp"
#include "FCMToolBar.hpp"
#include "FCMMainWnd.hpp"
#include "FCMView.hpp"
#include "FCMApp.hpp"

#endif //APPHEADERS_HPP
