/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		STATSPAGEDLG.HPP
** COMPONENT:	The Application.
** DESCRIPTION:	The CStatsPageDlg class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef STATSPAGEDLG_HPP
#define STATSPAGEDLG_HPP

/******************************************************************************
** 
** This is the property page dialog used to display the stats.
**
*******************************************************************************
*/

class CStatsPageDlg : public CPropertyPageDlg
{
public:
	//
	// Constructors/Destructor.
	//
	CStatsPageDlg();
	
	//
	// Members.
	//

protected:
	//
	// Members.
	//
	CListView	m_lvStats;
	
	//
	// Message processors.
	//
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

#endif //STATSPAGEDLG_HPP
