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
#include "Count.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CCount::CCount(CElectSoftDoc* pDoc)
{
	m_title=pDoc->GetTitle()+"_Count";
	m_signature=pDoc->GetSignature(); ///used to verify that loaded count files go with a particular Document
	
	AttachRaceArray(pDoc, AL); //create ScanRaces based on PrintRaces 
	AttachRaceArray(pDoc, FR);
	AttachRaceArray(pDoc, SO);
	AttachRaceArray(pDoc, JR);
	AttachRaceArray(pDoc, SR);
	AttachRaceArray(pDoc, GR);
	
	AttachBallotArray(pDoc, AL); //create ScanBallots based on PrintBallots 
	AttachBallotArray(pDoc, FR);
	AttachBallotArray(pDoc, SO);
	AttachBallotArray(pDoc, JR);
	AttachBallotArray(pDoc, SR);
	AttachBallotArray(pDoc, GR);
	
	m_bModified=true; // It hasn't been saved, now than has it?
}

CCount::~CCount()
{
	DeleteBallotArray(AL); DeleteRaceArray(AL);
	DeleteBallotArray(FR); DeleteRaceArray(FR);
	DeleteBallotArray(SO); DeleteRaceArray(SO);
	DeleteBallotArray(JR); DeleteRaceArray(JR);
	DeleteBallotArray(SR); DeleteRaceArray(SR);
	DeleteBallotArray(GR); DeleteRaceArray(GR);
}

CScanBallotArray* CCount::BallotArray(ClassYear year)
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

CScanRaceArray* CCount::RaceArray(ClassYear year)
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

void CCount::DeleteBallotArray(ClassYear year)
{
	for(int number=0; number<BallotCount(year); number++)
		delete GetBallotAt(year, number);
	
	BallotArray(year)->RemoveAll();
}

void CCount::DeleteRaceArray(ClassYear year)
{
	for(int position=0; position<RaceCount(year); position++)
		delete GetRaceAt(year, position);
	
	RaceArray(year)->RemoveAll();
}

void CCount::AttachRaceArray(CElectSoftDoc* pDoc, ClassYear year)
{
	//create ScanRaces that correspond to PrintRaces 
	
	RaceArray(year)->SetSize(pDoc->RaceCount(year));
	for(int position=0; position<pDoc->RaceCount(year); position++)
		RaceArray(year)->SetAt(position, new CScanRace(pDoc->GetRaceAt(year, position)));
}

void CCount::AttachBallotArray(CElectSoftDoc* pDoc, ClassYear year)
{
	//create ScanBallots that correspond to PrintBallots 
	
	BallotArray(year)->SetSize(pDoc->BallotCount(year));
	for(int number=0; number<pDoc->BallotCount(year); number++)
		BallotArray(year)->SetAt(number, new CScanBallot(year, number, this));
}

void CCount::Save(BOOL AskForPath)
{
	CString string, RIN;
	int number;
	
	if(AskForPath||m_pathname.IsEmpty())  // if we are explicitly asked to get a new path, or don't know it
	{	
		CFileDialog FD(false, "cou", m_title, OFN_HIDEREADONLY, 
			"Count Files (*.cou)|*.cou|All Files (*.*)|*.*||", NULL);
		
		if(FD.DoModal()!=IDOK)
			return;
		
		m_title=FD.GetFileTitle();
		m_pathname=FD.GetPathName();
	}
	
	CStdioFile SF(m_pathname, CFile::modeWrite|CFile::modeCreate|CFile::typeText);
	
	// Add all the info to the file 
	
	SF.WriteString("********************************************\n");
	SF.WriteString("**  THIS FILE IS GENERATED AUTOMATICALLY  **\n");
	SF.WriteString("**         DO NOT ALTER THIS FILE         **\n");
	SF.WriteString("********************************************\n");
	
	SF.WriteString(m_signature+'\n');
	
	for(number=0; number<BallotCount(AL); number++) { SF.WriteString(GetBallotAt(AL, number)->WriteInfo()); }
	for(number=0; number<BallotCount(FR); number++) { SF.WriteString(GetBallotAt(FR, number)->WriteInfo()); }
	for(number=0; number<BallotCount(SO); number++) { SF.WriteString(GetBallotAt(SO, number)->WriteInfo()); }
	for(number=0; number<BallotCount(JR); number++) { SF.WriteString(GetBallotAt(JR, number)->WriteInfo()); }
	for(number=0; number<BallotCount(SR); number++) { SF.WriteString(GetBallotAt(SR, number)->WriteInfo()); }
	for(number=0; number<BallotCount(GR); number++) { SF.WriteString(GetBallotAt(GR, number)->WriteInfo()); }
	
	SF.Close();
	m_bModified=false;
}

BOOL CCount::Open(CStdioFile* pSF)
{
	CString string;
	
	m_title=pSF->GetFileTitle();  // Data set by to dialog box in the calling function 
	m_pathname=pSF->GetFilePath();
	
	while(pSF->ReadString(string))   //Keep processing lines of text 
		if(!ProcessFileLine(string))
			return false;
	
	m_bModified=false;  //nothing modified yet 
	return true;
}

BOOL CCount::ProcessFileLine(CString string)
{
	ClassYear year;
	int number;
	
	string.TrimRight("\r\n");  //clean the line 
	if(string.IsEmpty())
		return true;
	
	switch(string[0])  // the type of the line is determined by the first character 
	{
	case '*': return true;  //comment 
	case 'D': return(m_signature==string);  //does this file get with the current document? 
	case 'B':  // a ballot
		if(string.GetLength()<10) //read the serial number 
			return false;
		
		if(!ReadYearCode(string.Mid(2, 2), year))
			return false;
		
		if(string[4]!='.')
			return false;
		
		number=atoi(string.Mid(5, 5))-1;
		if(number==(-1))
			return false;
		
		if(BallotCount(year)<=number) // I this an invalid serial number ?
			return false;
		
		return GetBallotAt(year, number)->ReadInfo(string); //load the data into the ballot 
		
	default:  return false;  //nothing else is allowed 
	}
}

BOOL CCount::SaveModified()
{
	if(!m_bModified)  // if there isn't anything new to save 
		return true;
	
	CString name=(m_pathname.IsEmpty())?m_title:m_pathname;  //determine the name 
	
	CString prompt;
	AfxFormatString1(prompt, AFX_IDP_ASK_TO_SAVE, name);
	switch(AfxMessageBox(prompt, MB_YESNOCANCEL, AFX_IDP_ASK_TO_SAVE)) // ask to user if he want's to save
	{
	case IDYES: Save(false); return true;
	case IDNO: return true;
	case IDCANCEL: return false;
	default: ASSERT(false); return true;
	}
}

BOOL CCount::ReadYearCode(CString code, ClassYear& year)
{
	//determines the year that code represents 
	
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