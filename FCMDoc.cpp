/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		FCMDOC.CPP
** COMPONENT:	The Application.
** DESCRIPTION:	CFCMDoc class definition.
**
*******************************************************************************
*/

#include "AppHeaders.hpp"

/******************************************************************************
**
** File details.
**
*******************************************************************************
*/

// The file type magic number.
const uint32 FILE_FORMAT  = 0x464D4346;		// "FCMF"

// The current format version.
const uint32 FILE_VERSION = 0x00000A01;		// Alpha #1

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

CFCMDoc::CFCMDoc()
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

CFCMDoc::~CFCMDoc()
{
}

/******************************************************************************
** Method:		operator <<()
**
** Description:	Operator to read the data from a stream.
**
** Parameters:	rStream		The stream to read from.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CFCMDoc::operator <<(CStream& rStream)
{
	uint32	iFormat;
	uint16  iVersion;

	// Read the format and version.
	rStream >> iFormat;
	rStream >> iVersion;

	// Check the format and version.
	if (iFormat != FILE_FORMAT)
		rStream.Throw(CStreamException::E_FORMAT_INVALID);

	if (iVersion != FILE_VERSION)
		rStream.Throw(CStreamException::E_VERSION_INVALID);

	// Read the database data.
	m_oDB.Read(rStream);
}

/******************************************************************************
** Method:		operator >>()
**
** Description:	Operator to write the data to a stream.
**
** Parameters:	rStream		The stream to write to.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CFCMDoc::operator >>(CStream& rStream)
{
	uint32	iFormat  = FILE_FORMAT;
	uint16  iVersion = FILE_VERSION;

	// Write the format and version.
	rStream << iFormat;
	rStream << iVersion;

	// Write the database data.
	m_oDB.Write(rStream);
}

/******************************************************************************
** Methods:		Modified()
**
** Description:	Query if the data has been modified.
**
** Parameters:	None.
**
** Returns:		true or false.
**
*******************************************************************************
*/

bool CFCMDoc::Modified() const
{
	// Check the database tables.
	return m_oDB.Modified();
}
