/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		STATSPAGE.CPP
** COMPONENT:	The Application.
** DESCRIPTION:	CStatsPage class definition.
**
*******************************************************************************
*/

#include "AppHeaders.hpp"
#include "StatsPage.hpp"
#include "StatisticDlg.hpp"

// The list view columns.
CTableGrid::Column CStatsPage::Columns[NUM_COLUMNS] =
{
	{ "Date",      100, LVCFMT_LEFT,  CTmpStats::DATE  },
	{ "Statistic", 100, LVCFMT_LEFT,  CTmpStats::NAME  },
	{ "Value",      75, LVCFMT_RIGHT, CTmpStats::VALUE }
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

CStatsPage::CStatsPage(CFCMDB& oDB, CStatTypes& oStatTypes, CStats& oStats, int nOwnerID)
	: CPropertyPage(IDD_STATS_PAGE)
	, m_oDB(oDB)
	, m_oStatTypes(oStatTypes)
	, m_oStats(oStats)
	, m_nOwnerID(nOwnerID)
	, m_oTmpStats(oDB, oStatTypes)
{
	DEFINE_CTRL_TABLE
		CTRL(IDC_STATS,	&m_lvGrid)
	END_CTRL_TABLE

	DEFINE_GRAVITY_TABLE
		CTRLGRAV(IDC_STATS,  LEFT_EDGE,  TOP_EDGE,    RIGHT_EDGE,  BOTTOM_EDGE)
		CTRLGRAV(IDC_ADD,    LEFT_EDGE,  BOTTOM_EDGE, LEFT_EDGE,   BOTTOM_EDGE)
		CTRLGRAV(IDC_EDIT,   LEFT_EDGE,  BOTTOM_EDGE, LEFT_EDGE,   BOTTOM_EDGE)
		CTRLGRAV(IDC_DELETE, LEFT_EDGE,  BOTTOM_EDGE, LEFT_EDGE,   BOTTOM_EDGE)
		CTRLGRAV(IDC_TYPES,  RIGHT_EDGE, BOTTOM_EDGE, RIGHT_EDGE,  BOTTOM_EDGE)
	END_GRAVITY_TABLE

	DEFINE_CTRLMSG_TABLE
		CMD_CTRLMSG(IDC_ADD,	BN_CLICKED, OnAdd     )
		CMD_CTRLMSG(IDC_EDIT,	BN_CLICKED, OnEdit    )
		CMD_CTRLMSG(IDC_DELETE,	BN_CLICKED, OnDelete  )
		CMD_CTRLMSG(IDC_TYPES,	BN_CLICKED, OnTypes   )
		NFY_CTRLMSG(IDC_STATS,  NM_DBLCLK,  OnDblClick)
	END_CTRLMSG_TABLE

	// Find the owners rows.
	CResultSet oRS = m_oStats.Select(CWhereEqual(CStats::OWNER_ID, m_nOwnerID));

	for (int i = 0; i < oRS.Count(); i++)
	{
		CRow& oCurRow = oRS[i];
		CRow& oCpyRow = m_oTmpStats.CreateRow();
		CRow* pTypRow = m_oStatTypes.SelectRow(CStatTypes::ID, oCurRow[CStats::TYPE_ID]);

		ASSERT(pTypRow != NULL);

		// Copy data.
		oCpyRow[CTmpStats::OWNER_ID] = oCurRow[CStats::OWNER_ID];
		oCpyRow[CTmpStats::DATE]     = oCurRow[CStats::DATE];
		oCpyRow[CTmpStats::TYPE_ID]  = oCurRow[CStats::TYPE_ID];
		oCpyRow[CTmpStats::VALUE]    = oCurRow[CStats::VALUE];
		oCpyRow[CTmpStats::NAME]     = pTypRow->Field(CStatTypes::NAME);

		// Insert into tmp table.
		m_oTmpStats.InsertRow(oCpyRow, false);
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

void CStatsPage::OnInitDialog()
{
	m_lvGrid.AddRows(m_oTmpStats);

	UpdateButtons();
}

/******************************************************************************
** Method:		OnOk()
**
** Description:	Validate the data and close the dialog.
**
** Parameters:	None.
**
** Returns:		true or false.
**
*******************************************************************************
*/

bool CStatsPage::OnOk()
{
	if (m_oTmpStats.Modified())
	{
		// Delete the existing rows for this owner and group.
		CResultSet oRS = m_oStats.Select(CWhereEqual(CStats::OWNER_ID, m_nOwnerID));

		for (int i = 0; i < oRS.Count(); i++)
			m_oStats.DeleteRow(oRS[i]);

		// Copy the rows back from the tmp table.
		for (i = 0; i < m_oTmpStats.RowCount(); i++)
		{
			CRow& oCurRow = m_oTmpStats[i];
			CRow& oCpyRow = m_oStats.CreateRow();

			// Copy data.
			oCpyRow[CStats::OWNER_ID] = oCurRow[CTmpStats::OWNER_ID];
			oCpyRow[CStats::DATE]     = oCurRow[CTmpStats::DATE];
			oCpyRow[CStats::TYPE_ID]  = oCurRow[CTmpStats::TYPE_ID];
			oCpyRow[CStats::VALUE]    = oCurRow[CTmpStats::VALUE];

			// Insert into tmp table.
			m_oStats.InsertRow(oCpyRow);
		}
	}	

	return true;
}

/******************************************************************************
** Method:		OnAdd()
**
** Description:	Add a new statistic.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CStatsPage::OnAdd()
{
	CRow& oRow = m_oTmpStats.CreateRow();

	// Set the owner.
	oRow[CTmpStats::OWNER_ID] = m_nOwnerID;

	// Show the add statistic dialog.
	CStatisticDlg Dlg(m_oStatTypes, oRow, false);

	if (Dlg.RunModal(*this) == IDOK)
	{
		// Add the row to the table and grid.
		m_oTmpStats.InsertRow(oRow);
		m_lvGrid.AddRow(oRow);
	}
	else
	{
		delete &oRow;
	}

	UpdateButtons();
}

/******************************************************************************
** Method:		OnEdit()
**
** Description:	Edit an exiting statistic.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CStatsPage::OnEdit()
{
	// Ignore, if no selection.
	if (m_lvGrid.IsSelection() == false)
		return;

	int   nRow = m_lvGrid.Selected();
	CRow& oRow = m_lvGrid.Row(nRow);

	// Show the edit statistic dialog.
	CStatisticDlg Dlg(m_oStatTypes, oRow, true);

	if (Dlg.RunModal(*this) == IDOK)
	{
		m_lvGrid.UpdateRow(nRow);
	}

	UpdateButtons();
}

/******************************************************************************
** Method:		OnDelete()
**
** Description:	Delete an existing statistic.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CStatsPage::OnDelete()
{
	// Ignore, if no selection.
	if (m_lvGrid.IsSelection() == false)
		return;

	// Delete selected row.
	m_lvGrid.DeleteRow(m_lvGrid.Selected());

	UpdateButtons();
}

/******************************************************************************
** Method:		OnTypes()
**
** Description:	Maintain the statistic types.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CStatsPage::OnTypes()
{
}

/******************************************************************************
** Method:		OnDblClick()
**
** Description:	Edit the row.
**
** Parameters:	rMsgHdr		The message details.
**
** Returns:		0.
**
*******************************************************************************
*/

LRESULT CStatsPage::OnDblClick(NMHDR&)
{
	OnEdit();

	return 0;
}

/******************************************************************************
** Method:		UpdateButtons()
**
** Description:	Updates the editing buttons.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CStatsPage::UpdateButtons()
{
	bool bIsSelection = m_lvGrid.IsSelection();

	Control(IDC_ADD).Enable(true);
	Control(IDC_EDIT).Enable(bIsSelection);
	Control(IDC_DELETE).Enable(bIsSelection);
	Control(IDC_TYPES).Enable(false);
}
