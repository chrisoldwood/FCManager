/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		PAYMENTSPAGE.CPP
** COMPONENT:	The Application.
** DESCRIPTION:	CPaymentsPage class definition.
**
*******************************************************************************
*/

#include "Common.hpp"
#include "PaymentsPage.hpp"
#include "FCMDB.hpp"
#include "FCMApp.hpp"

// The list view columns.
CTableGrid::Column CPaymentsPage::Columns[NUM_COLUMNS] =
{
	{ TXT("Date"),   75, LVCFMT_LEFT,  CTmpSubs::ITEM_DATE },
	{ TXT("Item"),  175, LVCFMT_LEFT,  CTmpSubs::ITEM_NAME },
	{ TXT("£ Fee"),  50, LVCFMT_RIGHT, CTmpSubs::FEE       },
	{ TXT("£ Paid"), 50, LVCFMT_RIGHT, CTmpSubs::PAID      }
};

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

CPaymentsPage::CPaymentsPage(CFCMDB& oDB, int nMemberID)
	: CPropertyPage(IDD_PAYMENTS_PAGE)
	, m_oDB(oDB)
	, m_nMemberID(nMemberID)
	, m_oTmpSubs(oDB, m_oDB.m_oMembers, true)
	, m_lvGrid(this)
{
	DEFINE_CTRL_TABLE
		CTRL(IDC_PAYMENTS,	&m_lvGrid)
	END_CTRL_TABLE

	DEFINE_GRAVITY_TABLE
		CTRLGRAV(IDC_PAYMENTS, LEFT_EDGE, TOP_EDGE, RIGHT_EDGE, BOTTOM_EDGE)
	END_GRAVITY_TABLE

	// Find all the payments for this member.
	CResultSet oRS = m_oDB.m_oSubs.Select(CWhereCmp(CSubs::MEMBER_ID, CWhereCmp::EQUALS, m_nMemberID));

	for (size_t i = 0; i < oRS.Count(); i++)
	{
		CRow& oCurRow = oRS[i];
		CRow& oCpyRow = m_oTmpSubs.CreateRow();
		CRow* pItmRow = m_oDB.m_oBalSheet.SelectRow(CBalSheet::ID, oCurRow[CSubs::ITEM_ID]);

		ASSERT(pItmRow != NULL);

		// Copy data.
		oCpyRow[CTmpSubs::ITEM_ID]   = oCurRow[CSubs::ITEM_ID];
		oCpyRow[CTmpSubs::MEMBER_ID] = oCurRow[CSubs::MEMBER_ID];
		oCpyRow[CTmpSubs::FEE]       = oCurRow[CSubs::FEE];
		oCpyRow[CTmpSubs::PAID]      = oCurRow[CSubs::PAID];
		oCpyRow[CTmpSubs::ITEM_DATE] = pItmRow->Field(CBalSheet::DATE);
		oCpyRow[CTmpSubs::ITEM_NAME] = pItmRow->Field(CBalSheet::NAME);

		// Insert into tmp table.
		m_oTmpSubs.InsertRow(oCpyRow, false);
	}

	// Initialise the grid.
	m_lvGrid.Columns(NUM_COLUMNS, Columns);
}

/******************************************************************************
** Method:		OnInitDialog()
**
** Description:	Initialise the dialog.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CPaymentsPage::OnInitDialog()
{
	m_lvGrid.AddRows(m_oTmpSubs, true, -1);
}

/******************************************************************************
** Method:		CompareRows()
**
** Description:	Handler method to compare two rows.
**
** Parameters:	oRow1	Row 1.
**				oRow2	Row 2.
**
** Returns:		As strcmp.
**
*******************************************************************************
*/

int CPaymentsPage::CompareRows(CRow& oRow1, CRow& oRow2)
{
	return oRow1[CTmpSubs::ITEM_DATE].Compare(oRow2[CTmpSubs::ITEM_DATE]);
}

/******************************************************************************
** Method:		RowFieldValue()
**
** Description:	Handler method to get the value for a field.
**
** Parameters:	oRow	The row.
**				nField	The field index.
**
** Returns:		The string value.
**
*******************************************************************************
*/

CString CPaymentsPage::RowFieldValue(CRow& oRow, size_t nField)
{
	// Format FEE?
	if (nField == CTmpSubs::FEE)
	{
		return App.FormatMoney(oRow, nField);
	}
	// Format PAID?
	else if (nField == CTmpSubs::PAID)
	{
		return App.FormatMoney(oRow, nField);
	}

	return oRow[nField].Format();
}
