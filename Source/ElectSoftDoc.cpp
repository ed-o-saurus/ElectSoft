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


#include "stdafx.h"
#include "ElectSoft.h"
#include "ElectSoftDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CElectSoftDoc, CDocument)

void CElectSoftDoc::DeleteContents() 
{
	UnloadRaces(); UnloadStudents(); ReplaceCount(NULL);
	
	DeleteBallotArray(AL);
	DeleteBallotArray(FR);
	DeleteBallotArray(SO);
	DeleteBallotArray(JR);
	DeleteBallotArray(SR);
	DeleteBallotArray(GR);
	
	CDocument::DeleteContents();
}

void CElectSoftDoc::Serialize(CArchive& ar)
{
	CObject::Serialize(ar);
	
	if(ar.IsStoring())
	{
		GET_APP->StopPrinting();
		GET_APP->StopScanning();
		ar << m_curr_year << m_BallotsLocked << m_signature;
		ar << m_year_FR << m_year_SO << m_year_JR << m_year_SR;
	}
	else
	{
		ar >> m_curr_year >> m_BallotsLocked >> m_signature;
		ar >> m_year_FR >> m_year_SO >> m_year_JR >> m_year_SR;
	}
	
	m_races_AL.Serialize(ar); m_ballots_AL.Serialize(ar);
	m_races_FR.Serialize(ar); m_ballots_FR.Serialize(ar);
	m_races_SO.Serialize(ar); m_ballots_SO.Serialize(ar);
	m_races_JR.Serialize(ar); m_ballots_JR.Serialize(ar);
	m_races_SR.Serialize(ar); m_ballots_SR.Serialize(ar);
	m_races_GR.Serialize(ar); m_ballots_GR.Serialize(ar);
}

BOOL CElectSoftDoc::Position()
{
	if(!PositionRaces(AL)) { return false; }
	if(!PositionRaces(FR)) { return false; }
	if(!PositionRaces(SO)) { return false; }
	if(!PositionRaces(JR)) { return false; }
	if(!PositionRaces(SR)) { return false; }
	if(!PositionRaces(GR)) { return false; }
	
	return true;
}

UINT CElectSoftDoc::GetClassYear(ClassYear year)
{
	switch(year)
	{
	case FR: return m_year_FR;
	case SO: return m_year_SO;
	case JR: return m_year_JR;
	case SR: return m_year_SR;
	default: ASSERT(false); return 0;
	}
}

void CElectSoftDoc::SetClassYear(ClassYear year, UINT val)
{
	switch(year)
	{
	case FR: m_year_FR=val; break;
	case SO: m_year_SO=val; break;
	case JR: m_year_JR=val; break;
	case SR: m_year_SR=val; break;
	}
	SetModifiedFlag();
}

CObArray* CElectSoftDoc::RaceArray(ClassYear year)
{
	switch(year)
	{
	case AL: return &m_races_AL;
	case FR: return &m_races_FR;
	case SO: return &m_races_SO;
	case JR: return &m_races_JR;
	case SR: return &m_races_SR;
	case GR: return &m_races_GR;
	default: ASSERT(false); return NULL;
	}
}

CObArray* CElectSoftDoc::BallotArray(ClassYear year)
{
	switch(year)
	{
	case AL: return &m_ballots_AL;
	case FR: return &m_ballots_FR;
	case SO: return &m_ballots_SO;
	case JR: return &m_ballots_JR;
	case SR: return &m_ballots_SR;
	case GR: return &m_ballots_GR;
	default: ASSERT(false); return NULL;
	}
}

BOOL CElectSoftDoc::PositionRaces(ClassYear year)
{
	// positions the races 
	
	UINT col, row;
	CPrintRace* pPRace;
	
	if(year==AL)
	{
		col=0; row=0; // general elections start at the begining 
	}
	else
		if(m_races_AL.GetSize())
		{		
			pPRace=(CPrintRace*)m_races_AL[m_races_AL.GetUpperBound()]; // year specific elections start at the end of the general elections 
			pPRace->GetLocation(col, row);		
			row+=pPRace->Size();
		}
		else
		{
			col=0; row=0;
		}
	
	for(int position=0; position<RaceCount(year); position++) // for each race 
		if(!PositionRace(GetRaceAt(year, position), col, row))
			return false;
	
	return true;
}

void CElectSoftDoc::UnloadStudents()
{
	for(POSITION pos=m_students.GetStartPosition(); pos;) // for each student
		delete GetNextStudentPosition(pos);
	
	m_students.RemoveAll();
}

void CElectSoftDoc::DeleteBallotArray(ClassYear year)
{
	for(int number=0; number<BallotCount(year); number++)
		delete GetBallotAt(year, number);
	
	BallotArray(year)->RemoveAll();
	BallotArray(year)->FreeExtra();
}

void CElectSoftDoc::DeleteRaceArray(ClassYear year)
{
	for(int position=0; position<RaceCount(year); position++)
		delete GetRaceAt(year, position);
	
	RaceArray(year)->RemoveAll();
	RaceArray(year)->FreeExtra();
}

int CElectSoftDoc::LoadStudents(CStdioFile* pSF, CString& Duplicate_RIN)
{
	//loads student's from a file 
	
	CString string;
	int line=0;
	
	while(pSF->ReadString(string)) //for each line in the file 
	{
		line++; Clean(string);
		if(!LoadStudent(string, Duplicate_RIN))  // if there is something wrong with the line of text
		{
			UnloadStudents(); // delete all students 
			return line;
		}
	}
	
	return 0;
}

