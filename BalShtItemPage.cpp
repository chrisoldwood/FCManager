/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		BALSHTITEMPAGE.CPP
** COMPONENT:	The Application.
** DESCRIPTION:	CBalShtItemPage class definition.
**
*******************************************************************************
*/

#include "AppHeaders.hpp"
#include "BalShtItemPage.hpp"

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

CBalShtItemPage::CBalShtItemPage(CRow& oRow)
	: CPropertyPage(IDD_BALSHEET_PAGE)
	, m_oRow(oRow)
	, m_strName(oRow[CBalSheet::NAME])
	, m_tDate(oRow[CBalSheet::DATE])
	, m_nType(oRow[CBalSheet::TYPE])
{
	DEFINE_CTRL_TABLE
		CTRL(IDC_NAME,	&m_ebName )
		CTRL(IDC_DATE,	&m_dtpDate)
		CTRL(IDC_TYPE,	&m_cbType )
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

void CBalShtItemPage::OnInitDialog()
{
	// Initialise the controls.
	m_ebName.TextLimit(CBalSheet::NAME_LEN);
	m_dtpDate.Format("ddd' 'dd'/'MM'/'yyyy");

	m_cbType.Add("Other");
	m_cbType.Add("Match");
	m_cbType.Add("Training");

	// Initialise the fields with data.
	m_ebName.Text(m_strName);
	m_dtpDate.SetDate(m_tDate);
	m_cbType.CurSel(m_nType);
}

/******************************************************************************
** Method:		OnValidate()
**
** Description:	Validate the data.
**
** Parameters:	None.
**
** Returns:		true or false.
**
*******************************************************************************
*/

bool CBalShtItemPage::OnValidate()
{
	m_strName = m_ebName.Text();
	m_tDate   = m_dtpDate.GetDate();
	m_nType   = m_cbType.CurSel();

	// At least the name supplied?
	if (m_ebName.TextLength() == 0)
	{
		AlertMsg("You must provide at least a name for the item");
		return false;
	}

	return true;
}

/******************************************************************************
** Method:		OnOk()
**
** Description:	Save the data.
**
** Parameters:	None.
**
** Returns:		true or false.
**
*******************************************************************************
*/

bool CBalShtItemPage::OnOk()
{
	m_oRow[CBalSheet::NAME] = m_strName;
	m_oRow[CBalSheet::DATE] = m_tDate;
	m_oRow[CBalSheet::TYPE] = m_nType;

	return true;
}
