/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		NOTESDLG.CPP
** COMPONENT:	The Application.
** DESCRIPTION:	CNotesDlg class definition.
**
*******************************************************************************
*/

#include "Common.hpp"
#include "NotesDlg.hpp"

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

CNotesDlg::CNotesDlg() : CDialog(IDD_NOTES)
	, m_nNotesLen(0)
{
	DEFINE_CTRL_TABLE
		CTRL(IDC_NOTES,	&m_ebNotes)
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

void CNotesDlg::OnInitDialog()
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

bool CNotesDlg::OnOk()
{
	m_strNotes = m_ebNotes.Text();

	return true;
}
