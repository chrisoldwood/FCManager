/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		EXPENSETYPESDLG.HPP
** COMPONENT:	The Application.
** DESCRIPTION:	The CExpenseTypesDlg class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef EXPENSETYPESDLG_HPP
#define EXPENSETYPESDLG_HPP

/******************************************************************************
** 
** This dialog is used to maintain the expense types.
**
*******************************************************************************
*/

class CExpenseTypesDlg : public CDialog
{
public:
	//
	// Constructors/Destructor.
	//
	CExpenseTypesDlg(CExpenseTypes& oTypes, CValueSet& oUsed);
	
protected:
	//
	// Members.
	//
	CListBox		m_lbTypes;

	CExpenseTypes&	m_oTypes;
	CValueSet&		m_oUsed;
	
	//
	// Message processors.
	//
	virtual void OnInitDialog();
	virtual bool OnCancel();

	void OnAdd();
	void OnEdit();
	void OnDelete();
	void OnSelectType();

	//
	// Internal methods.
	//
	void  UpdateUI();
	CRow& ItemData(int nItem);
	bool  IsTypeInUse(int nID);
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

inline CRow& CExpenseTypesDlg::ItemData(int nItem)
{
	ASSERT( (nItem >= 0) && (nItem < m_lbTypes.Count()) );

	return *((CRow*)m_lbTypes.ItemPtr(nItem));
}

#endif //EXPENSETYPESDLG_HPP
