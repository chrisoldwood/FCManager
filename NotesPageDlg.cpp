/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		NOTESPAGEDLG.CPP
** COMPONENT:	The Application.
** DESCRIPTION:	CNotesPageDlg class definition.
**
*******************************************************************************
*/

#include "AppHeaders.hpp"
#include "NotesPageDlg.hpp"

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

CNotesPageDlg::CNotesPageDlg()
	: CPropertyPageDlg(IDD_NOTES_PAGE)
	, m_nNotesLen(0)
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

void CNotesPageDlg::OnInitDialog()
{
	ASSERT(m_nNotesLen > 0);

	// Initialise the control.
	m_ebNotes.Text(m_strNotes);
	m_ebNotes.TextLimit(m_nNotesLen);
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

bool CNotesPageDlg::OnOk()
{
	m_strNotes = m_ebNotes.Text();

	return true;
}
