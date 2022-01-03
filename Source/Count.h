// ********************************************************************************
// **                                                                            **
// ** Copyright 2003 Edward F. Behn, Jr.                                         **
// **                                                                            **
// ** This file is part of Electsoft.                                            **
// **                                                                            **
// ** Electsoft is free software; you can redistribute it and/or modify it under **
// ** the terms of the GNU General Public License as published by the Free       **
// ** Software Foundation; either version 2 of the License, or (at your option)  **
// ** any later version.                                                         **
// **                                                                            **
// ** Electsoft is distributed in the hope that it will be useful, but WITHOUT   **
// ** ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or      **
// ** FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for  **
// ** more details.                                                              **
// **                                                                            **
// ** You should have received a copy of the GNU General Public License along    **
// ** with Electsoft; if not, write to the Free Software Foundation, Inc.,       **
// ** 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA                    **
// **                                                                            **
// ** ElectSoft was written for use by the Rules and Elections Committee of the  **
// ** RPI Student Senate.  It may, however, be used by any organization.         **
// **                                                                            **
// ********************************************************************************


#if !defined(AFX_COUNT_H__618A6760_9106_11D6_B481_00B0D0CDB4FC__INCLUDED_)
#define AFX_COUNT_H__618A6760_9106_11D6_B481_00B0D0CDB4FC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ScanRace.h"
#include "ScanBallot.h"

class CElectSoftDoc;

class CCount
{
public:
	void SetModifiedFlag(BOOL bModified=true) { m_bModified=bModified; }
	BOOL SaveModified();
	BOOL Open(CStdioFile* pSF);
	void Save(BOOL AskForPath);
	CString GetTitle() { return m_title; }
	void SetTitle(CString title) { m_title=title; }
	CCount(CElectSoftDoc* pDoc);
	~CCount();
	int RaceCount(ClassYear year) { return RaceArray(year)->GetSize(); }
	CScanRace* GetRaceAt(ClassYear year, int position) { return RaceArray(year)->GetAt(position); }
	int BallotCount(ClassYear year) { return BallotArray(year)->GetSize(); }
	CScanBallot* GetBallotAt(ClassYear year, int number) { return BallotArray(year)->GetAt(number); }
private:
	BOOL ReadYearCode(CString code, ClassYear& year);
	BOOL ProcessFileLine(CString string);
	CScanRaceArray* RaceArray(ClassYear year);
	CScanBallotArray* BallotArray(ClassYear year);
	void AttachBallotArray(CElectSoftDoc* pDoc, ClassYear year);
	void AttachRaceArray(CElectSoftDoc* pDoc, ClassYear year);
	void DeleteRaceArray(ClassYear year);
	void DeleteBallotArray(ClassYear year);
	
	CString m_title;
	CString m_pathname;
	CScanBallotArray m_ballots_AL, m_ballots_FR, m_ballots_SO, m_ballots_JR, m_ballots_SR, m_ballots_GR;
	CScanRaceArray m_races_AL, m_races_FR, m_races_SO, m_races_JR, m_races_SR, m_races_GR;
	CString m_signature;
	BOOL m_bModified;
};

#endif // !defined(AFX_COUNT_H__618A6760_9106_11D6_B481_00B0D0CDB4FC__INCLUDED_)