/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		MEMBERDLG.CPP
** COMPONENT:	The Application.
** DESCRIPTION:	CMemberDlg class definition.
**
*******************************************************************************
*/

#include "AppHeaders.hpp"
#include "MemberDlg.hpp"

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

CMemberDlg::CMemberDlg(CRow& oRow, bool bEditing)
	: CPropertyDlg(IDD_PROPERTY, IDC_TAB_CTRL)
	, m_oRow(oRow)
	, m_bEditing(bEditing)
	, m_oNamePage()
	, m_oStatsPage()
	, m_oNotesPage()
{
	DEFINE_PAGE_TABLE
		PAGE(&m_oNamePage,		"Name && Address" )
		PAGE(&m_oStatusPage,	"Status"          )
		PAGE(&m_oStatsPage,		"Statistics"      )
		PAGE(&m_oNotesPage,		"Additional Notes")
	END_PAGE_TABLE

	// Initialise the name and address page.
	m_oNamePage.m_strSurname     = m_oRow[CMembers::SURNAME].GetString();
	m_oNamePage.m_strForename    = m_oRow[CMembers::FORENAME].GetString();
	m_oNamePage.m_strStdPhone    = m_oRow[CMembers::STANDARD_PHONE].GetString();
	m_oNamePage.m_strAltPhone    = m_oRow[CMembers::ALTERNATE_PHONE].GetString();
	m_oNamePage.m_strEmailAddr   = m_oRow[CMembers::EMAIL_ADDRESS].GetString();
	m_oNamePage.m_strPostalAddr  = m_oRow[CMembers::POSTAL_ADDRESS].GetString();

	m_oNamePage.m_nSurnameLen    = CMembers::SURNAME_LEN;
	m_oNamePage.m_nForenameLen   = CMembers::FORENAME_LEN;
	m_oNamePage.m_nStdPhoneLen   = CMembers::PHONE_LEN;
	m_oNamePage.m_nAltPhoneLen   = CMembers::PHONE_LEN;
	m_oNamePage.m_nEmailAddrLen  = CMembers::EMAIL_LEN;
	m_oNamePage.m_nPostalAddrLen = CMembers::POSTAL_LEN;

	// Initialise the status page.
	m_oStatusPage.m_bIsRegistered = m_oRow[CMembers::IS_REGISTERED].GetBool();
	m_oStatusPage.m_bIsSenior     = m_oRow[CMembers::IS_SENIOR].GetBool();
	m_oStatusPage.m_nTeam         = m_oRow[CMembers::USUAL_TEAM];
	m_oStatusPage.m_nPosition     = m_oRow[CMembers::USUAL_POSITION];

	// Initialise the stats page.

	// Initialise the notes page.
	m_oNotesPage.m_strNotes  = m_oRow[CMembers::NOTES].GetString();

	m_oNotesPage.m_nNotesLen = CMembers::NOTES_LEN;
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

void CMemberDlg::OnInitDialog()
{
	// Set the dialog title.
	Title((m_bEditing == true) ? "Edit Member Details" : "Add A Member");
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

bool CMemberDlg::OnOk()
{
	// Get base class to process the pages.
	if (!CPropertyDlg::OnOk())
		return false;

/*
	// At least the surname supplied?
	if ( (m_ebSurname.TextLength() == 0) && (m_ebForename.TextLength() == 0) )
	{
		AlertMsg("You must provide either the Forename or Surname");
		return false;
	}

	CMembers& oTable = static_cast<CMembers&>(m_oMember.Table());

	// Find members with the same name but different ID.
	CResultSet oRS = oTable.Select(CWhereEqual(CMembers::FORENAME,  m_ebForename.Text())
								   & CWhereEqual(CMembers::SURNAME, m_ebSurname.Text())
								   & CWhereNotEqual(CMembers::ID,   m_oMember[CMembers::ID]));

	// Member already exists?
	if (oRS.Count() > 0)
	{
		AlertMsg("A member with that name already exists");
		return false;
	}
*/
	// Fetch the data from the pages.
	m_oRow[CMembers::SURNAME]         = m_oNamePage.m_strSurname;
	m_oRow[CMembers::FORENAME]        = m_oNamePage.m_strForename;
	m_oRow[CMembers::STANDARD_PHONE]  = m_oNamePage.m_strStdPhone;
	m_oRow[CMembers::ALTERNATE_PHONE] = m_oNamePage.m_strAltPhone;
	m_oRow[CMembers::EMAIL_ADDRESS]   = m_oNamePage.m_strEmailAddr;
	m_oRow[CMembers::POSTAL_ADDRESS]  = m_oNamePage.m_strPostalAddr;
	m_oRow[CMembers::IS_REGISTERED]   = m_oStatusPage.m_bIsRegistered;
	m_oRow[CMembers::IS_SENIOR]       = m_oStatusPage.m_bIsSenior;
	m_oRow[CMembers::USUAL_TEAM]      = m_oStatusPage.m_nTeam;
	m_oRow[CMembers::USUAL_POSITION]  = m_oStatusPage.m_nPosition;
	m_oRow[CMembers::NOTES]           = m_oNotesPage.m_strNotes;

	return true;
}

