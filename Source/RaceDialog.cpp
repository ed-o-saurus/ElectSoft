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
#include "RaceDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CRaceDialog::CRaceDialog(CWnd* pParent) : CDialog(CRaceDialog::IDD, pParent) {}

void CRaceDialog::DoDataExchange(CDataExchange* pDX)
{
	//displays info about a PrintRace
	
	int cc;
	CGroup* pGroup;
	HTREEITEM hGroup;
	CString candidate;
	BYTE code;
	CString description;
	POSITION pos;
	
	SetWindowText("Race : "+m_pPRace->GetName());
	
	for(pos=m_pPRace->DescriptionStartPosition(); pos;)  //add the description 
		description+=m_pPRace->GetNextDecsriptionLine(pos)+"\r\n";
	
	description.TrimRight("\r\n");
	
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_DESCRIPTION, description);
	DDX_Control(pDX, IDC_DATA, m_data);
	
	for(pos=m_pPRace->GetHeadGroupPosition(); pos;)  //for each group
	{
		pGroup=m_pPRace->GetNextGroup(pos);
		hGroup=m_data.InsertItem("Group"); // add a node to the tree
		
		for(cc=0; cc<pGroup->GetSize(); cc++) // for each candidate
		{
			pGroup->GetCandCodeAt(cc, candidate, code);	
			m_data.InsertItem(candidate.IsEmpty()?"Write-In":candidate, hGroup);
		}
		
		m_data.Expand(hGroup, TVE_EXPAND);
	}
	
	((CEdit*)GetDlgItem(IDC_DESCRIPTION))->SetReadOnly();
}