/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		REFEREEDLG.CPP
** COMPONENT:	The Application.
** DESCRIPTION:	CRefereeDlg class definition.
**
*******************************************************************************
*/

#include "Common.hpp"
#include "RefereeDlg.hpp"
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

CRefereeDlg::CRefereeDlg(CFCMDB& oDB, CRow& oRow, bool bEditing)
	: CPropertySheet()
	, m_oRow(oRow)
	, m_bEditing(bEditing)
	, m_oNamePage(oRow)
	, m_oStatsPage(oDB, oDB.m_oRefStatTypes, oDB.m_oRefStats, oRow[CReferees::ID])
	, m_oNotesPage(oRow, CReferees::NOTES, CReferees::NOTES_LEN)
{
	// Set the title.
	m_strTitle = (m_bEditing == true) ? TXT("Edit Referee Details") : TXT("Add A Referee");

	DEFINE_PAGE_TABLE
		PAGE(&m_oNamePage,		TXT("Name && Address"))
		PAGE(&m_oStatsPage,		TXT("Statistics")     )
		PAGE(&m_oNotesPage,		TXT("Notes")          )
	END_PAGE_TABLE
}
