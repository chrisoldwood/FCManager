/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		OPPONENTDLG.CPP
** COMPONENT:	The Application.
** DESCRIPTION:	COpponentDlg class definition.
**
*******************************************************************************
*/

#include "Common.hpp"
#include "OpponentDlg.hpp"
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

COpponentDlg::COpponentDlg(CFCMDB& oDB, CRow& oRow, bool bEditing)
	: CPropertySheet()
	, m_oRow(oRow)
	, m_bEditing(bEditing)
	, m_oOpponentPage(oRow)
	, m_oSecretaryPage(oRow)
	, m_oStatsPage(oDB, oDB.m_oOppStatTypes, oDB.m_oOppStats, oRow[COpponents::ID])
	, m_oNotesPage(oRow, COpponents::NOTES, COpponents::NOTES_LEN)
{
	// Set the title.
	m_strTitle = (m_bEditing == true) ? TXT("Edit Opponent Details") : TXT("Add An Opponent");

	DEFINE_PAGE_TABLE
		PAGE(&m_oOpponentPage,	TXT("Club Details")     )
		PAGE(&m_oSecretaryPage,	TXT("Secretary Details"))
		PAGE(&m_oStatsPage,		TXT("Statistics")       )
		PAGE(&m_oNotesPage,		TXT("Notes")            )
	END_PAGE_TABLE
}
