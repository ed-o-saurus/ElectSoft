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
#include "Scanning.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

UINT CScanning::MainRoutine(LPVOID pParam)
{
	GET_APP->m_ScanInfo.bRunning=true;	
	ScanStack();
	GET_APP->m_ScanInfo.bRunning=false;
	return 0;
}

void CScanning::ScanStack()
{
	CScannerInterface SI;
	CMap<CString, CString, UINT, UINT> Voters;
	CElectSoftView* pView=GET_APP->m_ScanInfo.pView;
	
	if(!SI.OpenComm())  // open the port 
	{
		pView->MessageBox("Comm port not opened", NULL, MB_ICONERROR);
		return;
	}
	
	if(!SI.CheckHopper())  // check the hopper status 
	{
		pView->MessageBox("Unable to communicate with scanner", NULL, MB_ICONERROR);
		SI.CloseComm();
		return;
	}
	
	while(!(SI.HopperEmpty()||GET_APP->m_ScanInfo.bKill)) // while there are ballots to scan and the thread isn't killed by the user 
		ScanBallot(&SI, GET_APP->m_ScanInfo.voiding);
	
	if(!SI.CloseComm()) // close the port 
		pView->MessageBox("Unable to close comm port", NULL, MB_ICONERROR);
}

void CScanning::ScanBallot(CScannerInterface* pSI, BOOL voiding)
{
	int number;
	ClassYear year;
	CElectSoftView* pView=GET_APP->m_ScanInfo.pView;
	CElectSoftDoc* pDoc=pView->GetDocument();
	CCount* pCount=pDoc->GetCount();
	
	if(!GetBallotInfo(pSI, year, number))  // get the serial number 
		return;
	
	CScanBallot* pSBallot=pCount->GetBallotAt(year, number);
	CPrintBallot* pPBallot=pDoc->GetBallotAt(year, number);
	
	if(!StatusCleared(pSBallot->GetStatus()))  // make sure the ballot should be counted 
		return;	
	
	ProcessBallot(pSI, voiding, pPBallot, pSBallot); // get the info 
	pCount->SetModifiedFlag(); // there is something to save in the count 
	
	while(GET_APP->m_ScanInfo.pSBallot)  // while there is a ballot that needs to be displayed 
		Sleep(10);
	
	GET_APP->m_ScanInfo.pSBallot=pSBallot; // post the ballot to be displayed 
	PostMessage(pView->m_hWnd, WM_COMMAND, MAKEWPARAM(ID_UPDATESCANBALLOT, 0), 0);  // inform the main thread that there is a ballot to be displayed 
}

BOOL CScanning::StatusCleared(BallotStatus status)
{
	CElectSoftView* pView=GET_APP->m_ScanInfo.pView;
	
	switch(status)  // the ballot's status 
	{
	case OUTSTANDING: return true;
	case COUNTED:
		return(pView->MessageBox("This ballot has been counted.\nDo you want it to be reentered?", NULL, MB_ICONWARNING|MB_YESNO)==IDYES);
	case VOIDED:
		return(pView->MessageBox("This ballot has been voided.\nDo you want it to be reentered?", NULL, MB_ICONWARNING|MB_YESNO)==IDYES);
	case REPORTED_LOST_DESTROYED:
		return(pView->MessageBox("This ballot has been repoted lost or destroyed.\nDo you want it to be reentered?", NULL, MB_ICONWARNING|MB_YESNO)==IDYES);
	default:
		ASSERT(false); return false;
	}
}

void CScanning::CheckStudent(CScanBallot* pSBallot, CCount* pCount)
{
	CString RIN=pSBallot->GetRIN();
	ClassYear ballot_year=pSBallot->GetYear();
	CStudent* pStudent;
	CElectSoftView* pView=GET_APP->m_ScanInfo.pView;
	
	if(!pView->GetDocument()->FindStudent(RIN, pStudent))  // is there is no such student 
	{
		pView->MessageBox("RIN not found", NULL, MB_ICONERROR);
		return;
	}
	
	if(pStudent->IsYear(ballot_year))  // if the student is the correct year 
		return;
	
	switch(ballot_year)
	{
	case FR: pView->MessageBox("Student is not a freshmen.",  NULL, MB_ICONERROR); break;
	case SO: pView->MessageBox("Student is not a sophomore.", NULL, MB_ICONERROR); break;
	case JR: pView->MessageBox("Student is not a junior.",    NULL, MB_ICONERROR); break;
	case SR: pView->MessageBox("Student is not a senior.",    NULL, MB_ICONERROR); break;
	case GR: pView->MessageBox("Student is not a graduate.",  NULL, MB_ICONERROR); break;
	}
}

BOOL CScanning::GetBallotInfo(CScannerInterface* pSI, ClassYear& year, int& number)
{
	CElectSoftView* pView=GET_APP->m_ScanInfo.pView;
	
	if(!pSI->ScanBallot())  // scan the ballot 
	{
		pView->MessageBox("Cannot Scan Ballot", NULL, MB_ICONERROR);
		return false;
	}
	
	if(!pSI->GetSerial(year, number))  // get the serial number 
	{
		pView->MessageBox("Cannot Read Serial Number", NULL, MB_ICONERROR);
		return false;
	}
	
	if(pView->GetDocument()->GetCount()->BallotCount(year)<=number)  // verify that the serial number is valid 
	{
		pView->MessageBox("Invalid Serial Number", NULL, MB_ICONERROR);
		return false;
	}
	
	return true;
}

void CScanning::ProcessBallot(CScannerInterface* pSI, BOOL voiding, CPrintBallot* pPBallot, CScanBallot* pSBallot)
{
	CElectSoftView* pView=GET_APP->m_ScanInfo.pView;
	CElectSoftDoc* pDoc=pView->GetDocument();
	CCount* pCount=pDoc->GetCount();
	
	if(voiding) // if ballots are being voided 
	{
		pSBallot->SetStatus(VOIDED);
		pPBallot->AddEvent(VOIDED, pDoc);
		return;
	}
	
	if(!pSBallot->ReadInfo(pCount, pSI)) // if we can't read info 
	{
		pView->MessageBox("Unable to read RIN\nVoiding ballot", NULL, MB_ICONERROR);
		pSBallot->SetStatus(VOIDED);
		pPBallot->AddEvent(VOIDED, pDoc);
		return;
	}
	
	CheckStudent(pSBallot, pCount);
	pSBallot->SetStatus(COUNTED);
	pPBallot->AddEvent(COUNTED, pDoc);
	
	if(pSBallot->HasWriteIn())  // if there are write-ins 
		pView->MessageBox("Ballot has write-in(s)", NULL, MB_ICONINFORMATION);
}