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


#if !defined(AFX_ELECTSOFTDOC_H__69E5602A_562F_11D6_B47E_00B0D0CDB4FC__INCLUDED_)
#define AFX_ELECTSOFTDOC_H__69E5602A_562F_11D6_B47E_00B0D0CDB4FC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Count.h"
#include "PrintBallot.h"
#include "PrintRace.h"

class CElectSoftDoc : public CDocument
{
public:
	CElectSoftDoc() { m_pCount=NULL; }
	CString GetSignature() { return m_signature; }
	void UnloadRaces();
	BOOL RacesLoaded();
	BOOL FindStudent(CString RIN, CStudent*& pStudent) { return m_students.Lookup(RIN, pStudent); }
	void ReplaceCount(CCount* pCount);
	CStudent* GetNextStudentPosition(POSITION& pos);
	POSITION GetStartStudentPosition() { return m_students.GetStartPosition(); }
	BOOL StudentsLoaded() { return !m_students.IsEmpty(); }
	int LoadRaces(CStdioFile* pSF);
	int LoadStudents(CStdioFile* pSF, CString& Duplicate_RIN);
	void LockBallots() { m_BallotsLocked=true; SetModifiedFlag(); }
	CCount* GetCount() { return m_pCount; }
	void UnloadStudents();
	CPrintBallot* GetBallotAt(ClassYear year, int number) { return (CPrintBallot*)BallotArray(year)->GetAt(number); }
	int BallotCount(ClassYear year) { return BallotArray(year)->GetSize(); }
	void AddBallot(CPrintBallot* pPBallot);
	UINT GetBallotCount(ClassYear year) { return BallotArray(year)->GetSize(); }
	BOOL BallotsLocked() { return m_BallotsLocked; }
	BOOL BallotsUnlocked() { return !m_BallotsLocked; }
	BOOL Position();
	CPrintRace* GetRaceAt(ClassYear year, int position) { return (CPrintRace*)RaceArray(year)->GetAt(position); }
	int RaceCount(ClassYear year) { return RaceArray(year)->GetSize(); }
	UINT GetCurrYear() { return m_curr_year; }
	UINT GetClassYear(ClassYear year);
	void SetCurrYear(UINT curr_year) { m_curr_year=curr_year; SetModifiedFlag(); }
	void SetClassYear(ClassYear, UINT val);
	
protected:
	virtual void Serialize(CArchive& ar);
	virtual void DeleteContents();
	virtual BOOL OnNewDocument();
	virtual BOOL SaveModified();
	DECLARE_DYNCREATE(CElectSoftDoc)
	
private:
	BOOL LoadRace(CString string);
	BOOL ReadYearCode(CString code, ClassYear& year);
	BOOL PositionRace(CPrintRace* pPRace, UINT& col, UINT& row);
	BOOL LoadStudent(CString string, CString& Duplicate_RIN);
	BOOL IntegrateInfo();
	void Clean(CString& string);
	CObArray* BallotArray(ClassYear year);
	CObArray* RaceArray(ClassYear year);
	void DeleteRaceArray(ClassYear year);
	void DeleteBallotArray(ClassYear year);
	BOOL PositionRaces(ClassYear year);
	
	BOOL m_BallotsLocked;
	
	CObArray m_races_AL, m_races_FR, m_races_SO, m_races_JR, m_races_SR, m_races_GR;
	
	CObArray m_ballots_AL, m_ballots_FR, m_ballots_SO, m_ballots_JR, m_ballots_SR, m_ballots_GR;
	UINT m_curr_year, m_year_FR, m_year_SO, m_year_JR, m_year_SR;
	
	CMap<CString, CString, CStudent*, CStudent*> m_students;
	CCount* m_pCount;
	CString m_signature;
};

#endif // !defined(AFX_ELECTSOFTDOC_H__69E5602A_562F_11D6_B47E_00B0D0CDB4FC__INCLUDED_)