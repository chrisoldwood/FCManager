/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		OPPONENTPAGE.HPP
** COMPONENT:	The Application.
** DESCRIPTION:	The COpponentPage class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef OPPONENTPAGE_HPP
#define OPPONENTPAGE_HPP

/******************************************************************************
** 
** This dialog is used to enter/edit an opponents club details.
**
*******************************************************************************
*/

class COpponentPage : public CPropertyPage
{
public:
	//
	// Constructors/Destructor.
	//
	COpponentPage(CRow& oRow);
	
protected:
	//
	// Members.
	//
	CRow&		m_oRow;

	CString		m_strClubName;
	CString		m_strGround;
	CString		m_strStdColours;
	CString		m_strAltColours;

	CEditBox	m_ebClubName;
	CEditBox	m_ebGround;
	CEditBox	m_ebStdColours;
	CEditBox	m_ebAltColours;

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

#endif //OPPONENTPAGE_HPP
