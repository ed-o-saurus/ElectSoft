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
#include "CountReport.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

void CCountReport::WriteReport(CElectSoftDoc* pDoc, CStdioFile* pSF)
{
	m_pSF=pSF;
	if((m_pCount=pDoc->GetCount())==NULL)
		return;
	
	SetUpRaces(AL); SetUpRaces(FR); SetUpRaces(SO);  //create CUIntArrays that correspond to Races
	SetUpRaces(JR); SetUpRaces(SR); SetUpRaces(GR);
	
	m_voters.RemoveAll();
	AddUpVoters();     // determines how many times everyone voted 
	AddBallots(pDoc);  // add up votes 
	
	AddLine(m_pCount->GetTitle()); AddLine(); // Add the title to the report 
	AddStatusCounts();  // how many ballots are there in each year and status 
	PrintRaces(); // output the results of the voting 
	AddOutstandingBallotsToReport(); // ballots that are unaccounted for
	AddRepeatVotersToReport();  // the bastands who voted more than once (God I hate them)
	
	DeleteRaces(AL); DeleteRaces(FR); DeleteRaces(SO);
	DeleteRaces(JR); DeleteRaces(SR); DeleteRaces(GR);
}

void CCountReport::AddUpVoters()
{
	int number;
	
	for(number=0; number<m_pCount->BallotCount(AL); number++) { AddVoter(m_pCount->GetBallotAt(AL, number)); }
	for(number=0; number<m_pCount->BallotCount(FR); number++) { AddVoter(m_pCount->GetBallotAt(FR, number)); }
	for(number=0; number<m_pCount->BallotCount(SO); number++) { AddVoter(m_pCount->GetBallotAt(SO, number)); }
	for(number=0; number<m_pCount->BallotCount(JR); number++) { AddVoter(m_pCount->GetBallotAt(JR, number)); }
	for(number=0; number<m_pCount->BallotCount(SR); number++) { AddVoter(m_pCount->GetBallotAt(SR, number)); }
	for(number=0; number<m_pCount->BallotCount(GR); number++) { AddVoter(m_pCount->GetBallotAt(GR, number)); }
}

void CCountReport::AddVoter(CScanBallot* pSBallot)
{
	if(pSBallot->GetStatus()==COUNTED)  // only counted ballots have voters 
		m_voters[pSBallot->GetRIN()]++; // increment the hash
}

void CCountReport::AddBallots(CElectSoftDoc* pDoc)
{
	int number;
	
	for(number=0; number<m_pCount->BallotCount(AL); number++) { AddBallot(AL, number, pDoc); }
	for(number=0; number<m_pCount->BallotCount(FR); number++) { AddBallot(FR, number, pDoc); }
	for(number=0; number<m_pCount->BallotCount(SO); number++) { AddBallot(SO, number, pDoc); }
	for(number=0; number<m_pCount->BallotCount(JR); number++) { AddBallot(JR, number, pDoc); }
	for(number=0; number<m_pCount->BallotCount(SR); number++) { AddBallot(SR, number, pDoc); }
	for(number=0; number<m_pCount->BallotCount(GR); number++) { AddBallot(GR, number, pDoc); }
}

void CCountReport::AddStatusCounts()
{
	AddLine("   |   Outstanding    |      Counted     |  Lost/Destroyed  |      Voided      |");
	AddSeperator();
	
	AddLine("AL"+GetBallotTypes(AL)->StatusCount()); AddSeperator();
	AddLine("FR"+GetBallotTypes(FR)->StatusCount()); AddSeperator();
	AddLine("SO"+GetBallotTypes(SO)->StatusCount()); AddSeperator();
	AddLine("JR"+GetBallotTypes(JR)->StatusCount()); AddSeperator();
	AddLine("SR"+GetBallotTypes(SR)->StatusCount()); AddSeperator();
	AddLine("GR"+GetBallotTypes(GR)->StatusCount()); AddSeperator();
	
	AddLine();
}

void CCountReport::PrintRaces()
{
	int position;
	
	for(position=0; position<m_pCount->RaceCount(AL); position++) { PrintRace(AL, position); }
	for(position=0; position<m_pCount->RaceCount(FR); position++) { PrintRace(FR, position); }
	for(position=0; position<m_pCount->RaceCount(SO); position++) { PrintRace(SO, position); }
	for(position=0; position<m_pCount->RaceCount(JR); position++) { PrintRace(JR, position); }
	for(position=0; position<m_pCount->RaceCount(SR); position++) { PrintRace(SR, position); }
	for(position=0; position<m_pCount->RaceCount(GR); position++) { PrintRace(GR, position); }
	
	AddLine();
}

void CCountReport::AddOutstandingBallotsToReport()
{
	AddOutstandingBallotToReport(AL);
	AddOutstandingBallotToReport(FR);
	AddOutstandingBallotToReport(SO);
	AddOutstandingBallotToReport(JR);
	AddOutstandingBallotToReport(SR);
	AddOutstandingBallotToReport(GR);
	
	AddLine();
}

void CCountReport::AddRepeatVotersToReport()
{
	CString RIN;
	UINT votes;
	CStringList RINlist;
	
	for(POSITION pos=m_voters.GetStartPosition(); pos;)  // for each entry in m_voters 
	{
		m_voters.GetNextAssoc(pos, RIN, votes);
		if(votes>1) // if the student voted more than once 
			RINlist.AddTail(RIN);
	}
	
	if(RINlist.IsEmpty())
		return;
	
	SortList(&RINlist);  // puts the list in order 
	
	AddLine("The following voted more than once:");
	while(!RINlist.IsEmpty()) // add the voters to the report 
		AddLine(RINlist.RemoveHead());
}

