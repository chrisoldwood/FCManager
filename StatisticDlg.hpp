/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		STATISTICDLG.HPP
** COMPONENT:	The Application.
** DESCRIPTION:	The CStatisticDlg class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef STATISTICDLG_HPP
#define STATISTICDLG_HPP

/******************************************************************************
** 
** This dialog is used to add/edit a members statistics.
**
*******************************************************************************
*/

class CStatisticDlg : public CDialog
{
public:
	//
	// Constructors/Destructor.
	//
	CStatisticDlg(CStatTypes& oStatTypes, CRow& oRow, bool bEditing);
	
	//
	// Members.
	//
	CRow&	m_oRow;
	
protected:
	//
	// Members.
	//
	bool			m_bEditing;

	CDateTimePicker	m_dtpDate;
	CComboBox		m_cbTypes;
	CDecimalBox		m_ebValue;

	CStatTypes&		m_oStatTypes;

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

#endif //STATISTICDLG_HPP
