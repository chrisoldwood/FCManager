/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		MEMBERDLG.HPP
** COMPONENT:	The Application.
** DESCRIPTION:	The CMemberDlg class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef MEMBERDLG_HPP
#define MEMBERDLG_HPP

#include "NamePageDlg.hpp"
#include "MbrStatusPageDlg.hpp"
#include "StatsPageDlg.hpp"
#include "NotesPageDlg.hpp"

/******************************************************************************
** 
** This dialog is used to enter/edit a members details.
**
*******************************************************************************
*/

class CMemberDlg : public CPropertyDlg
{
public:
	//
	// Constructors/Destructor.
	//
	CMemberDlg(CRow& oRow, bool bEditing);
	
	//
	// Members.
	//
	CRow&	m_oRow;
	
protected:
	//
	// Members.
	//
	bool				m_bEditing;

	CNamePageDlg		m_oNamePage;
	CMbrStatusPageDlg	m_oStatusPage;
	CStatsPageDlg		m_oStatsPage;
	CNotesPageDlg		m_oNotesPage;

	//
	// Message processors.
	//
	virtual void OnInitDialog();
	virtual bool OnOk();
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

#endif //MEMBERDLG_HPP
