/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		VIEWSBAR.CPP
** COMPONENT:	The Application.
** DESCRIPTION:	CViewsBar class definition.
**
*******************************************************************************
*/

#include "AppHeaders.hpp"

// The number of views.
const int NUM_VIEWS = 7;

// The list of views.
static const char* apszViewNames[NUM_VIEWS] = 
{
	"Members", "Fixtures", "Balance Sheet", "Accounts", "Team Sheets", "Opponents", "Referees"
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

CViewsBar::CViewsBar()
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

CViewsBar::~CViewsBar()
{
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

void CViewsBar::GetCreateParams(WNDCREATE& rParams)
{
	// Get base class settings.
	// NB: Skip ListBox settings as we override them.
	CCtrlWnd::GetCreateParams(rParams);

	// Override any settings.
	rParams.pszClassName = "LISTBOX";
	rParams.dwExStyle   |= WS_EX_CLIENTEDGE;
	rParams.dwStyle     |= LBS_OWNERDRAWFIXED | LBS_NOINTEGRALHEIGHT;
	rParams.dwStyle     |= LBS_NOTIFY | WS_VSCROLL;
}

/******************************************************************************
** Method:		OnCreate()
**
** Description:	Initialise the list view control with the choice of views.
**
** Parameters:	rcClient	The client rectangle.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CViewsBar::OnCreate(const CRect& rcClient)
{
	// Load the icons bitmap.
	m_bmpIcons.LoadRsc(IDB_VIEWS, RGB(255,0,255));

    CScreenDC DC;
    
    // Get the height of the default font.
    DC.Select(App.DefaultFont());
    CSize FontSize = DC.TextExtents("Ly");

	// Set the height of all items.
	ItemHeight(0, m_bmpIcons.Size().cy + FontSize.cy + (2*BORDER));

	// Add the view choices.
	for (int i = 0; i < NUM_VIEWS; i++)
		Add(apszViewNames[i]);
}

/******************************************************************************
** Method:		OnDrawItem()
**
** Description:	Draw the button.
**
** Parameters:	See DRAWITEMSTRUCT.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CViewsBar::OnDrawItem(uint iID, uint iAction, uint iState, CDC& rDC,
							uint iItem, const CRect& rcItem)
{
	// Repaint or Selection change?
	if ( (iAction & ODA_DRAWENTIRE) || (iAction & ODA_SELECT) )
	{
		CBrush oBgBrush;

		// Get background brush.
		if (iState & ODS_SELECTED)
			oBgBrush.Create(::GetSysColor(COLOR_BTNFACE));
		else
			oBgBrush.Create(::GetSysColor(COLOR_BTNSHADOW));

		// Paint item background.
		rDC.Fill(rcItem, oBgBrush);

		// Calculate the icon position.
		int nIconX = rcItem.left + ((rcItem.Width() - ICON_SIZE) / 2);
		int nIconY = rcItem.top + BORDER;

		// Calculate the source and destination rects.
		CRect rcSrc(ICON_SIZE * iItem, 0, (ICON_SIZE * iItem) + ICON_SIZE, ICON_SIZE);
		CRect rcDst(nIconX, nIconY, nIconX + ICON_SIZE, nIconY + ICON_SIZE);

		// Draw the icon.
		rDC.BitBlt(m_bmpIcons, rcSrc, rcDst);

		// Change fonts.
		rDC.Select(App.DefaultFont());
		rDC.TextColour((iState & ODS_SELECTED) ? GetSysColor(COLOR_BTNTEXT) : GetSysColor(COLOR_HIGHLIGHTTEXT));
		rDC.BkMode(TRANSPARENT);

		// Get the label.
		const char* pszLabel = apszViewNames[iItem];

		// Calculate its position.
		CSize  szText  = rDC.TextExtents(pszLabel);
		int    nLabelX = rcItem.left + ((rcItem.Width() - szText.cx) / 2);
		CPoint ptText(nLabelX, nIconY + ICON_SIZE);

		// Draw ihe label.
		rDC.TextOut(ptText, pszLabel);

		if (iState & ODS_SELECTED)
			rDC.Border3D(rcItem, true, true);
	}		
}

/******************************************************************************
** Method:		WndProc()
**
** Description:	Catch WM_ERASEBKGND to paint our own background.
**				
** Parameters:	Standard window procedure parameters.
**
** Returns:		LRESULT based on the message.
**
*******************************************************************************
*/

LRESULT CViewsBar::WndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	// Decode message.
	switch(iMsg)
	{
		// Draw window background.
		case WM_ERASEBKGND:
			{
				// Construct a device from the HDC.
				CScreenDC	DC((HDC) wParam);
				CBrush		oBkBrush(::GetSysColor(COLOR_BTNSHADOW));

				DC.Fill(ClientRect(), oBkBrush);

				// Don't forward to base class.
				MsgHandled(true);
				MsgResult(1);
				return 0;
			}
			break;

		// Call the default handler.
		default:
			break;
	}

	// Call the base class' handler.
	return CListBox::WndProc(hWnd, iMsg, wParam, lParam);
}
