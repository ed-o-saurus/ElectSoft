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
#include "PrintBallotDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CPrintBallotDialog::CPrintBallotDialog(CWnd* pParent):CDialog(CPrintBallotDialog::IDD, pParent){}

void CPrintBallotDialog::DoDataExchange(CDataExchange* pDX)
{
	//displays the data associated with a PrintBallot 
	
	CPrintBallot::CEvent event;
	CTime time;
	BallotStatus status;
	int nItem;
	
	SetWindowText("Print Ballot : "+m_pPBallot->SerialString());
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EVENTS, m_events);
	if(pDX->m_bSaveAndValidate)
		return;
	
	m_events.InsertColumn(0, "Event", LVCFMT_LEFT, 125);
	m_events.InsertColumn(1, "Time", LVCFMT_LEFT, 103);
	
	for(POSITION pos=m_pPBallot->GetHeadEventPosition(); pos;)  //for each event 
	{
		// add the nature and time of the event to the list
		
		event=m_pPBallot->GetNextEvent(pos);
		event.GetTimeType(time, status);
		
		switch(status) 
		{
		case PRINTED:                 nItem=m_events.InsertItem(0, "Printed");                break;
		case COUNTED:                 nItem=m_events.InsertItem(0, "Counted");                break;
		case VOIDED:                  nItem=m_events.InsertItem(0, "Voided");                 break;
		case REPORTED_LOST_DESTROYED: nItem=m_events.InsertItem(0, "Reported Lost/Destroyed"); break;
		}
		
		m_events.SetItemText(nItem, 1, time.Format("%c"));
		m_events.SetItemData(nItem, (DWORD)time.GetTime());
	}
	
	m_events.SortItems(EventListCompareFunc, 0);
}