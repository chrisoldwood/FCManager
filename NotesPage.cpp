/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		NOTESPAGE.CPP
** COMPONENT:	The Application.
** DESCRIPTION:	CNotesPage class definition.
**
*******************************************************************************
*/

#include "Common.hpp"
#include "NotesPage.hpp"
#include <MDBL/Row.hpp>

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

CNotesPage::CNotesPage(CRow& oRow, int nColumn, int nMaxLen)
	: CPropertyPage(IDD_NOTES_PAGE)
	, m_oRow(oRow)
	, m_nColumn(nColumn)
	, m_strNotes(oRow[nColumn])
	, m_nMaxLen(nMaxLen)
{
	DEFINE_CTRL_TABLE
		CTRL(IDC_NOTES,	&m_ebNotes)
	END_CTRL_TABLE

	DEFINE_GRAVITY_TABLE
		CTRLGRAV(IDC_NOTES, LEFT_EDGE, TOP_EDGE, RIGHT_EDGE, BOTTOM_EDGE)
	END_GRAVITY_TABLE
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

void CNotesPage::OnInitDialog()
{
	ASSERT(m_nMaxLen > 0);

	// Initialise the control.
	m_ebNotes.Text(m_strNotes);
	m_ebNotes.TextLimit(m_nMaxLen);
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

bool CNotesPage::OnValidate()
{
	m_strNotes = m_ebNotes.Text();

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

bool CNotesPage::OnOk()
{
	m_oRow[m_nColumn] = m_strNotes;

	return true;
}

/******************************************************************************
** Method:		OnActivate()
**
** Description:	The page is being (de)activated. Remove the text selection.
**
** Parameters:	bActivating		Being (de)activated?
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CNotesPage::OnActivate(bool bActivating)
{
	if (bActivating)
		m_ebNotes.PostMessage(EM_SETSEL, static_cast<WPARAM>(-1), static_cast<WPARAM>(-1));
}
