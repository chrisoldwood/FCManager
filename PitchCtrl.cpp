/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		PITCHCTRL.CPP
** COMPONENT:	The Application.
** DESCRIPTION:	CPitchCtrl class definition.
**
*******************************************************************************
*/

#include "AppHeaders.hpp"

//
// Ratios (%) for sizing the various pitch markings.
//

// Ratio of pitch to subs bench.
const int PITCH_Y = 85;
const int BENCH_Y = 100 - PITCH_Y;

// Insets of touchline.
const int TOUCHLINE_X = 3;
const int TOUCHLINE_Y = 3;

// Insets of bench border.
const int SUBS_BENCH_X = 3;
const int SUBS_BENCH_Y = 3;

// Centre circle.
const int CENTRE_X = 25;
const int CENTRE_Y = 25;

// 6 yard box.
const int YARD6_BOX_X = 10;
const int YARD6_BOX_Y = 10;

// 18 yard box.
const int YARD18_BOX_X = 25;
const int YARD18_BOX_Y = 25;

// Penalty box arc.
const int PENALTY_ARC_X = 30;
const int PENALTY_ARC_Y = 25;

const int NUM_PLAYERS = 16;

// Player formations.
static int g_aiFormations[CPitchCtrl::NUM_FORMATIONS][NUM_PLAYERS][2] = 
{
//
//                    4-4-2
//
//    GK          LB          CB          CB
{ { 50,  6},  { 20, 25},  { 40, 25},  { 60, 25},
//    RB          LM          CM          CM
  { 80, 25},  { 20, 50},  { 40, 50},  { 60, 50},
//    RM          IL          IR          S1
  { 80, 50},  { 33, 70},  { 66, 70},  { 16, 95},
//    S2          S3          S4          S5
  { 32, 95},  { 48, 95},  { 66, 95},  { 82, 95} },

//
//                    5-3-2
//
//    GK          LB          CB          CB
{ { 50,  6},  { 20, 25},  { 40, 25},  { 60, 25},
//    RB          LM          CM          CM
  { 80, 25},  { 20, 50},  { 40, 50},  { 60, 50},
//    RM          IL          IR          S1
  { 80, 50},  { 33, 70},  { 66, 70},  { 20, 90},
//    S2          S3          S4          S5
  { 40, 90},  { 60, 90},  { 80, 90},  { 90, 90} }
};


/******************************************************************************
** Method:		Constructor.
**
** Description:	.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

CPitchCtrl::CPitchCtrl(CRow& oRow, CTable& oMembers)
	: m_oRow(oRow)
	, m_oMembers(oMembers)
	, m_oBkBrush(RGB(0, 127, 0))
	, m_eFormation(F_4_4_2)
{
}

/******************************************************************************
** Method:		Destructor.
**
** Description:	.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

CPitchCtrl::~CPitchCtrl()
{
}

/******************************************************************************
** Method:		GetClassParams()
**
** Description:	Template method to get the window creation data.
**
** Parameters:	rParams		The create structure to fill.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CPitchCtrl::GetClassParams(WNDCLASS& rParams)
{
	// Get base class settings.
	CCtrlWnd::GetClassParams(rParams);

	// Override any settings.
	rParams.hbrBackground = (HBRUSH) (COLOR_WINDOW + 1);
	rParams.lpszClassName = "PitchCtrl";
}

/******************************************************************************
** Method:		GetCreateParams()
**
** Description:	Template method to get the window creation data.
**
** Parameters:	rParams		The create structure to fill.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CPitchCtrl::GetCreateParams(WNDCREATE& rParams)
{
	// Get base class settings.
	CCtrlWnd::GetCreateParams(rParams);

	// Override any settings.
	rParams.pszClassName = "PitchCtrl";
}

/******************************************************************************
** Method:		OnCreate()
**
** Description:	Creates the controls.
**
** Parameters:	rcClient	The client rectangle.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CPitchCtrl::OnCreate(const CRect& /*rcClient*/)
{
}

