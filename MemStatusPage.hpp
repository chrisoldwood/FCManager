/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		MEMSTATUSPAGE.HPP
** COMPONENT:	The Application.
** DESCRIPTION:	The CMemStatusPage class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef MEMSTATUSPAGE_HPP
#define MEMSTATUSPAGE_HPP

/******************************************************************************
** 
** This is the property page used to display the members status.
**
*******************************************************************************
*/

class CMemStatusPage : public CPropertyPage
{
public:
	//
	// Constructors/Destructor.
	//
	CMemStatusPage(CRow& oRow);
	
protected:
	//
	// Members.
	//
	CRow&		m_oRow;

	bool		m_bIsRegistered;
	bool		m_bIsSenior;
	int			m_nTeam;
	int			m_nPosition;

	CCheckBox	m_ckIsRegistered;
	CCheckBox	m_ckIsSenior;
	CComboBox	m_cbTeam;
	CComboBox	m_cbPosition;

	//
	// Message processors.
	//
	virtual void OnInitDialog();
	virtual bool OnValidate();
	virtual bool OnOk();
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

#endif //MEMSTATUSPAGE_HPP
