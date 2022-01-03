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
#include "PrintRace.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

IMPLEMENT_SERIAL(CPrintRace, CObject, 0)

CPrintRace::~CPrintRace()
{
	while(!m_groups.IsEmpty())
		delete (CGroup*)m_groups.RemoveHead();
}

BOOL CPrintRace::SetPosition(UINT col, UINT row)
{
	// sets the physical position of the race and assigns codes to the candidates 
	
	BYTE code=1; // codes start at 1
	
	for(POSITION pos=m_groups.GetHeadPosition(); pos;)  // for each group 
		if(!GetNextGroup(pos)->SetCodes(code)) // set codes for the group 
			return false;
	
	m_col=col; m_row=row;
	return true;
}

UINT CPrintRace::Size()
{
	UINT size=m_description.GetCount()+3; // descritption length and 3 lines of header 
	
	for(POSITION pos=m_groups.GetHeadPosition(); pos;) // for each group 
		size+=GetNextGroup(pos)->GetSize();
	
	return size;
}

CPrintRace::CPrintRace(CString string, BOOL& valid)
{
	// loads the race from a file 
	
	CStringList fields;
	CString NameCaption;
	CString description;
	int pos;
	
	valid=false;
	
	if(string.GetLength()<5)
		return;
	
	if(!ReadYearCode(string.Left(2), m_year))  // get the year 
		return;
	
	switch(string[2])  // get the affiliation 
	{
	case 'G': m_aff=GREEK;       break;
	case 'I': m_aff=INDEPENDENT; break;
	case 'B': m_aff=BOTH;        break;
	default: return;
	}
	
	if(!isdigit(string[3]))
		return;
	
	if(!isdigit(string[4]))
		return;
	
	m_MaxVotes=atoi(string.Mid(3, 2)); // get MaxVotes 
	if(!m_MaxVotes) // MaxVotes must not be zero 
		return;
	
	if(string.Right(1)!="^")  // formating thing 
		return;
	
	SplitString(string.Mid(5, string.GetLength()-6), fields, '^');  // bread the remaining part of the line into fields delimited by '^'
	if(fields.GetCount()<2) // two fields are requiered 
		return;
	
	valid=true;
	
	NameCaption=fields.RemoveHead(); pos=NameCaption.Find('|');  // the first field is Name|Caption 
	m_name=NameCaption.Left(pos); m_caption=NameCaption.Mid(pos+1);
	
	description=fields.RemoveHead(); // second field is the description 
	if(!description.IsEmpty())
		SplitString(description, m_description, '|');
	
	while(!fields.IsEmpty()) // read each group  
		m_groups.AddTail(new CGroup(fields.RemoveHead()));
}

void CPrintRace::Serialize(CArchive &ar)
{
	CObject::Serialize(ar);
	
	if(ar.IsStoring())
	{
		ar << m_col << m_row << m_year << m_aff;
		ar << m_name << m_caption << m_MaxVotes;
	}
	else
	{
		ar >> m_col >> m_row >> m_year >> m_aff;
		ar >> m_name >> m_caption >> m_MaxVotes;
	}
	
	m_description.Serialize(ar);
	m_groups.Serialize(ar);
}

BOOL CPrintRace::ReadYearCode(CString code, ClassYear &year)
{
	// determines the ClassYear represneted by code 
	
	if(code=="AL") { year=AL; return true; }
	if(code=="FR") { year=FR; return true; }
	if(code=="SO") { year=SO; return true; }
	if(code=="JR") { year=JR; return true; }
	if(code=="SR") { year=SR; return true; }
	if(code=="GR") { year=GR; return true; }
	
	return false;
}

void CPrintRace::SplitString(CString string, CStringList &list, char sp)
{
	// Divides string into sub-strings delimited by sp
	
	int pos;
	
	if((pos=string.Find(sp))==(-1))
	{
		list.AddTail(string);
		return;
	}
	
	list.AddTail(string.Left(pos));
	SplitString(string.Mid(pos+1), list, sp);
}