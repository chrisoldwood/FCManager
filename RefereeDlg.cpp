/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		REFEREEDLG.CPP
** COMPONENT:	The Application.
** DESCRIPTION:	CRefereeDlg class definition.
**
*******************************************************************************
*/

#include "AppHeaders.hpp"
#include "RefereeDlg.hpp"

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

CRefereeDlg::CRefereeDlg(CRow& oReferee, bool bEditing) : CDialog(IDD_REFEREE)
	, m_oReferee(oReferee)
	, m_bEditing(bEditing)
{
	DEFINE_CTRL_TABLE
		CTRL(IDC_SURNAME,			&m_ebSurname)
		CTRL(IDC_FORENAME,			&m_ebForename)
		CTRL(IDC_STD_PHONE,			&m_ebStdPhone)
		CTRL(IDC_ALT_PHONE,			&m_ebAltPhone)
		CTRL(IDC_EMAIL_ADDRESS,		&m_ebEmailAddr)
		CTRL(IDC_POSTAL_ADDRESS,	&m_ebPostalAddr)
	END_CTRL_TABLE

	DEFINE_CTRLMSG_TABLE
		CMD_CTRLMSG(IDC_NOTES, BN_CLICKED, OnNotes)
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

void CRefereeDlg::OnInitDialog()
{
	// Set the dialog title.
	Title((m_bEditing == true) ? "Edit Referee Details" : "Add A Referee");

	// Initialise the controls.
	m_ebSurname.TextLimit(CReferees::SURNAME_LEN);
	m_ebForename.TextLimit(CReferees::FORENAME_LEN);
	m_ebStdPhone.TextLimit(CReferees::PHONE_LEN);
	m_ebAltPhone.TextLimit(CReferees::PHONE_LEN);
	m_ebEmailAddr.TextLimit(CReferees::EMAIL_LEN);
	m_ebPostalAddr.TextLimit(CReferees::POSTAL_LEN);

	// Initialise the fields with data.
	m_ebSurname.Text(m_oReferee[CReferees::SURNAME]);
	m_ebForename.Text(m_oReferee[CReferees::FORENAME]);
	m_ebStdPhone.Text(m_oReferee[CReferees::STANDARD_PHONE]);
	m_ebAltPhone.Text(m_oReferee[CReferees::ALTERNATE_PHONE]);
	m_ebEmailAddr.Text(m_oReferee[CReferees::EMAIL_ADDRESS]);
	m_ebPostalAddr.Text(m_oReferee[CReferees::POSTAL_ADDRESS]);

	// Initialise the notes dialog.
	m_oNotesDlg.m_strNotes  = m_oReferee[CReferees::NOTES];
	m_oNotesDlg.m_nNotesLen = CReferees::NOTES_LEN;
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

bool CRefereeDlg::OnOk()
{
	// At least the surname supplied?
	if ( (m_ebSurname.TextLength() == 0) && (m_ebForename.TextLength() == 0) )
	{
		AlertMsg("You must provide either the Forename or Surname");
		return false;
	}

	CReferees& oTable = static_cast<CReferees&>(m_oReferee.Table());

	// Find referees with the same name but different ID.
	CResultSet oRS = oTable.Select(CWhereEqual(CReferees::FORENAME,  m_ebForename.Text())
								   & CWhereEqual(CReferees::SURNAME, m_ebSurname.Text())
								   & CWhereNotEqual(CReferees::ID,   m_oReferee[CReferees::ID]));

	// Referee already exists?
	if (oRS.Count() > 0)
	{
		AlertMsg("A referee with that name already exists");
		return false;
	}

	m_oReferee[CReferees::SURNAME]         = m_ebSurname.Text();
	m_oReferee[CReferees::FORENAME]        = m_ebForename.Text();
	m_oReferee[CReferees::STANDARD_PHONE]  = m_ebStdPhone.Text();
	m_oReferee[CReferees::ALTERNATE_PHONE] = m_ebAltPhone.Text();
	m_oReferee[CReferees::EMAIL_ADDRESS]   = m_ebEmailAddr.Text();
	m_oReferee[CReferees::POSTAL_ADDRESS]  = m_ebPostalAddr.Text();
	m_oReferee[CReferees::NOTES]           = m_oNotesDlg.m_strNotes;

	return true;
}

/******************************************************************************
** Method:		OnNotes()
**
** Description:	Show the notes editing dialog.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CRefereeDlg::OnNotes()
{
	m_oNotesDlg.RunModal(*this);
}
