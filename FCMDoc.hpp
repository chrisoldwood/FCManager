/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		FCMDOC.HPP
** COMPONENT:	The Application.
** DESCRIPTION:	The CFCMDoc class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef FCMDOC_HPP
#define FCMDOC_HPP

// General limits.
const int MAX_CLUB_TEAMS = 3;
const int MAX_POSITIONS  = 4;

/******************************************************************************
** 
** The application document class.
**
*******************************************************************************
*/

class CFCMDoc : public CSDIDoc
{
public:
	//
	// Constructors/Destructor.
	//
	CFCMDoc();
	~CFCMDoc();

	//
	// Persistance methods.
	//
	virtual bool Modified() const;

	virtual void operator <<(CStream& rStream);
	virtual void operator >>(CStream& rStream);

	//
	// Members.
	//
	CFCMDB	m_oDB;
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

#endif //FCMDOC_HPP
