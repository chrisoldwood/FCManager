/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		PITCHCTRL.HPP
** COMPONENT:	The Application.
** DESCRIPTION:	The CPitchCtrl class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef PITCHCTRL_HPP
#define PITCHCTRL_HPP

/******************************************************************************
** 
** This custom control is used to display a pitch and players.
**
*******************************************************************************
*/

class CPitchCtrl : public CCtrlWnd
{
public:
	//
	// Constructors/Destructor.
	//
	CPitchCtrl(CRow& oRow, CTable& oMembers);
	~CPitchCtrl();
	
	// Player formations.
	enum Formation
	{
		F_4_4_2,
		F_5_3_2,
		NUM_FORMATIONS,
	};

protected:
	//
	// Members.
	//
	CRow&		m_oRow;
	CTable&		m_oMembers;
	CBrush		m_oBkBrush;
	Formation	m_eFormation;

	//
	// Window creation template methods.
	//
	virtual void GetClassParams(WNDCLASS& rParams);
	virtual void GetCreateParams(WNDCREATE& rParams);

	//
	// Message processors.
	//
	virtual void OnCreate(const CRect& rcClient);
	virtual	void OnEraseBackground(CDC& rDC);
	virtual void OnPaint(CDC& rDC);

	//
	// Internal helpers.
	//
	void DrawBackground(CDC& rDC, const CRect& rcPitch);
	void DrawMarkings(CDC& rDC, const CRect& rcPitch);
	void DrawPlayers(CDC& rDC, const CRect& rcPitch);
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

#endif //PITCHCTRL_HPP
