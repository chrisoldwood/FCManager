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

// Teams per club.
enum ClubTeam
{
	TEAM_1ST,
	TEAM_2ND,
	TEAM_3RD,

	MAX_CLUB_TEAMS
};

// Positions.
enum Position
{
	GOALKEEPER,
	DEFENDER,
	MIDIFIELDER,
	ATTACKER,

	MAX_POSITIONS
};

// Formations.
enum Formation
{
	F_4_4_2,
	F_5_3_2,

	MAX_FORMATIONS
};

// Players per game.
const int MAX_PLAYERS = 16;

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
