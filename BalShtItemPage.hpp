/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		BALSHTITEMPAGE.HPP
** COMPONENT:	The Application.
** DESCRIPTION:	The CBalShtItemPage class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef BALSHTITEMPAGE_HPP
#define BALSHTITEMPAGE_HPP

/******************************************************************************
** 
** This dialog is used to enter/edit a balance sheet items details.
**
*******************************************************************************
*/

class CBalShtItemPage : public CPropertyPage
{
public:
	//
	// Constructors/Destructor.
	//
	CBalShtItemPage(CRow& oRow);
	
protected:
	//
	// Members.
	//
	CRow&			m_oRow;

	CString			m_strName;
	CDate			m_tDate;
	int				m_nType;

	CEditBox		m_ebName;
	CDateTimePicker	m_dtpDate;
	CComboBox		m_cbType;

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

#endif //BALSHTITEMPAGE_HPP
