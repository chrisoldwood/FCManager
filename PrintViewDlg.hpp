/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		PRINTVIEWDLG.HPP
** COMPONENT:	The Application.
** DESCRIPTION:	The CPrintViewDlg class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef PRINTVIEWDLG_HPP
#define PRINTVIEWDLG_HPP

/******************************************************************************
** 
** This is used when printing a view.
**
*******************************************************************************
*/

class CPrintViewDlg : public CDialog
{
public:
	//
	// Constructors/Destructor.
	//
	CPrintViewDlg(const CString& strViewName);
	
protected:
	//
	// Members.
	//
	CString			m_strViewName;
	CLabel			m_txtPrinter;
	CLabel			m_txtPort;

	CCheckBoxList	m_lvColumns;

	//
	// Message processors.
	//
	virtual void OnInitDialog();
	virtual bool OnOk();

	//
	// Control message processors.
	//
	void OnSelect();
	void OnMoveUp();
	void OnMoveDown();
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

#endif //PRINTVIEWDLG_HPP