void CCountReport::SetUpRaces(ClassYear year)
{
	CUIntArray* pTRace;
	RaceArray(year)->SetSize(m_pCount->RaceCount(year));  // We need the same number of totals races as ScanRaces
	for(int position=0; position<m_pCount->RaceCount(year); position++)
	{
		RaceArray(year)->SetAt(position, pTRace=new CUIntArray);  // fill RaceArray(year) with CUIntArrays 
		pTRace->SetSize(32); // 32 slots for 32 codes 
	}
}

void CCountReport::AddBallot(ClassYear year, int number, CElectSoftDoc* pDoc)
{
	UINT votes;
	CScanBallot* pSBallot=m_pCount->GetBallotAt(year, number);
	BallotStatus status=pSBallot->GetStatus();
	int position;
	CStudent* pStudent;
	
	GetBallotTypes(year)->IncrementCount(status);
	
	if(status!=COUNTED) // Ballots that aren't coutned don't affect the outcome
		return;
	
	if(!m_voters.Lookup(pSBallot->GetRIN(), votes))
		return;  // This should never be called (in theory) 
	
	if(votes>1)  // If the student voted more than once 
		return;
	
	if(!pDoc->FindStudent(pSBallot->GetRIN(), pStudent)) // Non-existant students don't count
		return;
	
	for(position=0; position<m_pCount->RaceCount(AL); position++)
		AddRace(year, position, pSBallot->GetCodeListAllAt(position), pStudent); //Add the individual race
	
	if(year==AL)
		return;
	
	for(position=0; position<m_pCount->RaceCount(year); position++)
		AddRace(year, position, pSBallot->GetCodeListYearAt(position), pStudent); //Add the individual race
}

void CCountReport::AddRace(ClassYear year, int position, CByteList* pCodeList, CStudent* pStudent)
{
	CScanRace* pSRace=m_pCount->GetRaceAt(year, position);
	
	if(!pSRace->IsEligible(pStudent))  // if the student is ineligible
		return;
	
	if(pCodeList->GetCount()>pSRace->GetMaxVotes()) //if the student voted for more candidates than allowed
		return;
	
	CUIntArray* pTRace=RaceArray(year)->GetAt(position);
	for(POSITION pos=pCodeList->GetHeadPosition(); pos;)
		(*pTRace)[pCodeList->GetNext(pos)]++; //increment the totals 
}

void CCountReport::PrintRace(ClassYear year, int position)
{
	CString string, candidate;
	CScanRace* pSRace=m_pCount->GetRaceAt(year, position);
	CUIntArray* pTRace=RaceArray(year)->GetAt(position);
	
	AddLine(pSRace->GetName());
	
	for(BYTE code=0; code<32; code++)  // for each possible code 
		if(pSRace->GetCand(code, candidate)) // if there is a corrisponding candidate for the code 
		{
			string.Format("%25s : %5d", candidate, pTRace->GetAt(code)); // output the candidate name and the number of votes 
			AddLine(string);
		}
	
	AddLine();
}

void CCountReport::AddOutstandingBallotToReport(ClassYear year)
{
	CScanBallot* pSBallot;
	
	for(int number=0; number<m_pCount->BallotCount(year); number++) // for each ballot in the year
		if((pSBallot=m_pCount->GetBallotAt(year, number))->GetStatus()==OUTSTANDING) // if the ballot is outstanding
			AddLine("OUTSTANDING : "+pSBallot->SerialString()); //output the info 
}

void CCountReport::DeleteRaces(ClassYear year)
{
	for(int position=0; position<m_pCount->RaceCount(year); position++)
		delete RaceArray(year)->GetAt(position);
	
	RaceArray(year)->RemoveAll();
}

CArray<CUIntArray*, CUIntArray*>* CCountReport::RaceArray(ClassYear year)
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

void CCountReport::SortList(CStringList *pList)
{
	// This is a classic QuickSort
	
	CString pivot;
	CStringList L, R;
	
	if(pList->GetCount()<=1)
		return;
	
	pivot=pList->RemoveHead();  // There is no order to the list, so we can choose the first element as the pivot 
	while(!pList->IsEmpty()) // partition the list 
		if(pList->GetHead()<pivot)
			L.AddTail(pList->RemoveHead());
		else
			R.AddTail(pList->RemoveHead());
	
	SortList(&L); SortList(&R); // sort the left and right lists 
	
	pList->AddTail(&L); pList->AddTail(pivot); pList->AddTail(&R);  // recombine them 
}

CCountReport::ballot_types* CCountReport::GetBallotTypes(ClassYear year)
{
	switch(year)
	{
	case AL: return &m_types_AL;
	case FR: return &m_types_FR;
	case SO: return &m_types_SO;
	case JR: return &m_types_JR;
	case SR: return &m_types_SR;
	case GR: return &m_types_GR;
	default: ASSERT(false); return NULL;
	}
}

void CCountReport::ballot_types::IncrementCount(BallotStatus status)
{
	switch(status)
	{
	case OUTSTANDING:             m_Outstanding++;    return;
	case COUNTED:                 m_Counted++;        return;
	case REPORTED_LOST_DESTROYED: m_Lost_Destroyed++; return;
	case VOIDED:                  m_Voided++;         return;
	}
}

CString CCountReport::ballot_types::StatusCount()
{
	CString string;
	string.Format(" |       %5d      |       %5d      |       %5d      |       %5d      |", 
		m_Outstanding, m_Counted, m_Lost_Destroyed, m_Voided);
	
	return string;
}