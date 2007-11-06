/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		STATISTICDLG.CPP
** COMPONENT:	The Application.
** DESCRIPTION:	CStatisticDlg class definition.
**
*******************************************************************************
*/

#include "Common.hpp"
#include "StatisticDlg.hpp"
#include "StatTypes.hpp"
#include "TmpStats.hpp"
#include <time.h>

/******************************************************************************
** Method:		Constructor.
**
** Description:	.
**
** Parameters:	oStatTypes	The stat types table.
**				oRow		The stats table row.
**				bEditing	Editing or creating row?
**
** Returns:		Nothing.
**
*******************************************************************************
*/

CStatisticDlg::CStatisticDlg(CStatTypes& oStatTypes, CRow& oRow, bool bEditing)
	: CDialog(IDD_STATISTIC)
	, m_oRow(oRow)
	, m_bEditing(bEditing)
	, m_ebValue(false, 5, 2)
	, m_oStatTypes(oStatTypes)
{
	DEFINE_CTRL_TABLE
		CTRL(IDC_DATE,			&m_dtpDate)
		CTRL(IDC_STATISTICS,	&m_cbTypes)
		CTRL(IDC_VALUE,			&m_ebValue)
	END_CTRL_TABLE
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

void CStatisticDlg::OnInitDialog()
{
	// Set the dialog title.
	Title((m_bEditing == true) ? "Edit Statistic" : "Add A Statistic");

	// Initialise controls.
	m_dtpDate.Format("ddd' 'dd'/'MM'/'yyyy");

	// Load stats types into combo box.
	for (int i = 0; i < m_oStatTypes.RowCount(); i++)
	{
		CRow& oRow = m_oStatTypes[i];

		// Create the combo string.
		CString strName = oRow[CStatTypes::NAME];

		// Add to the combo box.
		int n = m_cbTypes.Add(strName);
		m_cbTypes.ItemData(n, i);
	}

	// Adding an entry?
	if (!m_bEditing)
	{
		// Set date to today.
		m_oRow[CTmpStats::DATE] = time(NULL);

		// Default to first type.
		m_cbTypes.CurSel(0);
	}
	// Editing entry.
	else
	{
		// Find stat type in the combo box.
		m_cbTypes.CurSel(m_cbTypes.FindExact(m_oRow[CTmpStats::NAME]));
	}

	// Initialise the fields with data.
	m_dtpDate.SetDate(CDate(m_oRow[CTmpStats::DATE]));
	m_ebValue.RealValue(m_oRow[CTmpStats::VALUE].GetDouble());
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

bool CStatisticDlg::OnOk()
{
	// Fetch field data.
	int    nRow   = m_cbTypes.ItemData(m_cbTypes.CurSel());
	CRow&  oRow   = m_oStatTypes[nRow];
	double dValue = m_ebValue.RealValue();

	// Save changes.
	m_oRow[CTmpStats::DATE]    = m_dtpDate.GetDate().GetDateInSecs();
	m_oRow[CTmpStats::TYPE_ID] = oRow[CStatTypes::ID];
	m_oRow[CTmpStats::VALUE]   = dValue;
	m_oRow[CTmpStats::NAME]    = oRow[CStatTypes::NAME];

	return true;
}
