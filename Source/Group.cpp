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
#include "Group.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

IMPLEMENT_SERIAL(CGroup, CObject, 0)

CGroup::CGroup(CString string)
{
	//sets the candidate names 
	//fills the array with names in string seperated by pipes
	
	CString candidate;
	int pos;
	
	string+='|';
	
	do
	{
		pos=string.Find('|');
		candidate=string.Left(pos);
		string=string.Mid(pos+1);
		
		candidate.TrimLeft(); candidate.TrimRight();
		m_candidates.Add(candidate);
	}
	while(!string.IsEmpty());
	
	m_candidates.FreeExtra();
}

BOOL CGroup::SetCodes(BYTE& code)
{
	//sets the codes
	//Each non-write-in gets a unique code.
	//Each write-in is assigned a code of zero
	
	m_codes.SetSize(m_candidates.GetSize());
	
	for(int cc=0; cc<m_candidates.GetSize(); cc++)
		if((m_codes[cc]=(m_candidates[cc].GetLength())?(code++):0)==32)
			return false;  //codes may not exceed 31 
	
	return true;
}

void CGroup::Serialize(CArchive& ar)
{
	CObject::Serialize(ar);
	
	m_candidates.Serialize(ar);
	m_codes.Serialize(ar);
}