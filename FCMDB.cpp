/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		FCMDB.CPP
** COMPONENT:	The Application.
** DESCRIPTION:	CFCMDB class definition.
**
*******************************************************************************
*/

#include "AppHeaders.hpp"

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

CFCMDB::CFCMDB()
	: m_oDetails(*this)
	, m_oMembers(*this)
	, m_oFixtures(*this)
	, m_oBalSheet(*this)
	, m_oOpponents(*this)
	, m_oReferees(*this)
{
	// Create the database schema.
	AddTable(m_oDetails);
	AddTable(m_oMembers);
	AddTable(m_oFixtures);
	AddTable(m_oBalSheet);
	AddTable(m_oOpponents);
	AddTable(m_oReferees);
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

CFCMDB::~CFCMDB()
{
}
