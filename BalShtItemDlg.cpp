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
	, m_oTmpSubs(oDB, oDB.m_oMembers, false)
	, m_oMembers(oDB.m_oMembers)
	, m_oItemPage(oRow)
	, m_oIncomePage(oRow, m_oTmpSubs, m_oMembers)
	, m_oExpensesPage(oRow)
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
		CTable& oTable  = m_oDB.m_oSubs;

		// Fetch the current subs for the item.
		CResultSet oRS = oTable.Select(CWhereEqual(CSubs::ITEM_ID, m_nItemID));

		// Copy to temporary table.
		for (int i = 0; i < oRS.Count(); i++)
		{
			CRow& oOrig = oRS[i];
			CRow& oCopy = m_oTmpSubs.CreateRow();

			ASSERT(oOrig[CSubs::ITEM_ID] == m_nItemID);

			oCopy[CSubs::ITEM_ID]   = m_nItemID;
			oCopy[CSubs::MEMBER_ID] = oOrig[CSubs::MEMBER_ID];
			oCopy[CSubs::FEE]       = oOrig[CSubs::FEE];
			oCopy[CSubs::PAID]      = oOrig[CSubs::PAID];

			m_oTmpSubs.InsertRow(oCopy, false);
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
		CResultSet oRS = oSubs.Select(CWhereEqual(CSubs::ITEM_ID, nItemID));

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

void CBalShtItemDlg::UpdateExpensesTable()
{
}
