/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		TEAMSELDLG.HPP
** COMPONENT:	The Application.
** DESCRIPTION:	The CTeamSelDlg class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef TEAMSELDLG_HPP
#define TEAMSELDLG_HPP

/******************************************************************************
** 
** This dialog is used to edit the team selection.
**
*******************************************************************************
*/

class CTeamSelDlg : public CDialog
{
public:
	//
	// Constructors/Destructor.
	//
	CTeamSelDlg(CRow& oTeamSel, CTable& oMembers, bool bEditing);
	
	//
	// Members.
	//
	CRow&	m_oTeamSel;
	
protected:
	//
	// Members.
	//
	bool			m_bEditing;

	CTable&			m_oMembers;
	CDateTimePicker	m_dtpDate;
	CComboBox		m_cbOpponent;
	CComboBox		m_cbTeamFilter;
	CComboBox		m_cbPosFilter;
	CListBox		m_lbPlayer;
	CComboBox		m_cbFormation;
	CPitchCtrl		m_oPitch;
	CNotesDlg		m_oNotesDlg;
	int				m_nTeamFilter;
	int				m_nPosFilter;
	int				m_nFormation;
	
	//
	// Message handlers.
	//
	virtual void OnInitDialog();
	virtual bool OnOk();
	virtual bool OnCancel();
	        void OnNotes();

	void OnSelectTeamFilter();
	void OnSelectPosFilter();
	void OnSelectPlayer();
	void OnSelectFormation();

	//
	// Internal helpers.
	//
	void RefreshPlayerList();
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

#endif //TEAMSELDLG_HPP
