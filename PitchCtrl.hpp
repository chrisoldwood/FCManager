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
	CPitchCtrl(CMembers& oMembers);
	~CPitchCtrl();

	//
	// Methods.
	//
	void SetFormation(Formation eFormation);
	void SetPlayer(int nPos, int nID);

protected:
	//
	// Members.
	//
	int			m_aiPlayers[MAX_PLAYERS];
	CString		m_astrPlayers[MAX_PLAYERS];
	CMembers&	m_oMembers;
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

inline void CPitchCtrl::SetFormation(Formation eFormation)
{
	m_eFormation = eFormation;
	Invalidate();
}

#endif //PITCHCTRL_HPP