BOOL CElectSoftDoc::OnNewDocument() 
{
	m_BallotsLocked=false; // ballots aren't locked yet 
	m_signature.Format("D%08x%08x%08x", CTime::GetCurrentTime().GetTime(), rand(), rand()); //signature used to verify Count files
	m_curr_year=CTime::GetCurrentTime().GetYear(); // the current calender year
	m_year_SR=m_curr_year+((CTime::GetCurrentTime().GetMonth()<7)?0:1); //calculate the 
	m_year_JR=m_year_SR+1; m_year_SO=m_year_SR+2; m_year_FR=m_year_SR+3;
	
	return CDocument::OnNewDocument();
}

int CElectSoftDoc::LoadRaces(CStdioFile* pSF)
{
	CString string, next_string;
	int line=0;
	
	if(RacesLoaded())
		return 0;
	
	while(pSF->ReadString(string))
	{
		line++; Clean(string);
		
		while(string.Right(1)=="\\")
			if(pSF->ReadString(next_string))
			{
				string=string.Left(string.GetLength()-1);
				line++; Clean(next_string);
				string+=next_string;
			}
		
		if(!LoadRace(string))
		{
			UnloadRaces();
			return line;
		}
	}
	
	return 0;
}

void CElectSoftDoc::Clean(CString& string)
{
	string=string.SpanExcluding("#"); 
	string.TrimLeft(); string.TrimRight();
}

BOOL CElectSoftDoc::SaveModified()
{
	if(m_pCount)
		if(!m_pCount->SaveModified())
			return false;
	
	return CDocument::SaveModified();
}

CStudent* CElectSoftDoc::GetNextStudentPosition(POSITION &pos)
{
	CString RIN;
	CStudent* pStudent;
	
	m_students.GetNextAssoc(pos, RIN, pStudent);
	return pStudent;
}

void CElectSoftDoc::ReplaceCount(CCount *pCount)
{
	if(m_pCount)
		delete m_pCount;
	
	m_pCount=pCount;
}

BOOL CElectSoftDoc::RacesLoaded()
{
	if(RaceArray(AL)->GetSize()) { return true; }
	if(RaceArray(FR)->GetSize()) { return true; }
	if(RaceArray(SO)->GetSize()) { return true; }
	if(RaceArray(JR)->GetSize()) { return true; }
	if(RaceArray(SR)->GetSize()) { return true; }
	if(RaceArray(GR)->GetSize()) { return true; }
	
	return false;
}

void CElectSoftDoc::UnloadRaces()
{
	DeleteRaceArray(AL);
	DeleteRaceArray(FR);
	DeleteRaceArray(SO);
	DeleteRaceArray(JR);
	DeleteRaceArray(SR);
	DeleteRaceArray(GR);
}

void CElectSoftDoc::AddBallot(CPrintBallot* pPBallot)
{
	BallotArray(pPBallot->GetYear())->Add(pPBallot);
	SetModifiedFlag();
}

BOOL CElectSoftDoc::LoadStudent(CString string, CString &Duplicate_RIN)
{
	//Adds one student based on 
	
	CStudent* pStudent;
	CStudent* dummy;
	BOOL eligible, valid;
	
	if(string.IsEmpty())
		return true;
	
	pStudent=new CStudent(string, eligible, valid); // create new student
	
	if(!valid) // if the line is invalid
	{
		delete pStudent;
		return false;
	}
	
	if(!eligible) // if the student is ineligable
	{
		delete pStudent;
		return true;
	}
	
	if(FindStudent(pStudent->GetRIN(), dummy)) // if there is already a student with this RIN 
	{
		Duplicate_RIN=pStudent->GetRIN();
		delete pStudent;
		return false;
	}
	
	m_students[pStudent->GetRIN()]=pStudent; // save the student in the hash
	return true;
}

BOOL CElectSoftDoc::PositionRace(CPrintRace *pPRace, UINT& col, UINT& row)
{
	//set the position of a race
	
	if(!pPRace->SetPosition(col, row)) // set the pysical position 
		return false;
	
	if((row+=pPRace->Size())<48)  // update the row and return unless there is a column over flow
		return true;
	
	if(col) // if this is the second row, there isn't enough room for this race
		return false;
	
	if(!pPRace->SetPosition(col=1, row=0)) // start at the second row 
		return false;
	
	return((row+=pPRace->Size())<48);
}

BOOL CElectSoftDoc::ReadYearCode(CString code, ClassYear& year)
{
	if(code.GetLength()!=2)
		return false;
	
	if(code=="AL") { year=AL; return true; }
	if(code=="FR") { year=FR; return true; }
	if(code=="SO") { year=SO; return true; }
	if(code=="JR") { year=JR; return true; }
	if(code=="SR") { year=SR; return true; }
	if(code=="GR") { year=GR; return true; }
	
	return false;
}

BOOL CElectSoftDoc::LoadRace(CString string)
{
	//load a print race from a file 
	
	CPrintRace* pPRace;
	BOOL valid;
	
	if(string.IsEmpty())
		return true;
	
	pPRace=new CPrintRace(string, valid);
	
	if(!valid)
	{
		delete pPRace;
		return false;
	}
	
	RaceArray(pPRace->GetYear())->Add(pPRace);
	return true;
}