/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		MBRSTATUSPAGEDLG.HPP
** COMPONENT:	The Application.
** DESCRIPTION:	The CMbrStatusPageDlg class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef MBRSTATUSPAGEDLG_HPP
#define MBRSTATUSPAGEDLG_HPP

/******************************************************************************
** 
** This is the property page dialog used to display the members status.
**
*******************************************************************************
*/

class CMbrStatusPageDlg : public CPropertyPageDlg
{
public:
	//
	// Constructors/Destructor.
	//
	CMbrStatusPageDlg();
	
	//
	// Members.
	//
	bool	m_bIsRegistered;
	bool	m_bIsSenior;
	int		m_nTeam;
	int		m_nPosition;
	
protected:
	//
	// Members.
	//
	CCheckBox	m_ckIsRegistered;
	CCheckBox	m_ckIsSenior;
	CComboBox	m_cbTeam;
	CComboBox	m_cbPosition;

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

#endif //MBRSTATUSPAGEDLG_HPP
