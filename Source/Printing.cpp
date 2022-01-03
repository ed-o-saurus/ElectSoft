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
#include "Printing.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#define PRINT_PAUSE 500

UINT CPrinting::MainRoutine(LPVOID pParam)
{
	GET_APP->m_PrintInfo.bRunning=true;   //indicate that the tread is running
	PrintStack();
	GET_APP->m_PrintInfo.bRunning=false;  //indicate that the tread isn't running
	return 0;
}

void CPrinting::PrintStack()
{
	BOOL AutoReg=true;      //Automatic print queue regulation is on by default 
	UINT AlignmentCountdown=0;  //The first this to do is align the printer 
	int size=GET_APP->m_PrintInfo.size; //The number of ballots to print 
	CElectSoftView* pView=GET_APP->m_PrintInfo.pView;
	
	if(!CPrinterInterface::CheckPrinterConfig())   //If the printer doesn't print 8 1/2 by 11 inch sheets
	{
		pView->MessageBox("Incorrect Printer Configuration", NULL, MB_ICONERROR);
		return;
	}
	
	while(size&&(!GET_APP->m_PrintInfo.bKill))  //While there are ballots to print and the tread hasn't been terminated externally
		Step(AutoReg, AlignmentCountdown, size);
}

void CPrinting::PrintBallot(int &size, UINT &AlignmentCountdown)
{
	ClassYear year=GET_APP->m_PrintInfo.year;  //The ballot's year 
	CElectSoftView* pView=GET_APP->m_PrintInfo.pView;
	CElectSoftDoc* pDoc=pView->GetDocument();
	CPrintBallot* pPBallot;
	CPrinterInterface PI;
	
	if(!PI.Print(year, pDoc))  //Try to print the ballot 
	{
		Sleep(PRINT_PAUSE);  //If it fails sleep and try again 
		return;
	}
	
	pPBallot=new CPrintBallot(year, pDoc);  //New print ballot to add to the document 
	pPBallot->AddEvent(PRINTED, pDoc);  //The ballot has been printed 
	pDoc->AddBallot(pPBallot);  //Add the ballot to the document 
	size--; AlignmentCountdown--;  //One down 
	
	while(GET_APP->m_PrintInfo.pPBallot) //While there is a ballot waitting to be added to the GUI 
		Sleep(10);
	
	GET_APP->m_PrintInfo.pPBallot=pPBallot;  //Post the ballot to be added to the GUI 
	PostMessage(pView->m_hWnd, WM_COMMAND, MAKEWPARAM(ID_INSERTPRINTBALLOT, 0), 0);
}

#ifdef _SIM_BALLOT

void CPrinting::AlignPrinter(UINT &AlignmentCountdown)
{ AlignmentCountdown=GET_APP->m_PrintInfo.AlignmentRate; }  //reset the alignment countdown

#else

void CPrinting::AlignPrinter(UINT &AlignmentCountdown)
{
	CPrinterInterface PI;
	BOOL changed=true;
	
	while(changed)  //While the user has changed the alignment dialog
	{
		if(PI.PrintAlignment()) //Print an alignment form
		{
			//If successful
			CAlignDialog AD;
			AD.DoModal();  //Show the alignment dialog
			changed=AD.m_changed;  //Has the alignment dialog changed?
		}
		else
			Sleep(PRINT_PAUSE);
	}
	
	AlignmentCountdown=GET_APP->m_PrintInfo.AlignmentRate; //reset the alignment countdown
}

#endif

BOOL CPrinting::QueueEmpty(BOOL& AutoReg)
{
	CElectSoftView* pView=GET_APP->m_PrintInfo.pView;
	DWORD cJobs;
	
	if(!AutoReg)   //If we aren't auto regulating the pring queue
		return true;
	
	if(CPrinterInterface::PrintQueue(cJobs)) //Check the print queue
		return(!cJobs);  //If successful 
	
	pView->MessageBox("Unable to engage automatic print queue regulation", NULL, MB_ICONWARNING);
	AutoReg=false;  //stop auto regulating 
	return true;
}

void CPrinting::Step(BOOL& AutoReg, UINT& AlignmentCountdown, int& size)
{
	CElectSoftView* pView=GET_APP->m_PrintInfo.pView;
	
	if(!QueueEmpty(AutoReg))  //If there are documents in the print queue 
	{
		Sleep(PRINT_PAUSE);  //Sleep and try again later 
		return;
	}
	
	if(AlignmentCountdown)  // If a ballot should be printed 
		PrintBallot(size, AlignmentCountdown); //Print a ballot 
	else
		AlignPrinter(AlignmentCountdown);  //Align the printer 
}