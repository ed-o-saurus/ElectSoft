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
#include "ScanRace.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CScanRace::CScanRace(CPrintRace* pPRace) //ClassYear year, int position, CElectSoftDoc* pDoc)
{
	//creates a ScanRace based on a PrintRace 
	
	int cc;
	CGroup* pGroup;
	CString candidate;
	BYTE code;
	
	m_aff=pPRace->GetAff();
	m_MaxVotes=pPRace->GetMaxVotes();
	m_year=pPRace->GetYear();
	m_name=pPRace->GetName();
	pPRace->GetLocation(m_col, m_row0);
	m_row0+=pPRace->GetDescriptionLength()+3;
	m_length=pPRace->Size()-pPRace->GetDescriptionLength()-3;
	
	for(POSITION pos=pPRace->GetHeadGroupPosition(); pos;)
	{
		pGroup=pPRace->GetNextGroup(pos);
		for(cc=0; cc<pGroup->GetSize(); cc++)
		{
			pGroup->GetCandCodeAt(cc, candidate, code);
			
			if(candidate.IsEmpty())  //an empty candidate string indicates a write-in
				candidate="Write-In";
			
			m_candidates[code]=candidate;
		}
	}
}

BOOL CScanRace::IsEligible(CStudent* pStudent)
{
	// Is the student eligible to vote in this race?
	
	if(!pStudent->IsYear(m_year))  // check the year 
		return false;
	
	return((m_aff==BOTH)||(m_aff==pStudent->GetAff())); //check the affiliation
}