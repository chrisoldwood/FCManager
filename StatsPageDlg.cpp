/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		STATSPAGEDLG.CPP
** COMPONENT:	The Application.
** DESCRIPTION:	CStatsPageDlg class definition.
**
*******************************************************************************
*/

#include "AppHeaders.hpp"
#include "StatsPageDlg.hpp"

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

CStatsPageDlg::CStatsPageDlg()
	: CPropertyPageDlg(IDD_STATS_PAGE)
{
	DEFINE_CTRL_TABLE
		CTRL(IDC_STATS,	&m_lvStats)
	END_CTRL_TABLE

	DEFINE_GRAVITY_TABLE
		CTRLGRAV(IDC_STATS,  LEFT_EDGE,  TOP_EDGE,    RIGHT_EDGE,  BOTTOM_EDGE)
		CTRLGRAV(IDC_ADD,    LEFT_EDGE,  BOTTOM_EDGE, LEFT_EDGE,   BOTTOM_EDGE)
		CTRLGRAV(IDC_EDIT,   LEFT_EDGE,  BOTTOM_EDGE, LEFT_EDGE,   BOTTOM_EDGE)
		CTRLGRAV(IDC_DELETE, LEFT_EDGE,  BOTTOM_EDGE, LEFT_EDGE,   BOTTOM_EDGE)
		CTRLGRAV(IDC_NEW,    RIGHT_EDGE, BOTTOM_EDGE, RIGHT_EDGE,  BOTTOM_EDGE)
	END_GRAVITY_TABLE
}
