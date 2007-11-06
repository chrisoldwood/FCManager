/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		MEMBERDLG.CPP
** COMPONENT:	The Application.
** DESCRIPTION:	CMemberDlg class definition.
**
*******************************************************************************
*/

#include "Common.hpp"
#include "MemberDlg.hpp"
#include "Members.hpp"
#include "FCMDB.hpp"

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

CMemberDlg::CMemberDlg(CFCMDB& oDB, CRow& oRow, bool bEditing)
	: CPropertySheet()
	, m_oRow(oRow)
	, m_bEditing(bEditing)
	, m_oNamePage(oRow)
	, m_oStatusPage(oRow)
	, m_oPaymentsPage(oDB, oRow[CMembers::ID])
	, m_oStatsPage(oDB, oDB.m_oMemStatTypes, oDB.m_oMemStats, oRow[CMembers::ID])
	, m_oNotesPage(oRow, CMembers::NOTES, CMembers::NOTES_LEN)
{
	// Set the title.
	m_strTitle = (m_bEditing == true) ? "Edit Member Details" : "Add A Member";

	DEFINE_PAGE_TABLE
		PAGE(&m_oNamePage,		"Name && Address" )
		PAGE(&m_oStatusPage,	"Status"          )
		PAGE(&m_oPaymentsPage,	"Payments"        )
		PAGE(&m_oStatsPage,		"Statistics"      )
		PAGE(&m_oNotesPage,		"Notes"           )
	END_PAGE_TABLE
}