/******************************************************************************
** Method:		OnEraseBackground()
**
** Description:	Window background needs repainting
**
** Parameters:	rDC		The device to paint on.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CPitchCtrl::OnEraseBackground(CDC& rDC)
{
	DrawBackground(rDC, ClientRect());
}

/******************************************************************************
** Method:		OnPaint()
**
** Description:	Paints the toolbar background.
**
** Parameters:	rDC		The device to paint on.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CPitchCtrl::OnPaint(CDC& rDC)
{
	CRect rcClient = ClientRect();

	// Use white pen for pitch markings.
	rDC.Select(CBrush(NULL_BRUSH));
	rDC.Select(CPen(WHITE_PEN));

	DrawMarkings(rDC, rcClient);

	rDC.Select(CBrush(BLACK_BRUSH));

	DrawPlayers(rDC, rcClient);
}

/******************************************************************************
** Method:		DrawBackground()
**
** Description:	Draw the pitch background.
**				NB: Assumes the DC is already setup.
**
** Parameters:	rDC		The device to paint on.
**				rcPitch	The rectangle defining the pitch boundary.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CPitchCtrl::DrawBackground(CDC& rDC, const CRect& rcPitch)
{
	rDC.Fill(rcPitch, m_oBkBrush);
}

/******************************************************************************
** Method:		DrawMarkings()
**
** Description:	Draw the pitch markings, i.e. penatly area, centre circle and
**				subs bench.
**				NB: Assumes the DC is already setup.
**
** Parameters:	rDC		The device to paint on.
**				rcPitch	The rectangle defining the pitch boundary.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CPitchCtrl::DrawMarkings(CDC& rDC, const CRect& rcPitch)
{
	// Calculate pitch and subs bench areas.
	int nPitchY = (rcPitch.Height() * PITCH_Y) / 100;
	int nBenchY = (rcPitch.Height() * BENCH_Y) / 100;

	CRect rcField(rcPitch);
	CRect rcBench(rcPitch);

	rcField.bottom = rcField.top    + nPitchY;
	rcBench.top    = rcBench.bottom - nBenchY;

	// Calculate pitch touchline.
	int nTouchLineX = (rcField.Width()  * TOUCHLINE_X) / 100;
	int nTouchLineY = (rcField.Height() * TOUCHLINE_Y) / 100;

	rcField.left   += nTouchLineX;
	rcField.top    += nTouchLineY;
	rcField.right  -= nTouchLineX;
	rcField.bottom -= nTouchLineY;

	// Calculate bench border.
	int nBenchLineX = (rcBench.Width()  * SUBS_BENCH_X) / 100;
	int nBenchLineY = (rcBench.Height() * SUBS_BENCH_Y) / 100;

	rcBench.left   += nBenchLineX;
	rcBench.top    += nBenchLineY;
	rcBench.right  -= nBenchLineX;
	rcBench.bottom -= 0;

	// Calculate centre circle.
	CPoint ptCircCentre(rcField.Centre().x, rcField.bottom);
	int    nCircleX = (rcField.Width()  * CENTRE_X) / 100;
	int    nCircleY = (rcField.Height() * CENTRE_Y) / 100;
	CRect  rcCircle(ptCircCentre, ptCircCentre);

	rcCircle.left   -= nCircleX;
	rcCircle.top    -= nCircleY;
	rcCircle.right  += nCircleX;
	rcCircle.bottom += nCircleY;
	
	// Calculate 6 yard box.
	CPoint pt6YBCentre(rcField.Centre().x, rcField.top);
	int    n6YardBoxX = (rcField.Width()  * YARD6_BOX_X) / 100;
	int    n6YardBoxY = (rcField.Height() * YARD6_BOX_Y) / 100;
	CRect  rc6YardBox(pt6YBCentre, pt6YBCentre);

	rc6YardBox.left   -= n6YardBoxX;
	rc6YardBox.top    -= 0;
	rc6YardBox.right  += n6YardBoxX;
	rc6YardBox.bottom += n6YardBoxY;

	// Calculate 18 yard box.
	CPoint pt18YBCentre(rcField.Centre().x, rcField.top);
	int    n18YardBoxX = (rcField.Width()  * YARD18_BOX_X) / 100;
	int    n18YardBoxY = (rcField.Height() * YARD18_BOX_Y) / 100;
	CRect  rc18YardBox(pt18YBCentre, pt18YBCentre);

	rc18YardBox.left   -= n18YardBoxX;
	rc18YardBox.top    -= 0;
	rc18YardBox.right  += n18YardBoxX;
	rc18YardBox.bottom += n18YardBoxY;

	// Calculate penalty arc.
	CPoint ptPenCentre(rcField.Centre().x, rc18YardBox.bottom); 
	int    nPenArcX = (rc18YardBox.Width()  * PENALTY_ARC_X) / 100;
	int    nPenArcY = (rc18YardBox.Height() * PENALTY_ARC_Y) / 100;
	CRect  rcPenArc(ptPenCentre, ptPenCentre);

	rcPenArc.left   -= nPenArcX;
	rcPenArc.top    -= nPenArcY;
	rcPenArc.right  += nPenArcX;
	rcPenArc.bottom += nPenArcY;

	// Draw pitch markings.
	rDC.Rectangle(rcField);
	rDC.Rectangle(rcBench);
	rDC.Arc(rcCircle, CPoint(rcCircle.right, ptCircCentre.y), CPoint(rcCircle.left, ptCircCentre.y));
	rDC.Rectangle(rc6YardBox);
	rDC.Rectangle(rc18YardBox);
	rDC.Arc(rcPenArc, CPoint(rcPenArc.left, ptPenCentre.y), CPoint(rcPenArc.right, ptPenCentre.y));
}

/******************************************************************************
** Method:		DrawPlayers()
**
** Description:	Draw the players according to the current formation.
**				NB: Assumes the DC is already setup.
**
** Parameters:	rDC		The device to paint on.
**				rcPitch	The rectangle defining the pitch boundary.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CPitchCtrl::DrawPlayers(CDC& rDC, const CRect& rcPitch)
{
	CSize dmPitch = rcPitch.Size();

	for (int i = 0; i < NUM_PLAYERS; i++)
	{
		// Calculate players centrepoint.
		CPoint ptCentre;

		ptCentre.x = (dmPitch.cx * g_aiFormations[m_eFormation][i][0]) / 100;
		ptCentre.y = (dmPitch.cy * g_aiFormations[m_eFormation][i][1]) / 100;

		// Create player rect.
		CRect rcPlayer(ptCentre, ptCentre);

		rcPlayer.Inflate(10);

		// Draw it.
		rDC.Rectangle(rcPlayer);
	}
}
