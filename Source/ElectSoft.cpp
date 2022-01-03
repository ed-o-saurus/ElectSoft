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

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

BEGIN_MESSAGE_MAP(CElectSoftApp, CWinApp)
	ON_COMMAND(ID_ABOUT, OnAppAbout)
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
END_MESSAGE_MAP()

CElectSoftApp theApp;

BOOL CElectSoftApp::InitInstance()
{
	srand(CTime::GetCurrentTime().GetTime()); // seeds the random number generator
	
	if(!AfxSocketInit()) // initializes the socket routines 
		return false;
	
	if(!AfxInitRichEdit()) // in order to use a Rich Text edit box
		return false;
	
	Enable3dControls();
	
	AddDocTemplate(new CSingleDocTemplate(IDR_MAINFRAME,  // creates the only document template
		RUNTIME_CLASS(CElectSoftDoc), 
		RUNTIME_CLASS(CFrameWnd), 
		RUNTIME_CLASS(CElectSoftView)));
	
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);
	if(!ProcessShellCommand(cmdInfo)) // command line stuff 
		return false;
	
	CRegistyInterface::SetUpFileTypes(); // rigisters file types 
	SetRegistryKey("BehnWare Enterprises");
	EnableShellOpen();
	
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();
	
	FillGPL(); // fills m_GPL with the General Public Licence 
	
	return true;
}

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();
	enum { IDD = IDD_ABOUTBOX };
protected:
	virtual void DoDataExchange(CDataExchange* pDX);
private:
	CRichEditCtrl m_GPL;
	static DWORD CALLBACK Callback(DWORD dwCookie, LPBYTE pbBuff, long cb, long* pcb);
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD) {}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	char* pGPL=GET_APP->m_GPL.GetBuffer(0);
	EDITSTREAM es;
	
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GPL, m_GPL);
	
	es.dwCookie=(DWORD)(&pGPL);  // fill the GPL Rich Text box 
	es.pfnCallback=Callback;
	m_GPL.StreamIn(SF_RTF, es);
}

void CElectSoftApp::OnAppAbout() { CAboutDlg aboutDlg; aboutDlg.DoModal(); }

DWORD CALLBACK CAboutDlg::Callback(DWORD dwCookie, LPBYTE pbBuff, long cb, long* pcb)
{
	//dumps data into the Rich Text box
	
	char** pGPL=(char**)dwCookie;
	
	memcpy(pbBuff, *pGPL, *pcb=min(cb, (long)strlen(*pGPL)));
	(*pGPL)+=*pcb;
	return 0;
}

void CElectSoftApp::StartPrinting(CElectSoftView* pView, UINT AlignmentRate, ClassYear year, UINT size)
{
	// starts the printing thread 
	
	if(m_PrintInfo.bRunning) // if the thread is all ready running 
		return;
	
	m_PrintInfo.pView=pView;  // info used by the thread 
	m_PrintInfo.pPBallot=NULL;
	m_PrintInfo.AlignmentRate=AlignmentRate;
	m_PrintInfo.year=year;
	m_PrintInfo.size=size;
	
	m_PrintInfo.bKill=false; // clear any past kill message 
	m_PrintInfo.pThread=AfxBeginThread(CPrinting::MainRoutine, 0, // create the thread 
		THREAD_PRIORITY_NORMAL, 0, CREATE_SUSPENDED, NULL);
	m_PrintInfo.pThread->m_bAutoDelete=true; // the thread should delete itself when it finishes 
	m_PrintInfo.pThread->ResumeThread(); // start execution 
}

void CElectSoftApp::StopPrinting()
{
	// kills the printing thread 
	
	if(!m_PrintInfo.bRunning)  // if the thread is all ready stopped 
		return;
	
	m_PrintInfo.bKill=true; // send the message to kill the thread 
	
	WaitForSingleObject(m_PrintInfo.pThread, INFINITE); // wait for the thread to stop 
	
	if(m_PrintInfo.pPBallot) // if a print ballot needs to be posted 
	{
		m_PrintInfo.pView->InsertPrintBallot(m_PrintInfo.pPBallot); // post the ballot 
		m_PrintInfo.pPBallot=NULL;
	}
}

void CElectSoftApp::StartScanning(CElectSoftView* pView, BOOL voiding)
{
	// start the scanning thread 
	
	if(m_ScanInfo.bRunning)  // if the thread is all ready running 
		return;
	
#ifdef _SIM_BALLOT  // if we need to load the ballot list from a file 
	CString SS;
	
	m_InputBallots.RemoveAll();
	
	CFileDialog FD(true, NULL, "*.bls", OFN_FILEMUSTEXIST|OFN_HIDEREADONLY|OFN_PATHMUSTEXIST,
		"Ballot List (*.bls)|*.bls|All Files (*.*)|*.*||", NULL);
	
	if(FD.DoModal()!=IDOK)  // get the list
		return;
	
	CStdioFile SF(FD.GetPathName(), CFile::modeRead|CFile::typeText); // open the file 
	
	while(SF.ReadString(SS)) // load the file info memory 
	{
		SS.TrimLeft(); SS.TrimRight();
		if(!SS.IsEmpty())
			m_InputBallots.AddTail("c:\\ballots\\"+SS.Left(2)+'_'+SS.Right(5)+".txt");
	}
	
	SF.Close();
#endif
	
	m_ScanInfo.pView=pView; // info used by the thread 
	m_ScanInfo.voiding=voiding;
	m_ScanInfo.pSBallot=NULL;
	
	m_ScanInfo.bKill=false; // clear any past kill message 
	m_ScanInfo.pThread=AfxBeginThread(CScanning::MainRoutine, 0,  // create the thread 
		THREAD_PRIORITY_NORMAL, 0, CREATE_SUSPENDED, NULL);
	m_ScanInfo.pThread->m_bAutoDelete=true;  // the thread should delete itself when it finishes 
	m_ScanInfo.pThread->ResumeThread(); // start execution 
}

void CElectSoftApp::StopScanning()
{
	// kills the scanning thread 
	
	if(!m_ScanInfo.bRunning) // if the thread is all ready stopped 
		return;
	
	m_ScanInfo.bKill=true; // send the message to kill the thread 
	
	WaitForSingleObject(m_ScanInfo.pThread, INFINITE); // wait for the thread to stop 
	
	if(m_ScanInfo.pSBallot) // if a print ballot needs to be posted 
	{
		m_ScanInfo.pView->UpdateScanBallot(m_ScanInfo.pSBallot);
		m_ScanInfo.pSBallot=NULL;
	}
}

void CElectSoftApp::st_AlignInfo::ChangeParameters(int Tpos, int Rpos, int Lpos, int Bpos)
{
	// recalculate the ballot alignment parameters
	
	bx+=(2*Rpos-47*Lpos)/45; mx+=(Lpos-Rpos)/45;
	by+=(2*Tpos-49*Bpos)/47; my+=(Bpos-Tpos)/47;
}
