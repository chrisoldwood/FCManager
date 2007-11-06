/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		FIXTUREDLG.CPP
** COMPONENT:	The Application.
** DESCRIPTION:	CFixtureDlg class definition.
**
*******************************************************************************
*/

#include "Common.hpp"
#include "FixtureDlg.hpp"
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

CFixtureDlg::CFixtureDlg(CFCMDB& oDB, CRow& oRow, bool bEditing)
	: CPropertySheet()
	, m_oRow(oRow)
	, m_bEditing(bEditing)
	, m_oDetailsPage(oDB, oRow)
	, m_oStatsPage(oDB, oDB.m_oFixStatTypes, oDB.m_oFixStats, oRow[CFixtures::ID])
	, m_oNotesPage(oRow, CFixtures::NOTES, CFixtures::NOTES_LEN)
{
	// Set the title.
	m_strTitle = (m_bEditing == true) ? "Edit Fixture Details" : "Add A Fixture";

	DEFINE_PAGE_TABLE
		PAGE(&m_oDetailsPage,	"Details"   )
		PAGE(&m_oStatsPage,		"Statistics")
		PAGE(&m_oNotesPage,		"Notes"     )
	END_PAGE_TABLE
}
