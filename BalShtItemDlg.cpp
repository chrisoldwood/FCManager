/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		BALSHTITEMDLG.CPP
** COMPONENT:	The Application.
** DESCRIPTION:	CBalShtItemDlg class definition.
**
*******************************************************************************
*/

#include "AppHeaders.hpp"
#include "BalShtItemDlg.hpp"

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

CBalShtItemDlg::CBalShtItemDlg(CFCMDB& oDB, CRow& oRow, bool bEditing)
	: CPropertySheet()
	, m_oRow(oRow)
	, m_bEditing(bEditing)
	, m_oDB(oDB)
	, m_nItemID(oRow[CBalSheet::ID])
	, m_oItemTypes(oDB.m_oBalShtTypes)
	, m_oTmpSubs(oDB, oDB.m_oMembers, false)
	, m_oMembers(oDB.m_oMembers)
	, m_oTmpExps(oDB, oDB.m_oExpenseTypes)
	, m_oExpTypes(oDB.m_oExpenseTypes)
	, m_oItemPage(oRow, m_oItemTypes)
	, m_oIncomePage(oRow, m_oTmpSubs, m_oMembers)
	, m_oExpensesPage(oRow, m_oTmpExps, m_oExpTypes)
	, m_oNotesPage(oRow, CBalSheet::NOTES, CBalSheet::NOTES_LEN)
{
	// Set the title.
	m_strTitle = (m_bEditing == true) ? "Edit Balance Sheet Item" : "Add A Balance Sheet Item";

	DEFINE_PAGE_TABLE
		PAGE(&m_oItemPage,		"Item Details")
		PAGE(&m_oIncomePage,	"Income"      )
		PAGE(&m_oExpensesPage,	"Expenses"    )
		PAGE(&m_oNotesPage,		"Notes"       )
	END_PAGE_TABLE

	// Editing existing item?
	if (m_bEditing)
	{
		CTable& oSubsTable = m_oDB.m_oSubs;

		// Fetch the current subs for the item.
		CResultSet oSubsRS = oSubsTable.Select(CWhereCmp(CSubs::ITEM_ID, CWhereCmp::EQUALS, m_nItemID));

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
		CResultSet oExpsRS = oExpsTable.Select(CWhereCmp(CExpenses::ITEM_ID, CWhereCmp::EQUALS, m_nItemID));

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
	}
}

/******************************************************************************
** Methods:		UpdateSubsTable()
**				UpdateDebitsTotal()
**
** Description:	Updates the sums of the credits/debits.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CBalShtItemDlg::UpdateSubsTable()
{
	// Credits table untouched?
	if (!m_oTmpSubs.Modified())
		return;

	CTable& oSubs   = m_oDB.m_oSubs;
	int     nItemID = m_oRow[CBalSheet::ID];

	// Was editing item?
	if (m_bEditing)
	{
		// Fetch the current subs for the item.
		CResultSet oRS = oSubs.Select(CWhereCmp(CSubs::ITEM_ID, CWhereCmp::EQUALS, nItemID));

		// Delete all rows for the item.
		for (int i = 0; i < oRS.Count(); i++)
			oSubs.DeleteRow(oRS[i]);
	}

	// Copy from temporary table to real table.
	for (int i = 0; i < m_oTmpSubs.RowCount(); i++)
	{
		CRow& oTmp = m_oTmpSubs[i];
		CRow& oNew = oSubs.CreateRow();

		oNew[CSubs::ITEM_ID]   = nItemID;
		oNew[CSubs::MEMBER_ID] = oTmp[CSubs::MEMBER_ID];
		oNew[CSubs::FEE]       = oTmp[CSubs::FEE];
		oNew[CSubs::PAID]      = oTmp[CSubs::PAID];

		oSubs.InsertRow(oNew);
	}
}

void CBalShtItemDlg::UpdateExpsTable()
{
	// Debits table untouched?
	if (!m_oTmpExps.Modified())
		return;

	CTable& oExps   = m_oDB.m_oExpenses;
	int     nItemID = m_oRow[CBalSheet::ID];

	// Was editing item?
	if (m_bEditing)
	{
		// Fetch the current expenses for the item.
		CResultSet oRS = oExps.Select(CWhereCmp(CExpenses::ITEM_ID, CWhereCmp::EQUALS, nItemID));

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
	}
}
