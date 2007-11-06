/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		STATSPAGE.HPP
** COMPONENT:	The Application.
** DESCRIPTION:	The CStatsPage class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef STATSPAGE_HPP
#define STATSPAGE_HPP

#if _MSC_VER > 1000
#pragma once
#endif

#include <WCL/CommonUI.hpp>
#include "TmpStats.hpp"
#include "TableGrid.hpp"

// Forward declarations.
class CStatTypes;
class CStats;

/******************************************************************************
** 
** This is base class for property pages used to display stats.
**
*******************************************************************************
*/

class CStatsPage : public CPropertyPage
{
public:
	//
	// Constructors/Destructor.
	//
	CStatsPage(CFCMDB& oDB, CStatTypes& oStatTypes, CStats& oStats, int nOwnerID);
	
	//
	// Members.
	//

protected:
	//
	// Members.
	//
	CFCMDB&		m_oDB;
	int			m_nOwnerID;
	CStatTypes&	m_oStatTypes;
	CStats&		m_oStats;
	CTmpStats	m_oTmpStats;

	CTableGrid	m_lvGrid;
	
	// The list view columns.
	enum
	{
		DATE,
		NAME,
		VALUE,
		NUM_COLUMNS
	};

	static CTableGrid::Column Columns[NUM_COLUMNS];

	//
	// Message processors.
	//
	virtual void OnInitDialog();
	virtual bool OnOk();
			void OnAdd();
			void OnEdit();
			void OnDelete();
	     LRESULT OnDblClick(NMHDR& rMsgHdr);

	//
	// Internal methods.
	//
	void UpdateButtons();
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

#endif //STATSPAGE_HPP
