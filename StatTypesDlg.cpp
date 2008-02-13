/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		STATTYPESDLG.CPP
** COMPONENT:	The Application.
** DESCRIPTION:	CStatTypesDlg class definition.
**
*******************************************************************************
*/

#include "Common.hpp"
#include "StatTypesDlg.hpp"
#include "StatTypeDlg.hpp"
#include "StatTypes.hpp"
#include <MDBL/ValueSet.hpp>

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

CStatTypesDlg::CStatTypesDlg(const CString& strType, CStatTypes& oTypes, CValueSet& oUsed)
	: CDialog(IDD_STAT_TYPES)
	, m_strType(strType)
	, m_oTypes(oTypes)
	, m_oUsed(oUsed)
{
	DEFINE_CTRL_TABLE
		CTRL(IDC_TYPES,	&m_lbTypes)
	END_CTRL_TABLE

	DEFINE_CTRLMSG_TABLE
		CMD_CTRLMSG(IDC_ADD,	BN_CLICKED,		&CStatTypesDlg::OnAdd       )
		CMD_CTRLMSG(IDC_EDIT,	BN_CLICKED,		&CStatTypesDlg::OnEdit      )
		CMD_CTRLMSG(IDC_DELETE,	BN_CLICKED,		&CStatTypesDlg::OnDelete    )
		CMD_CTRLMSG(IDC_TYPES,	LBN_SELCHANGE,	&CStatTypesDlg::OnSelectType)
	END_CTRLMSG_TABLE
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

void CStatTypesDlg::OnInitDialog()
{
	// Set the dialog title.
	Title(m_strType + TXT(" Statistic Types"));

	// Load the set of types.
	for (size_t i = 0; i < m_oTypes.RowCount(); i++)
	{
		CRow& oRow = m_oTypes[i];

		m_lbTypes.Add(oRow[CStatTypes::NAME], &oRow);
	}

	// Select the first by default.
	m_lbTypes.CurSel(0U);

	UpdateUI();
}

/******************************************************************************
** Method:		OnCancel()
**
** Description:	Validate the data and close the dialog.
**
** Parameters:	None.
**
** Returns:		true or false.
**
*******************************************************************************
*/

bool CStatTypesDlg::OnCancel()
{
	return true;
}

/******************************************************************************
** Method:		OnSelectType()
**
** Description:	Handle selection change in types listbox.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CStatTypesDlg::OnSelectType()
{
	UpdateUI();
}

/******************************************************************************
** Method:		OnAdd()
**
** Description:	Add a new type.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CStatTypesDlg::OnAdd()
{
	CRow&        oRow = m_oTypes.CreateRow();
	CStatTypeDlg Dlg(oRow);

	// Get stat type properties.
	if (Dlg.RunModal(*this) == IDOK)
	{
		// Add the row to the table and dialog.
		m_oTypes.InsertRow(oRow);
		m_lbTypes.Add(oRow[CStatTypes::NAME], &oRow);

		// Select if first item.
		if (m_lbTypes.Count() == 1)
			m_lbTypes.CurSel(0U);
	}
	else
	{
		delete &oRow;
	}

	UpdateUI();
}

/******************************************************************************
** Method:		OnEdit()
**
** Description:	Edit the selected type.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CStatTypesDlg::OnEdit()
{
	int          nSel = m_lbTypes.CurSel();
	CRow&        oRow = ItemData(nSel);
	CStatTypeDlg Dlg(oRow);

	// Get stat type properties.
	if (Dlg.RunModal(*this) == IDOK)
	{
		// Replace row.
		m_lbTypes.Delete(nSel);
		m_lbTypes.Add(oRow[CStatTypes::NAME], &oRow);
		m_lbTypes.RestoreSel(nSel);
	}

	UpdateUI();
}

/******************************************************************************
** Method:		OnDelete()
**
** Description:	Delete the selected type.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CStatTypesDlg::OnDelete()
{
	int   nSel = m_lbTypes.CurSel();
	CRow& oRow = ItemData(nSel);

	// Remove from dialog and table.
	m_lbTypes.Delete(nSel);
	m_lbTypes.RestoreSel(nSel);
	m_oTypes.DeleteRow(oRow);

	UpdateUI();
}

/******************************************************************************
** Method:		UpdateUI()
**
** Description:	Updates the button states.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CStatTypesDlg::UpdateUI()
{
	bool bSelection = (m_lbTypes.CurSel() != LB_ERR);
	bool bInUse     = true;

	if (bSelection)
	{
		CRow& oRow = ItemData(m_lbTypes.CurSel());

		bInUse = IsTypeInUse(oRow[CStatTypes::ID]);
	}

	Control(IDC_ADD).Enable(true);
	Control(IDC_EDIT).Enable(bSelection);
	Control(IDC_DELETE).Enable(bSelection && !bInUse);
}

/******************************************************************************
** Method:		IsTypeInUse()
**
** Description:	Queries if the given type is in use.
**
** Parameters:	nID		The ID of the type.
**
** Returns:		true or false.
**
*******************************************************************************
*/

bool CStatTypesDlg::IsTypeInUse(int nID)
{
	for (size_t i = 0; i < m_oUsed.Count(); i++)
	{
		if (m_oUsed[i].m_iValue == nID)
			return true;
	}

	return false;
}
