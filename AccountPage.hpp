/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		ACCOUNTPAGE.HPP
** COMPONENT:	The Application.
** DESCRIPTION:	The CAccountPage class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef ACCOUNTPAGE_HPP
#define ACCOUNTPAGE_HPP

/******************************************************************************
** 
** This dialog is used to enter/edit an accounts details.
**
*******************************************************************************
*/

class CAccountPage : public CPropertyPage
{
public:
	//
	// Constructors/Destructor.
	//
	CAccountPage(CRow& oRow);
	
protected:
	//
	// Members.
	//
	CRow&			m_oRow;

	CString			m_strName;
	int				m_nType;
	int				m_nTotal;

	CEditBox		m_ebName;
	CDecimalBox		m_ebBalance;
	CRadioBtn		m_rbFixed;
	CRadioBtn		m_rbVariable;
	CListView		m_lvTrans;

	//
	// Message processors.
	//
	virtual void OnInitDialog();
	virtual bool OnValidate();
	virtual bool OnOk();

	void OnFixed();
	void OnVariable();
	void OnAddTrans();
	void OnEditTrans();
	void OnDelTrans();
	LRESULT OnDblClick(NMHDR&);

	//
	// Internal methods.
	//
//	void RefreshTrans();
//	void UpdateTransBtns();
//	void UpdateTransTotal();
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

#endif //ACCOUNTPAGE_HPP
