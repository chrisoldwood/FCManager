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
	m_strTitle = (m_bEditing == true) ? TXT("Edit Fixture Details") : TXT("Add A Fixture");

	DEFINE_PAGE_TABLE
		PAGE(&m_oDetailsPage,	TXT("Details")   )
		PAGE(&m_oStatsPage,		TXT("Statistics"))
		PAGE(&m_oNotesPage,		TXT("Notes")     )
	END_PAGE_TABLE
}
