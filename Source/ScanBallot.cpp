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
#include "ScanBallot.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CScanBallot::CScanBallot(ClassYear year, int number, CCount* pCount)
{
	int position;
	
	m_year=year; m_number=number;
	m_status=OUTSTANDING;
	
	m_CodeListArray_all.SetSize(pCount->RaceCount(AL));  // fills m_CodeListArray_all with ByteLists 
	for(position=0; position<pCount->RaceCount(AL); position++)
		m_CodeListArray_all[position]=new CByteList;
	
	if(m_year==AL)
		return;
	
	m_CodeListArray_year.SetSize(pCount->RaceCount(m_year));  // fills m_CodeListArray_year with ByteLists 
	for(position=0; position<pCount->RaceCount(m_year); position++)
		m_CodeListArray_year[position]=new CByteList;
}

CScanBallot::~CScanBallot()
{
	int position;
	
	for(position=0; position<m_CodeListArray_all.GetSize(); position++)
		delete m_CodeListArray_all[position];
	
	for(position=0; position<m_CodeListArray_year.GetSize(); position++)
		delete m_CodeListArray_year[position];
	
	m_CodeListArray_all.RemoveAll();
	m_CodeListArray_year.RemoveAll();
}

BOOL CScanBallot::HasWriteIn()
{
	//if there are any codes equal to zero
	
	int position;
	
	for(position=0; position<m_CodeListArray_all.GetSize(); position++)
		if(GetCodeListAllAt(position)->Find(0))
			return true;
	
	for(position=0; position<m_CodeListArray_year.GetSize(); position++)
		if(GetCodeListYearAt(position)->Find(0))
			return true;
	
	return false;
}

BOOL CScanBallot::ReadInfo(CCount* pCount, CScannerInterface* pSI)
{
	//gets ballot info from a ScannerInterface 
	
	int position;
	
	if(!pSI->GetRIN(m_RIN)) // get the RIN 
		return false;
	
	for(position=0; position<m_CodeListArray_all.GetSize(); position++) //get results for general elections 
		pSI->FillCodeList(pCount->GetRaceAt(AL, position), GetCodeListAllAt(position));
	
	if(m_year==AL)
		return true;
	
	for(position=0; position<m_CodeListArray_year.GetSize(); position++) //get results for year specific elections 
		pSI->FillCodeList(pCount->GetRaceAt(m_year, position), GetCodeListYearAt(position));
	
	return true;
}

CString CScanBallot::WriteInfo()
{
	//generate a string to be stored in a count file
	
	CString string;
	int position;
	
	switch(m_status) //output the status (and RIN)
	{
	case OUTSTANDING:             return "BO"+SerialString()+"\n";
	case COUNTED:                 string="BC"+SerialString()+m_RIN; break;
	case VOIDED:                  return "BV"+SerialString()+"\n";
	case REPORTED_LOST_DESTROYED: return "BR"+SerialString()+"\n";
	}
	
	for(position=0; position<m_CodeListArray_all.GetSize(); position++) // add code lists to string
		string+=WriteCodeList(GetCodeListAllAt(position))+'|';
	
	if(m_year==AL)
		return string+"\n";
	
	for(position=0; position<m_CodeListArray_year.GetSize(); position++) // add code lists to string
		string+=WriteCodeList(GetCodeListYearAt(position))+'|';
	
	return string+"\n";
}

BOOL CScanBallot::ReadInfo(CString string)
{
	//read info from string
	
	int position;
	
	if(string.GetLength()<10)
		return false;
	
	switch(string[1]) //determine the status
	{
	case 'O': m_status=OUTSTANDING;             return true;
	case 'C': m_status=COUNTED;                 break;
	case 'V': m_status=VOIDED;                  return true;
	case 'R': m_status=REPORTED_LOST_DESTROYED; return true;
	default: return false;
	}
	
	if(string.GetLength()<19)
		return false;
	
	m_RIN=string.Mid(10, 9); // get the RIN
	
	for(int i=0; i<9; i++) // verify that the RIN is valid 
		if(!isdigit(m_RIN[i]))
			return false;	
	
	if(string.Right(1)!="|") // verify format 
		return false;
	
	string=string.Mid(19); // drop the first 19 characters (we no longer need them)
		
	for(position=0; position<m_CodeListArray_all.GetSize(); position++) // for each general race 
	{
		if(string.IsEmpty()) // make sure there is still data 
			return false;
		
		FillCodeList(StripCodes(string), GetCodeListAllAt(position)); // read the data 
	}
	
	if(m_year==AL)
		return string.IsEmpty(); // we should be done 
	
	for(position=0; position<m_CodeListArray_year.GetSize(); position++)
	{
		if(string.IsEmpty())
			return false;
		
		FillCodeList(StripCodes(string), GetCodeListYearAt(position));
	}
	
	return string.IsEmpty();  // we should be done 
}

CString CScanBallot::SerialString()
{
	CString SS;
	
	switch(m_year)
	{
	case AL: SS.Format("AL.%05d", m_number+1); break;
	case FR: SS.Format("FR.%05d", m_number+1); break;
	case SO: SS.Format("SO.%05d", m_number+1); break;
	case JR: SS.Format("JR.%05d", m_number+1); break;
	case SR: SS.Format("SR.%05d", m_number+1); break;
	case GR: SS.Format("GR.%05d", m_number+1); break;
	}
	
	return SS;
}

void CScanBallot::FillCodeList(CString codes, CByteList* pCodeList)
{
	//fill a code list from a string
	
	pCodeList->RemoveAll();
	for(int i=0; i<codes.GetLength(); i++)
		pCodeList->AddTail(codes[i]&0x1f);
}

CString CScanBallot::WriteCodeList(CByteList* pCodeList)
{
	// format a CodeList into string form
	
	CString string;
	
	for(POSITION pos=pCodeList->GetHeadPosition(); pos;)
		string+=(char)(pCodeList->GetNext(pos)|0x40);
	
	return string;
}

CString CScanBallot::StripCodes(CString &string)
{
	// pop a code list from string 
	
	CString rv=string.SpanExcluding("|"); 
	string=string.Mid(rv.GetLength()+1);
	return rv;
}