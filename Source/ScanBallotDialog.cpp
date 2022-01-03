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
#include "ScanBallotDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CScanBallotDialog::CScanBallotDialog(CWnd* pParent) : CDialog(CScanBallotDialog::IDD, pParent) {}

void CScanBallotDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	
	SetWindowText(m_pSBallot->SerialString()+" : Counted"); // This dialog box will only come up on counted ballots
	FillText();
	m_votes.TrimRight("\r\n"); // get rid of unneeded cartrige returns and new line characters
	DDX_Text(pDX, IDC_VOTES, m_votes);
}

void CScanBallotDialog::FillText()
{
	int position;
	ClassYear year=m_pSBallot->GetYear();
	
	AddLine("RIN : "+m_pSBallot->GetRIN()); AddLine();
	
	for(position=0; position<m_pCount->RaceCount(AL); position++)
		AddRace(m_pCount->GetRaceAt(AL, position), m_pSBallot->GetCodeListAllAt(position));
	
	if(year==AL)
		return;
	
	for(position=0; position<m_pCount->RaceCount(year); position++)
		AddRace(m_pCount->GetRaceAt(year, position), m_pSBallot->GetCodeListYearAt(position));
}

void CScanBallotDialog::AddRace(CScanRace* pSRace, CByteList* pCodeList)
{
	CString candidate;
	AddLine(pSRace->GetName());
	
	for(POSITION pos=pCodeList->GetHeadPosition(); pos;)  // for each code in the race 
		if(pSRace->GetCand(pCodeList->GetNext(pos), candidate)) //get the candidate name 
			AddLine("\t"+candidate);
	
	AddLine();
}