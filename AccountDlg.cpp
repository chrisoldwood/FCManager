/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		ACCOUNTDLG.CPP
** COMPONENT:	The Application.
** DESCRIPTION:	CAccountDlg class definition.
**
*******************************************************************************
*/

#include "AppHeaders.hpp"
#include "AccountDlg.hpp"

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

CAccountDlg::CAccountDlg(CFCMDB& oDB, CRow& oRow, bool bEditing)
	: CPropertySheet()
	, m_oRow(oRow)
	, m_bEditing(bEditing)
	, m_oDB(oDB)
	, m_nItemID(oRow[CAccounts::ID])
//	, m_oTmpSubs(oDB, oDB.m_oMembers, false)
//	, m_oMembers(oDB.m_oMembers)
//	, m_oTmpExps(oDB, oDB.m_oExpenseTypes)
//	, m_oExpTypes(oDB.m_oExpenseTypes)
	, m_oAccountPage(oRow)
	, m_oNotesPage(oRow, CAccounts::NOTES, CAccounts::NOTES_LEN)
{
	// Set the title.
	m_strTitle = (m_bEditing == true) ? "Edit Account" : "Add An Account";

	DEFINE_PAGE_TABLE
		PAGE(&m_oAccountPage,	"Name && Transactions")
		PAGE(&m_oNotesPage,		"Notes"               )
	END_PAGE_TABLE

	// Editing existing item?
	if (m_bEditing)
	{
/*		CTable& oSubsTable = m_oDB.m_oSubs;

		// Fetch the current subs for the item.
		CResultSet oSubsRS = oSubsTable.Select(CWhereEqual(CSubs::ITEM_ID, m_nItemID));

		// Copy to temporary table.
		for (int i = 0; i < oSubsRS.Count(); i++)
		{
			CRow& oOrig = oSubsRS[i];
			CRow& oCopy = m_oTmpSubs.CreateRow();

			ASSERT(oOrig[CSubs::ITEM_ID] == m_nItemID);

			oCopy[CSubs::ITEM_ID]   = m_nItemID;
			oCopy[CSubs::MEMBER_ID] = oOrig[CSubs::MEMBER_ID];
			oCopy[CSubs::FEE]       = oOrig[CSubs::FEE];
			oCopy[CSubs::PAID]      = oOrig[CSubs::PAID];

			m_oTmpSubs.InsertRow(oCopy, false);
		}

		CTable& oExpsTable = m_oDB.m_oExpenses;

		// Fetch the current expenses for the item.
		CResultSet oExpsRS = oExpsTable.Select(CWhereEqual(CExpenses::ITEM_ID, m_nItemID));

		// Copy to temporary table.
		for (i = 0; i < oExpsRS.Count(); i++)
		{
			CRow& oOrig = oExpsRS[i];
			CRow& oCopy = m_oTmpExps.CreateRow();

			ASSERT(oOrig[CExpenses::ITEM_ID] == m_nItemID);

			oCopy[CExpenses::ITEM_ID] = m_nItemID;
			oCopy[CExpenses::TYPE_ID] = oOrig[CExpenses::TYPE_ID];
			oCopy[CExpenses::PAID]    = oOrig[CExpenses::PAID];

			m_oTmpExps.InsertRow(oCopy, false);
		}
*/	}
}

/******************************************************************************
** Method:		UpdateTransTable()
**
** Description:	Updates the account transactions table.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CAccountDlg::UpdateTransTable()
{
/*	// Debits table untouched?
	if (!m_oTmpExps.Modified())
		return;

	CTable& oExps   = m_oDB.m_oExpenses;
	int     nItemID = m_oRow[CAccounts::ID];

	// Was editing item?
	if (m_bEditing)
	{
		// Fetch the current expenses for the item.
		CResultSet oRS = oExps.Select(CWhereEqual(CExpenses::ITEM_ID, nItemID));

		// Delete all rows for the item.
		for (int i = 0; i < oRS.Count(); i++)
			oExps.DeleteRow(oRS[i]);
	}

	// Copy from temporary table to real table.
	for (int i = 0; i < m_oTmpExps.RowCount(); i++)
	{
		CRow& oTmp = m_oTmpExps[i];
		CRow& oNew = oExps.CreateRow();

		oNew[CExpenses::ITEM_ID] = nItemID;
		oNew[CExpenses::TYPE_ID] = oTmp[CExpenses::TYPE_ID];
		oNew[CExpenses::PAID]    = oTmp[CExpenses::PAID];

		oExps.InsertRow(oNew);
	}*/
}
