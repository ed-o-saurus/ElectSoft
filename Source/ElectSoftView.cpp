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
#include "ElectSoftView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CElectSoftView, CFormView)

BEGIN_MESSAGE_MAP(CElectSoftView, CFormView)
	ON_WM_SIZE()
	ON_NOTIFY(TCN_SELCHANGE, IDC_MAINTAB, OnSelchangeMaintab)
	ON_WM_TIMER()
	ON_COMMAND(ID_RACES_PROPERTIES, OnRacesProperties)
	ON_UPDATE_COMMAND_UI(ID_RACES_PROPERTIES, OnUpdateRacesProperties)
	ON_COMMAND(ID_RACES_LOAD, OnRacesLoad)
	ON_UPDATE_COMMAND_UI(ID_RACES_LOAD, OnUpdateRacesLoad)
	ON_COMMAND(ID_RACES_BALLOTPROPERTIES, OnRacesBallotProperties)
	ON_COMMAND(ID_PRINTING_ALIGN, OnPrintingAlign)
	ON_COMMAND(ID_PRINTING_PRINT, OnPrintingPrint)
	ON_UPDATE_COMMAND_UI(ID_PRINTING_PRINT, OnUpdatePrintingPrint)
	ON_COMMAND(ID_PRINTING_HISTORY, OnPrintingHistory)
	ON_UPDATE_COMMAND_UI(ID_PRINTING_HISTORY, OnUpdatePrintingHistory)
	ON_COMMAND(ID_SAMPLEBALLOT_AL, OnSampleBallotAL)
	ON_UPDATE_COMMAND_UI(ID_SAMPLEBALLOT_AL, OnUpdateSampleBallot)
	ON_COMMAND(ID_SAMPLEBALLOT_FR, OnSampleBallotFR)
	ON_UPDATE_COMMAND_UI(ID_SAMPLEBALLOT_FR, OnUpdateSampleBallot)
	ON_COMMAND(ID_SAMPLEBALLOT_SO, OnSampleBallotSO)
	ON_UPDATE_COMMAND_UI(ID_SAMPLEBALLOT_SO, OnUpdateSampleBallot)
	ON_COMMAND(ID_SAMPLEBALLOT_JR, OnSampleBallotJR)
	ON_UPDATE_COMMAND_UI(ID_SAMPLEBALLOT_JR, OnUpdateSampleBallot)
	ON_COMMAND(ID_SAMPLEBALLOT_SR, OnSampleBallotSR)
	ON_UPDATE_COMMAND_UI(ID_SAMPLEBALLOT_SR, OnUpdateSampleBallot)
	ON_COMMAND(ID_SAMPLEBALLOT_GR, OnSampleBallotGR)
	ON_UPDATE_COMMAND_UI(ID_SAMPLEBALLOT_GR, OnUpdateSampleBallot)
	ON_COMMAND(ID_PRINTING_LOCK, OnPrintingLock)
	ON_UPDATE_COMMAND_UI(ID_PRINTING_LOCK, OnUpdatePrintingLock)
	ON_COMMAND(ID_COUNTING_STUDENTS, OnCountingStudents)
	ON_UPDATE_COMMAND_UI(ID_COUNTING_STUDENTS, OnUpdateCountingStudents)
	ON_COMMAND(ID_COUNTING_NEW, OnCountingNew)
	ON_UPDATE_COMMAND_UI(ID_COUNTING_NEW, OnUpdateCountingNew)
	ON_COMMAND(ID_COUNTING_OPEN, OnCountingOpen)
	ON_UPDATE_COMMAND_UI(ID_COUNTING_OPEN, OnUpdateCountingNew)
	ON_COMMAND(ID_COUNTING_SAVE, OnCountingSave)
	ON_UPDATE_COMMAND_UI(ID_COUNTING_SAVE, OnUpdateCountingSave)
	ON_COMMAND(ID_COUNTING_SAVE_AS, OnCountingSaveAs)
	ON_UPDATE_COMMAND_UI(ID_COUNTING_SAVE_AS, OnUpdateCountingSave)
	ON_COMMAND(ID_COUNTING_PROPERTIES, OnCountingProperties)
	ON_UPDATE_COMMAND_UI(ID_COUNTING_PROPERTIES, OnUpdateCountingProperties)
	ON_COMMAND(ID_COUNTING_SCAN, OnCountingScan)
	ON_UPDATE_COMMAND_UI(ID_COUNTING_SCAN, OnUpdateCountingScan)
	ON_COMMAND(ID_COUNTING_REPORTLD, OnCountingReportLD)
	ON_UPDATE_COMMAND_UI(ID_COUNTING_REPORTLD, OnUpdateCountingReportLD)
	ON_COMMAND(ID_COUNTING_EXPORT, OnCountingExport)
	ON_UPDATE_COMMAND_UI(ID_COUNTING_EXPORT, OnUpdateCountingExport)
	ON_COMMAND(ID_COUNTING_INFORMATION, OnCountingInformation)
	ON_UPDATE_COMMAND_UI(ID_COUNTING_INFORMATION, OnUpdateCountingInformation)
	ON_COMMAND(ID_TIME_SYNC, OnTimeSync)
	ON_COMMAND(ID_TIME_AUTOSYNC, OnTimeAutosync)
	ON_UPDATE_COMMAND_UI(ID_TIME_AUTOSYNC, OnUpdateTimeAutosync)
	ON_COMMAND(ID_TIME_SERVER, OnTimeServer)
	ON_NOTIFY(NM_SETFOCUS, IDC_RACELIST_AL, OnSetfocusRacelistAL)
	ON_NOTIFY(NM_SETFOCUS, IDC_RACELIST_FR, OnSetfocusRacelistFR)
	ON_NOTIFY(NM_SETFOCUS, IDC_RACELIST_SO, OnSetfocusRacelistSO)
	ON_NOTIFY(NM_SETFOCUS, IDC_RACELIST_JR, OnSetfocusRacelistJR)
	ON_NOTIFY(NM_SETFOCUS, IDC_RACELIST_SR, OnSetfocusRacelistSR)
	ON_NOTIFY(NM_SETFOCUS, IDC_RACELIST_GR, OnSetfocusRacelistGR)
	ON_NOTIFY(NM_SETFOCUS, IDC_PRINTBALLOTS_AL, OnSetfocusPrintballotsAL)
	ON_NOTIFY(NM_SETFOCUS, IDC_PRINTBALLOTS_FR, OnSetfocusPrintballotsFR)
	ON_NOTIFY(NM_SETFOCUS, IDC_PRINTBALLOTS_SO, OnSetfocusPrintballotsSO)
	ON_NOTIFY(NM_SETFOCUS, IDC_PRINTBALLOTS_JR, OnSetfocusPrintballotsJR)
	ON_NOTIFY(NM_SETFOCUS, IDC_PRINTBALLOTS_SR, OnSetfocusPrintballotsSR)
	ON_NOTIFY(NM_SETFOCUS, IDC_PRINTBALLOTS_GR, OnSetfocusPrintballotsGR)
	ON_NOTIFY(NM_DBLCLK, IDC_SCANBALLOTS, OnDblclkScanBallots)
	ON_COMMAND(ID_RETURN, OnReturn)
	ON_NOTIFY(NM_DBLCLK, IDC_RACELIST_AL, OnDblclkRacelist)
	ON_NOTIFY(NM_DBLCLK, IDC_RACELIST_FR, OnDblclkRacelist)
	ON_NOTIFY(NM_DBLCLK, IDC_RACELIST_SO, OnDblclkRacelist)
	ON_NOTIFY(NM_DBLCLK, IDC_RACELIST_JR, OnDblclkRacelist)
	ON_NOTIFY(NM_DBLCLK, IDC_RACELIST_SR, OnDblclkRacelist)
	ON_NOTIFY(NM_DBLCLK, IDC_RACELIST_GR, OnDblclkRacelist)
	ON_NOTIFY(NM_DBLCLK, IDC_PRINTBALLOTS_AL, OnDblclkPrintBallots)
	ON_NOTIFY(NM_DBLCLK, IDC_PRINTBALLOTS_FR, OnDblclkPrintBallots)
	ON_NOTIFY(NM_DBLCLK, IDC_PRINTBALLOTS_SO, OnDblclkPrintBallots)
	ON_NOTIFY(NM_DBLCLK, IDC_PRINTBALLOTS_JR, OnDblclkPrintBallots)
	ON_NOTIFY(NM_DBLCLK, IDC_PRINTBALLOTS_SR, OnDblclkPrintBallots)
	ON_NOTIFY(NM_DBLCLK, IDC_PRINTBALLOTS_GR, OnDblclkPrintBallots)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_SCANBALLOTS, OnColumnclickScanballots)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_STUDENTLIST, OnColumnclickStudentlist)
	
	ON_COMMAND(ID_INSERTPRINTBALLOT, OnInsertPrintBallot)
	ON_COMMAND(ID_UPDATESCANBALLOT, OnUpdateScanBallot)
END_MESSAGE_MAP()

CElectSoftView::CElectSoftView() : CFormView(CElectSoftView::IDD) { m_TS.m_pView=this; }

void CElectSoftView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	
	DDX_Control(pDX, IDC_RACELIST_AL, m_RaceList_AL);
	DDX_Control(pDX, IDC_RACELIST_FR, m_RaceList_FR);
	DDX_Control(pDX, IDC_RACELIST_SO, m_RaceList_SO);
	DDX_Control(pDX, IDC_RACELIST_JR, m_RaceList_JR);
	DDX_Control(pDX, IDC_RACELIST_SR, m_RaceList_SR);
	DDX_Control(pDX, IDC_RACELIST_GR, m_RaceList_GR);
	
	DDX_Control(pDX, IDC_PRINTBALLOTS_AL, m_PrintBallotList_AL);
	DDX_Control(pDX, IDC_PRINTBALLOTS_FR, m_PrintBallotList_FR);
	DDX_Control(pDX, IDC_PRINTBALLOTS_SO, m_PrintBallotList_SO);
	DDX_Control(pDX, IDC_PRINTBALLOTS_JR, m_PrintBallotList_JR);
	DDX_Control(pDX, IDC_PRINTBALLOTS_SR, m_PrintBallotList_SR);
	DDX_Control(pDX, IDC_PRINTBALLOTS_GR, m_PrintBallotList_GR);
	
	DDX_Control(pDX, IDC_STUDENTLIST, m_StudentList);
	DDX_Control(pDX, IDC_SCANBALLOTS, m_ScanBallotList);
	
	DDX_Control(pDX, IDC_MAINTAB, m_MainTab);
}

void CElectSoftView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();
	
	m_MainTab.DeleteAllItems();  // put the four items on the main tab
	m_MainTab.InsertItem(0, "Races");
	m_MainTab.InsertItem(1, "Print Ballots");
	m_MainTab.InsertItem(2, "Students");
	m_MainTab.InsertItem(3, "Scan Ballots");
	
	RaceListCols(AL); RefreshRaceList(AL); // configure the RaceLists 
	RaceListCols(FR); RefreshRaceList(FR);
	RaceListCols(SO); RefreshRaceList(SO);
	RaceListCols(JR); RefreshRaceList(JR);
	RaceListCols(SR); RefreshRaceList(SR);
	RaceListCols(GR); RefreshRaceList(GR);
	
	PrintBallotListCols(AL); RefreshPrintBallotList(AL); // configure the PrintBallot Lists 
	PrintBallotListCols(FR); RefreshPrintBallotList(FR);
	PrintBallotListCols(SO); RefreshPrintBallotList(SO);
	PrintBallotListCols(JR); RefreshPrintBallotList(JR);
	PrintBallotListCols(SR); RefreshPrintBallotList(SR);
	PrintBallotListCols(GR); RefreshPrintBallotList(GR);
	
	while(m_StudentList.DeleteColumn(0)); // configure the StudentList 
	m_StudentList.InsertColumn(0, "RIN", LVCFMT_LEFT, 62);
	m_StudentList.InsertColumn(1, "Name", LVCFMT_LEFT, 113);
	m_StudentList.InsertColumn(2, "Year", LVCFMT_LEFT, 118);
	m_StudentList.InsertColumn(3, "Affiliation", LVCFMT_LEFT, 72);
	RefreshStudentList();
	
	while(m_ScanBallotList.DeleteColumn(0)); // configure the ScanBallot list 
	m_ScanBallotList.InsertColumn(0, "Serial Number", LVCFMT_LEFT, 80);
	m_ScanBallotList.InsertColumn(1, "Status", LVCFMT_LEFT, 85);
	m_ScanBallotList.InsertColumn(2, "Voter", LVCFMT_LEFT, 62);
	RefreshScanBallotList();
	
	m_MainTab.SetCurSel(0); // select the first tab 
	DisplayRaces();
	
	m_AutoSyncTime=false;
	m_RaceListSelected=AL;
	m_PrintBallotListSelected=AL;
}

#ifdef _DEBUG
CElectSoftDoc* CElectSoftView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CElectSoftDoc)));
	return (CElectSoftDoc*)m_pDocument;
}
#endif //_DEBUG

void CElectSoftView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	RefreshRaceList(AL); RefreshPrintBallotList(AL);
	RefreshRaceList(FR); RefreshPrintBallotList(FR);
	RefreshRaceList(SO); RefreshPrintBallotList(SO);
	RefreshRaceList(JR); RefreshPrintBallotList(JR);
	RefreshRaceList(SR); RefreshPrintBallotList(SR);
	RefreshRaceList(GR); RefreshPrintBallotList(GR);
	RefreshStudentList();
	RefreshScanBallotList();
}

void CElectSoftView::OnSize(UINT nType, int cx, int cy) 
{
	// this routine resizes all the items in the window
	
	CRect r;
	CSize size;
	CPoint Xoffset, Yoffset;
	CPoint FR_offset;
	CPoint AL_offset;
	CPoint SO_offset;
	CPoint JR_offset;
	CPoint SR_offset;
	CPoint GR_offset;
	
	CFormView::OnSize(nType, cx, cy);
	
	if(!GetDlgItem(IDC_MAINTAB))
		return;
	
	UpdateData(false);
	
	GetClientRect(r);
	r.DeflateRect(14, 14);
	m_MainTab.MoveWindow(r);
	r.DeflateRect(18, 36, 18, 18);
	
	size=CSize((r.Width()-10)/2, (r.Height()-20)/3);
	Xoffset=CPoint(size.cx+10, 0);
	Yoffset=CPoint(0, size.cy+10);
	
	AL_offset=0;				FR_offset=Xoffset;		
	SO_offset=Yoffset;			JR_offset=Xoffset+Yoffset;
	SR_offset=Yoffset+Yoffset;	GR_offset=Xoffset+Yoffset+Yoffset;
	
	RaceList(AL)->MoveWindow(CRect(r.TopLeft()+AL_offset, size));
	RaceList(FR)->MoveWindow(CRect(r.TopLeft()+FR_offset, size));
	RaceList(SO)->MoveWindow(CRect(r.TopLeft()+SO_offset, size));
	RaceList(JR)->MoveWindow(CRect(r.TopLeft()+JR_offset, size));
	RaceList(SR)->MoveWindow(CRect(r.TopLeft()+SR_offset, size));
	RaceList(GR)->MoveWindow(CRect(r.TopLeft()+GR_offset, size));
	
	size=CSize((r.Width()-20)/3, (r.Height()-10)/2);
	Xoffset=CPoint(size.cx+10, 0);
	Yoffset=CPoint(0, size.cy+10);
	
	AL_offset=0;		FR_offset=Xoffset;			SO_offset=Xoffset+Xoffset;
	JR_offset=Yoffset;	SR_offset=Xoffset+Yoffset;	GR_offset=Xoffset+Xoffset+Yoffset;
	
	PrintBallotList(AL)->MoveWindow(CRect(r.TopLeft()+AL_offset, size));
	PrintBallotList(FR)->MoveWindow(CRect(r.TopLeft()+FR_offset, size));
	PrintBallotList(SO)->MoveWindow(CRect(r.TopLeft()+SO_offset, size));
	PrintBallotList(JR)->MoveWindow(CRect(r.TopLeft()+JR_offset, size));
	PrintBallotList(SR)->MoveWindow(CRect(r.TopLeft()+SR_offset, size));
	PrintBallotList(GR)->MoveWindow(CRect(r.TopLeft()+GR_offset, size));
	
	m_StudentList.MoveWindow(r);
	m_ScanBallotList.MoveWindow(r);
	
	ShowScrollBar(SB_BOTH, false);
}

void CElectSoftView::RefreshRaceList(ClassYear year, CPrintRace* focus)
{
	// refill a particular RaceList and set the focus 
	
	CPrintRace* pPRace;
	int nItem;
	
	RaceList(year)->DeleteAllItems(); // clean up 
	RaceList(year)->EnableWindow();
	
	for(int position=0; position<GetDocument()->RaceCount(year); position++) // for each PrintRace
	{
		pPRace=GetDocument()->GetRaceAt(year, position);
		nItem=InsertRace(pPRace); //insert the race 
		if(pPRace==focus) // set the focus if appropriate
			RaceList(year)->SetItemState(nItem, LVIS_FOCUSED|LVIS_SELECTED, 
				LVIS_FOCUSED|LVIS_SELECTED); 
	}
}

int CElectSoftView::InsertRace(CPrintRace* pPRace)
{
	// insert a PrintRace
	
	CListCtrl* pList=RaceList(pPRace->GetYear());
	
	CString string;
	
	int nItem=pList->InsertItem(pList->GetItemCount(), pPRace->GetName());
	pList->SetItemText(nItem, 1, pPRace->GetCaption());
	string.Format("%d", pPRace->GetMaxVotes()); pList->SetItemText(nItem, 2, string);
	
	switch(pPRace->GetYear())
	{
	case AL: pList->SetItemText(nItem, 3, "All");       break;
	case FR: pList->SetItemText(nItem, 3, "Freshmen");  break;
	case SO: pList->SetItemText(nItem, 3, "Sophomore"); break;
	case JR: pList->SetItemText(nItem, 3, "Junior");    break;
	case SR: pList->SetItemText(nItem, 3, "Senior");    break;
	case GR: pList->SetItemText(nItem, 3, "Graduate");  break;
	}
	
	switch(pPRace->GetAff())
	{
	case BOTH:        pList->SetItemText(nItem, 4, "Both");        break;
	case GREEK:       pList->SetItemText(nItem, 4, "Greek");       break;
	case INDEPENDENT: pList->SetItemText(nItem, 4, "Independent"); break;
	}
	
	pList->SetItemData(nItem, (DWORD)pPRace);
	return nItem;
}

void CElectSoftView::RefreshPrintBallotList(ClassYear year)
{
	PrintBallotList(year)->DeleteAllItems();
	
	if(!GetDocument()->RacesLoaded())
	{
		PrintBallotList(year)->EnableWindow(false);
		return;
	}
	
	PrintBallotList(year)->EnableWindow();
	
	for(int number=0; number<GetDocument()->BallotCount(year); number++)
		InsertPrintBallot(GetDocument()->GetBallotAt(year, number));
}

void CElectSoftView::InsertPrintBallot(CPrintBallot* pPBallot)
{
	CListCtrl* pList=PrintBallotList(pPBallot->GetYear());
	
	int nItem=pList->InsertItem(pList->GetItemCount(), pPBallot->SerialString());
	pList->SetItemData(nItem, (DWORD)pPBallot);
}

void CElectSoftView::RefreshStudentList()
{
	m_StudentList.DeleteAllItems();
	
	if(!GetDocument()->StudentsLoaded())
	{
		m_StudentList.EnableWindow(false);
		return;
	}
	m_StudentList.EnableWindow(true);
	
	for(POSITION pos=GetDocument()->GetStartStudentPosition(); pos;)
		InsertStudent(GetDocument()->GetNextStudentPosition(pos));
	
	m_StudentList.SortItems(StudentListCompareFunc, 0);	
}

void CElectSoftView::InsertStudent(CStudent* pStudent)
{
	int nItem=m_StudentList.InsertItem(m_StudentList.GetItemCount(), pStudent->GetRIN());
	m_StudentList.SetItemText(nItem, 1, pStudent->GetName());
	m_StudentList.SetItemText(nItem, 2, pStudent->YearString());
	m_StudentList.SetItemText(nItem, 3, (pStudent->GetAff()==GREEK)?"Greek":"Independent");
	
	m_StudentList.SetItemData(nItem, (DWORD)pStudent);
}

void CElectSoftView::RefreshScanBallotList()
{
	int number;	
	CCount* pCount=GetDocument()->GetCount();
	m_ScanBallotList.DeleteAllItems();
	
	if(!pCount)
	{
		m_ScanBallotList.EnableWindow(false);
		return;
	}
	
	m_ScanBallotList.EnableWindow();
	
	for(number=0; number<pCount->BallotCount(AL); number++)
		InsertScanBallot(pCount->GetBallotAt(AL, number));
	
	for(number=0; number<pCount->BallotCount(FR); number++)
		InsertScanBallot(pCount->GetBallotAt(FR, number));
	
	for(number=0; number<pCount->BallotCount(SO); number++)
		InsertScanBallot(pCount->GetBallotAt(SO, number));
	
	for(number=0; number<pCount->BallotCount(JR); number++)
		InsertScanBallot(pCount->GetBallotAt(JR, number));
	
	for(number=0; number<pCount->BallotCount(SR); number++)
		InsertScanBallot(pCount->GetBallotAt(SR, number));
	
	for(number=0; number<pCount->BallotCount(GR); number++)
		InsertScanBallot(pCount->GetBallotAt(GR, number));
}

void CElectSoftView::InsertScanBallot(CScanBallot* pSBallot)
{
	int nItem=m_ScanBallotList.InsertItem(m_ScanBallotList.GetItemCount(), pSBallot->SerialString());
	
	switch(pSBallot->GetStatus())
	{
	case OUTSTANDING:
		m_ScanBallotList.SetItemText(nItem, 1, "Outstanding");
		m_ScanBallotList.SetItemText(nItem, 2, "");
		break;
	case COUNTED:
		m_ScanBallotList.SetItemText(nItem, 1, "Counted");
		m_ScanBallotList.SetItemText(nItem, 2, pSBallot->GetRIN());
		break;
	case REPORTED_LOST_DESTROYED:
		m_ScanBallotList.SetItemText(nItem, 1, "Lost/Destroyed");
		m_ScanBallotList.SetItemText(nItem, 2, "");
		break;
	case VOIDED:
		m_ScanBallotList.SetItemText(nItem, 1, "Voided");
		m_ScanBallotList.SetItemText(nItem, 2, "");
		break;
	}
	
	m_ScanBallotList.SetItemData(nItem, (DWORD)pSBallot);
}

void CElectSoftView::OnSelchangeMaintab(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// when the user changes the selection on the main tab
	
	switch(m_MainTab.GetCurSel())
	{
	case 0: DisplayRaces(); break;
	case 1: DisplayPrintBallots(); break;
	case 2: DisplayStudents(); break;
	case 3: DisplayScanBallots(); break;
	}
	*pResult = 0;
}

void CElectSoftView::DisplayRaces()
{
	// display the races tab
	
	RaceList(AL)->ShowWindow(SW_SHOW);
	RaceList(FR)->ShowWindow(SW_SHOW);
	RaceList(SO)->ShowWindow(SW_SHOW);
	RaceList(JR)->ShowWindow(SW_SHOW);
	RaceList(SR)->ShowWindow(SW_SHOW);
	RaceList(GR)->ShowWindow(SW_SHOW);
	m_MainTab.BringWindowToTop();
	RaceList(AL)->BringWindowToTop();
	RaceList(FR)->BringWindowToTop();
	RaceList(SO)->BringWindowToTop();
	RaceList(JR)->BringWindowToTop();
	RaceList(SR)->BringWindowToTop();
	RaceList(GR)->BringWindowToTop();
	
	m_StudentList.ShowWindow(SW_HIDE);
	PrintBallotList(AL)->ShowWindow(SW_HIDE);
	PrintBallotList(FR)->ShowWindow(SW_HIDE);
	PrintBallotList(SO)->ShowWindow(SW_HIDE);
	PrintBallotList(JR)->ShowWindow(SW_HIDE);
	PrintBallotList(SR)->ShowWindow(SW_HIDE);
	PrintBallotList(GR)->ShowWindow(SW_HIDE);
	m_ScanBallotList.ShowWindow(SW_HIDE);
}

void CElectSoftView::DisplayPrintBallots()
{
	// display the PrintBallots tab
	
	PrintBallotList(AL)->ShowWindow(SW_SHOW);
	PrintBallotList(FR)->ShowWindow(SW_SHOW);
	PrintBallotList(SO)->ShowWindow(SW_SHOW);
	PrintBallotList(JR)->ShowWindow(SW_SHOW);
	PrintBallotList(SR)->ShowWindow(SW_SHOW);
	PrintBallotList(GR)->ShowWindow(SW_SHOW);
	m_MainTab.BringWindowToTop();
	PrintBallotList(AL)->BringWindowToTop();
	PrintBallotList(FR)->BringWindowToTop();
	PrintBallotList(SO)->BringWindowToTop();
	PrintBallotList(JR)->BringWindowToTop();
	PrintBallotList(SR)->BringWindowToTop();
	PrintBallotList(GR)->BringWindowToTop();
	
	m_StudentList.ShowWindow(SW_HIDE);
	RaceList(AL)->ShowWindow(SW_HIDE);
	RaceList(FR)->ShowWindow(SW_HIDE);
	RaceList(SO)->ShowWindow(SW_HIDE);
	RaceList(JR)->ShowWindow(SW_HIDE);
	RaceList(SR)->ShowWindow(SW_HIDE);
	RaceList(GR)->ShowWindow(SW_HIDE);
	m_ScanBallotList.ShowWindow(SW_HIDE);
}

void CElectSoftView::DisplayStudents()
{
	// display the students tab
	
	m_StudentList.ShowWindow(SW_SHOW);
	m_MainTab.BringWindowToTop();
	m_StudentList.BringWindowToTop();
	
	RaceList(AL)->ShowWindow(SW_HIDE);
	RaceList(FR)->ShowWindow(SW_HIDE);
	RaceList(SO)->ShowWindow(SW_HIDE);
	RaceList(JR)->ShowWindow(SW_HIDE);
	RaceList(SR)->ShowWindow(SW_HIDE);
	RaceList(GR)->ShowWindow(SW_HIDE);
	PrintBallotList(AL)->ShowWindow(SW_HIDE);
	PrintBallotList(FR)->ShowWindow(SW_HIDE);
	PrintBallotList(SO)->ShowWindow(SW_HIDE);
	PrintBallotList(JR)->ShowWindow(SW_HIDE);
	PrintBallotList(SR)->ShowWindow(SW_HIDE);
	PrintBallotList(GR)->ShowWindow(SW_HIDE);
	m_ScanBallotList.ShowWindow(SW_HIDE);
}

void CElectSoftView::DisplayScanBallots()
{
	// display the ScanBallot tab
	
	m_ScanBallotList.ShowWindow(SW_SHOW);
	m_MainTab.BringWindowToTop();
	m_ScanBallotList.BringWindowToTop();
	
	m_StudentList.ShowWindow(SW_HIDE);
	RaceList(AL)->ShowWindow(SW_HIDE);
	RaceList(FR)->ShowWindow(SW_HIDE);
	RaceList(SO)->ShowWindow(SW_HIDE);
	RaceList(JR)->ShowWindow(SW_HIDE);
	RaceList(SR)->ShowWindow(SW_HIDE);
	RaceList(GR)->ShowWindow(SW_HIDE);
	PrintBallotList(AL)->ShowWindow(SW_HIDE);
	PrintBallotList(FR)->ShowWindow(SW_HIDE);
	PrintBallotList(SO)->ShowWindow(SW_HIDE);
	PrintBallotList(JR)->ShowWindow(SW_HIDE);
	PrintBallotList(SR)->ShowWindow(SW_HIDE);
	PrintBallotList(GR)->ShowWindow(SW_HIDE);
}

CPrintBallot* CElectSoftView::GetSelectedPrintBallot()
{
	// returns a pointer to the PrintBallot that is selected 
	
	CListCtrl* pList=PrintBallotList(m_PrintBallotListSelected);
	POSITION pos=pList->GetFirstSelectedItemPosition();
	
	if(!pos)
		return NULL;
	
	return (CPrintBallot*)(pList->GetItemData(pList->GetNextSelectedItem(pos)));
}

CPrintRace* CElectSoftView::GetSelectedRace()
{
	// returns a pointer to the Race that is selected 
	
	CListCtrl* pList=RaceList(m_RaceListSelected);
	POSITION pos=pList->GetFirstSelectedItemPosition();
	if(!pos)
		return NULL;
	
	return (CPrintRace*)pList->GetItemData(pList->GetNextSelectedItem(pos));
}

void CElectSoftView::UpdateScanBallot(CScanBallot* pSBallot)
{
	// refreshed the info for a ScanBallot
	
	LVFINDINFO FindInfo;
	int nItem;
	
	FindInfo.flags=LVFI_PARAM;
	FindInfo.lParam=(DWORD)pSBallot;
	
	if((nItem=m_ScanBallotList.FindItem(&FindInfo))==(-1))
		return;	
	
	switch(pSBallot->GetStatus())
	{
	case OUTSTANDING:
		m_ScanBallotList.SetItemText(nItem, 1, "Outstanding");
		m_ScanBallotList.SetItemText(nItem, 2, "");
		break;
	case COUNTED:
		m_ScanBallotList.SetItemText(nItem, 1, "Counted");
		m_ScanBallotList.SetItemText(nItem, 2, pSBallot->GetRIN());
		break;
	case REPORTED_LOST_DESTROYED:
		m_ScanBallotList.SetItemText(nItem, 1, "Lost/Destroyed");
		m_ScanBallotList.SetItemText(nItem, 2, "");
		break;
	case VOIDED:
		m_ScanBallotList.SetItemText(nItem, 1, "Voided");
		m_ScanBallotList.SetItemText(nItem, 2, "");
		break;
	}
}

void CElectSoftView::OnTimer(UINT nIDEvent) 
{
	// send a request to the time server for an update
	
	m_TS.TrasRequest(false);
	CFormView::OnTimer(nIDEvent);
}

CScanBallot* CElectSoftView::GetSelectedScanBallot()
{
	// returns a pointer to the ScanBallot that is selected 
		
	POSITION pos=m_ScanBallotList.GetFirstSelectedItemPosition();
	
	if(!pos)
		return NULL;
	
	return (CScanBallot*)m_ScanBallotList.GetItemData(m_ScanBallotList.GetNextSelectedItem(pos));
}

CListCtrl* CElectSoftView::PrintBallotList(ClassYear year)
{
	switch(year)
	{
	case AL: return &m_PrintBallotList_AL;
	case FR: return &m_PrintBallotList_FR;
	case SO: return &m_PrintBallotList_SO;
	case JR: return &m_PrintBallotList_JR;
	case SR: return &m_PrintBallotList_SR;
	case GR: return &m_PrintBallotList_GR;
	default: ASSERT(false); return NULL;
	}
}

CListCtrl* CElectSoftView::RaceList(ClassYear year)
{
	switch(year)
	{
	case AL: return &m_RaceList_AL;
	case FR: return &m_RaceList_FR;
	case SO: return &m_RaceList_SO;
	case JR: return &m_RaceList_JR;
	case SR: return &m_RaceList_SR;
	case GR: return &m_RaceList_GR;
	default: ASSERT(false); return NULL;
	}
}

void CElectSoftView::RaceListCols(ClassYear year)
{
	// sets the columns of a RaceList
	
	CListCtrl* pList=RaceList(year);

	while(pList->DeleteColumn(0));
	pList->InsertColumn(0, "Name", LVCFMT_LEFT, 73);
	pList->InsertColumn(1, "Caption", LVCFMT_LEFT, 73);
	pList->InsertColumn(2, "Maximum Votes", LVCFMT_LEFT, 66);
	pList->InsertColumn(3, "Year", LVCFMT_LEFT, 45);
	pList->InsertColumn(4, "Affiliation", LVCFMT_LEFT, 79);
}

void CElectSoftView::PrintBallotListCols(ClassYear year)
{
	// sets the columns of a PrintBallotList
	
	CListCtrl* pList=PrintBallotList(year);

	while(pList->DeleteColumn(0));
	pList->InsertColumn(0, "Serial Number", LVCFMT_LEFT, 80);
}

void CElectSoftView::OnRacesProperties()
{
	// displays the properties of the selected race
	
	CRaceDialog RD;
	CPrintRace* pPRace=GetSelectedRace();
	if(!pPRace)
		return;
	
	RD.m_pPRace=pPRace;
	RD.DoModal();
}

void CElectSoftView::OnRacesLoad()
{
	// loads the races from a file
	
	int err_line;
	CFileDialog FD(true, NULL, "*.rac", OFN_FILEMUSTEXIST|OFN_HIDEREADONLY|OFN_PATHMUSTEXIST, 
		"Race Files (*.rac)|*.rac|All Files (*.*)|*.*||", NULL);
	
	if(FD.DoModal()!=IDOK) // get the filename 
		return;
	
	CStdioFile SF(FD.GetPathName(), CFile::modeRead|CFile::typeText); // open the file 
	err_line=GetDocument()->LoadRaces(&SF);  // read the data 
	SF.Close(); //close the port 
	
	if(err_line) //if there is an error 
	{
		CString err;
		err.Format("Error in line %d", err_line);
		MessageBox(err, NULL, MB_ICONERROR);
		return;
	}
	
	if(!GetDocument()->Position())  // position the races 
	{
		GetDocument()->UnloadRaces();
		MessageBox("Unable to position races", NULL, MB_ICONERROR);
		return;
	}
	
	RefreshRaceList(AL); RefreshPrintBallotList(AL);
	RefreshRaceList(FR); RefreshPrintBallotList(FR);
	RefreshRaceList(SO); RefreshPrintBallotList(SO);
	RefreshRaceList(JR); RefreshPrintBallotList(JR);
	RefreshRaceList(SR); RefreshPrintBallotList(SR);
	RefreshRaceList(GR); RefreshPrintBallotList(GR);
	
	GetDocument()->SetTitle(FD.GetFileTitle());
	m_MainTab.SetCurSel(0);
	DisplayRaces();
}

void CElectSoftView::OnRacesBallotProperties()
{
	// deisplays the properties of the selected race 
	
	CBallotPropertiesDialog BPD;
	BPD.m_pDoc=GetDocument();
	BPD.DoModal();
}

#ifdef _SIM_BALLOT

void CElectSoftView::OnPrintingAlign()
{
	// just show the alignment dialog without printing anything
	
	BOOL changed;
	
	do
	{
		CAlignDialog AD;
		AD.DoModal();
		changed=AD.m_changed;
	}
	while(changed);
}

#else

void CElectSoftView::OnPrintingAlign()
{
	// align the printer 
	
	CPrinterInterface PI;
	BOOL changed;
	
	if(!CPrinterInterface::CheckPrinterConfig()) // make sure the paper size is correct
	{
		MessageBox("Incorrect Printer Configuration", NULL, MB_ICONERROR);
		return;
	}
	
	do
	{
		if(!PI.PrintAlignment())  // print the ballot 
			return;
		
		CAlignDialog AD;
		AD.DoModal();  // recalculate the info 
		changed=AD.m_changed;
	}
	while(changed);
}

#endif

void CElectSoftView::OnPrintingPrint()
{
	// start or stop printing
	
	if(GET_APP->m_PrintInfo.bRunning) // if we are printing, stop 
	{
		GET_APP->StopPrinting();
		return;
	}
	
	CBallotOrder BO;
	if(BO.DoModal()!=IDOK) // get the number of ballots 
		return;
	
	GET_APP->StartPrinting(this, BO.m_AlignmentRate, BO.m_year, BO.m_size); // start printing
	m_MainTab.SetCurSel(1);
	DisplayPrintBallots();
}

void CElectSoftView::OnUpdatePrintingPrint(CCmdUI* pCmdUI)
{
	// display the appropriate menu item for printing 
	
	if(!GetDocument()->RacesLoaded()) // if no races loaded, we can't print
	{
		pCmdUI->SetText("&Start Printing");
		pCmdUI->Enable(false);
		return;
	}

	if(GET_APP->m_PrintInfo.bRunning) // if we're running, give the option to stop 
	{
		pCmdUI->SetText("&Stop Printing");
		pCmdUI->Enable();
		return;
	}
	
	pCmdUI->SetText("&Start Printing"); // give the option to start 
	pCmdUI->Enable(GetDocument()->BallotsUnlocked());
}

void CElectSoftView::OnPrintingHistory()
{
	// get the history of the selected ballot 
	
	CPrintBallot* pPBallot=GetSelectedPrintBallot();
	if(pPBallot)
	{
		CPrintBallotDialog PBD;
		PBD.m_pPBallot=pPBallot;
		PBD.DoModal();
	}
}

void CElectSoftView::SampleBallot(ClassYear year)
{
	// prints a sample ballot
	
	if(!CPrinterInterface::CheckPrinterConfig())
	{
		MessageBox("Incorrect Printer Configuration", NULL, MB_ICONERROR);
		return;
	}
	
	CPrinterInterface PI;
	PI.Print(year, GetDocument(), true);
}

void CElectSoftView::OnPrintingLock()
{
	// locks the printballots
	// This prevents printing of additional ballots and allows the scanning of ballots 
	
	if(MessageBox(
		"Locking the ballots will prevent any further changes.\nDo you want to proceed?", 
		NULL, MB_ICONQUESTION|MB_YESNO)==IDYES)
	{
		GetDocument()->LockBallots();
		MessageBox("Ballots Locked", NULL, MB_ICONEXCLAMATION);
	}
}

void CElectSoftView::OnUpdatePrintingLock(CCmdUI* pCmdUI)
{
	// causes the menu item that is used to lock ballots to be displayed properly
	
	if(!GetDocument()->RacesLoaded()) // can't lock ballots with out haveing loaded races 
	{
		pCmdUI->Enable(false);
		return;
	}
	
	if(!GetDocument()->BallotsUnlocked()) // can't re-lock ballots 
	{
		pCmdUI->Enable(false);
		return;
	}
	
	pCmdUI->Enable(!GET_APP->m_PrintInfo.bRunning); // can't lock ballots while printing is in progress 
}

void CElectSoftView::OnCountingStudents()
{
	// load or unload students 
	
	int err_line;
	CString Duplicate_RIN, success;
	
	if(GetDocument()->StudentsLoaded()) // if students are loaded, unload them 
	{
		GetDocument()->UnloadStudents();		
		RefreshStudentList();
		return;
	}
	
	CFileDialog FD(true, NULL, "students.stu", OFN_FILEMUSTEXIST|OFN_HIDEREADONLY|OFN_PATHMUSTEXIST, 
		"Student Files (*.stu)|*.stu|All Files (*.*)|*.*||", NULL);
	
	if(FD.DoModal()!=IDOK) // get the filename 
		return;
	
	CStdioFile SF(FD.GetPathName(), CFile::modeRead|CFile::typeText);
	err_line=GetDocument()->LoadStudents(&SF, Duplicate_RIN); // parse the file 
	SF.Close();
	
	if(err_line) // if there is an error 
	{
		CString err;
		err.Format("Error in line %d", err_line);
		MessageBox(err, NULL, MB_ICONERROR);
		return;
	}
	
	if(!Duplicate_RIN.IsEmpty()) // if there is a duplicate RIN
	{
		MessageBox("Duplicate RIN ("+Duplicate_RIN+")", NULL, MB_ICONERROR);
		return;
	}
	
	RefreshStudentList();
	m_MainTab.SetCurSel(2);
	DisplayStudents();
	
	success.Format("%d students successfully loaded", m_StudentList.GetItemCount());
	MessageBox(success, NULL, MB_ICONINFORMATION);
}

void CElectSoftView::OnUpdateCountingStudents(CCmdUI* pCmdUI)
{
	// causes the student load/unload menu item to be displayed properly
	
	if(GetDocument()->StudentsLoaded()) // if the student's are loaded, give the option to unload
	{
		pCmdUI->SetText("Unload Students");
		pCmdUI->Enable(!GET_APP->m_ScanInfo.bRunning);
		return;
	}
	
	pCmdUI->SetText("Load Students");
	pCmdUI->Enable();
}

void CElectSoftView::OnCountingNew()
{
	// create a new count
	
	if(GetDocument()->GetCount()) // save the old count
		if(!GetDocument()->GetCount()->SaveModified())
			return;
	
	GetDocument()->ReplaceCount(new CCount(GetDocument())); // generate a new count
	RefreshScanBallotList();
	m_MainTab.SetCurSel(3);
	DisplayScanBallots();
}

void CElectSoftView::OnCountingOpen()
{
	// open an old count 
	
	BOOL valid;
	
	if(GetDocument()->GetCount()) // save aold count
		if(!GetDocument()->GetCount()->SaveModified())
			return;
	
	CCount* pCount=new CCount(GetDocument()); // create a new count
	
	CFileDialog FD(true, NULL, "*.cou", OFN_FILEMUSTEXIST|OFN_HIDEREADONLY|OFN_PATHMUSTEXIST, 
		"Count Files (*.cou)|*.cou|All Files (*.*)|*.*||", NULL);
	
	if(FD.DoModal()!=IDOK)
		return;
	
	CStdioFile SF(FD.GetPathName(), CFile::modeRead|CFile::typeText);
	valid=pCount->Open(&SF); //read the file 
	SF.Close();
	
	if(!valid) // if the file is formated incorrectly 
	{
		MessageBox("Invalid Count File", NULL, MB_ICONERROR);
		delete pCount;
		return;
	}
	
	GetDocument()->ReplaceCount(pCount);
	RefreshScanBallotList();
	m_MainTab.SetCurSel(3);
	DisplayScanBallots();
}

void CElectSoftView::OnCountingProperties()
{
	// display the count's name
	
	CCountDialog CD;
	CD.m_pCount=GetDocument()->GetCount();
	CD.DoModal();
}

void CElectSoftView::OnCountingScan()
{
	// start/stop scanning 
	
	if(GET_APP->m_ScanInfo.bRunning)
		GET_APP->StopScanning();
	else
		switch(MessageBox("Do you want to count these ballots?\nClick 'yes' to count\nClick 'no' to void", 
			NULL, MB_ICONQUESTION|MB_YESNOCANCEL))
		{
		case IDYES: GET_APP->StartScanning(this, false); break;
		case IDNO:  GET_APP->StartScanning(this, true);  break;
		}
}

void CElectSoftView::OnUpdateCountingScan(CCmdUI* pCmdUI)
{
	// stet up the start/stop scanning menu item 
	
	if(!GetDocument()->GetCount())
	{
		pCmdUI->SetText("Start Scanning");
		pCmdUI->Enable(false);
		return;
	}
	
	if(GET_APP->m_ScanInfo.bRunning)
	{
		pCmdUI->SetText("Stop Scanning");
		pCmdUI->Enable();
		return;
	}
	
	pCmdUI->SetText("Start Scanning");
	pCmdUI->Enable(GetDocument()->StudentsLoaded());
}

void CElectSoftView::OnCountingReportLD()
{
	// report a ballot lost or destroyed
	
	ClassYear year;
	int number;
	CScanBallot* pSBallot;
	
	if(m_MainTab.GetCurSel()!=3)
		return;
	
	if(!(pSBallot=GetSelectedScanBallot()))
		return;
	
	switch(pSBallot->GetStatus())
	{
	case COUNTED:
		if(MessageBox(
			"This ballot has been counted.\nDo you want it to be reported lost or destroyed?", 
			NULL, MB_ICONWARNING|MB_YESNO)==IDNO)
			return;
		break;
	case VOIDED:
		if(MessageBox(
			"This ballot has been voided.\nDo you want it to be reported lost or destroyed?", 
			NULL, MB_ICONWARNING|MB_YESNO)==IDNO)
			return;
		break;
	case REPORTED_LOST_DESTROYED: return;
	}
	
	pSBallot->GetSerial(year, number);
	pSBallot->SetStatus(REPORTED_LOST_DESTROYED);
	GetDocument()->GetBallotAt(year, number)->AddEvent(REPORTED_LOST_DESTROYED, GetDocument());
	GetDocument()->GetCount()->SetModifiedFlag();
	
	UpdateScanBallot(pSBallot);	
}

void CElectSoftView::OnCountingExport()
{
	// writes a count report
	
	CFileDialog FD(false, "txt", GetDocument()->GetCount()->GetTitle(), OFN_HIDEREADONLY,
		"Text Files (*.txt)|*.txt|All Files (*.*)|*.*||", NULL);
	
	if(FD.DoModal()!=IDOK)
		return;
	
	CStdioFile SF(FD.GetPathName(), CFile::modeWrite|CFile::modeCreate|CFile::typeText);
	CCountReport CR;
	CR.WriteReport(GetDocument(), &SF);
	SF.Close();
}

void CElectSoftView::OnCountingInformation()
{
	// display the info for a ScanBallot
	
	CScanBallot* pSBallot=GetSelectedScanBallot();
	
	if(!pSBallot)
		return;
	
	if(pSBallot->GetStatus()!=COUNTED)
		return;
	
	CScanBallotDialog SBD;
	SBD.m_pSBallot=pSBallot;
	SBD.m_pCount=GetDocument()->GetCount();
	SBD.DoModal();
}

void CElectSoftView::OnTimeAutosync()
{
	// toggle the time autosync
	
	if(m_AutoSyncTime=(!m_AutoSyncTime))
	{
		SetTimer(1, 300000, NULL);
		OnTimer(1);
	}
	else
		KillTimer(1);
}

void CElectSoftView::OnTimeServer()
{
	// change the time server
	
	CTimeServerDialog TSD;
	TSD.DoModal();
}

void CElectSoftView::OnReturn() 
{
	//when the user presses the return key
	
	switch(m_MainTab.GetCurSel())
	{
	case 0:	OnRacesProperties(); return;
	case 1: OnPrintingHistory(); return;
	case 3: OnCountingInformation(); return;
	}
}

void CElectSoftView::OnColumnclickScanballots(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// when the user clicks on the top of the ScanBallotList, sort
	
	m_ScanBallotList.SortItems(ScanBallotsCompareFunc, ((NM_LISTVIEW*)pNMHDR)->iSubItem);
	*pResult = 0;
}

int CALLBACK CElectSoftView::ScanBallotsCompareFunc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
	// comares ScanBallots for sorting
	
	CScanBallot* pSBallot1=(CScanBallot*)lParam1;
	CScanBallot* pSBallot2=(CScanBallot*)lParam2;

	switch(lParamSort)
	{
	case 0:
		ClassYear year1, year2;
		int number1, number2;
		
		pSBallot1->GetSerial(year1, number1);
		pSBallot2->GetSerial(year2, number2);
		
		return (year1==year2)?(number1-number2):(year1-year2);
	case 1: return (pSBallot1->GetStatus())-(pSBallot2->GetStatus());
	case 2: return pSBallot1->GetRIN().Compare(pSBallot2->GetRIN());
	default: ASSERT(false); return 0;
	}
}

void CElectSoftView::OnColumnclickStudentlist(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// when the user clicks on the top of the student list, sort
	
	m_StudentList.SortItems(StudentListCompareFunc, ((NM_LISTVIEW*)pNMHDR)->iSubItem);	
	*pResult = 0;
}

int CALLBACK CElectSoftView::StudentListCompareFunc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
	// comares students for sorting
	
	CStudent* pStudent1=(CStudent*)lParam1;
	CStudent* pStudent2=(CStudent*)lParam2;
	
	switch(lParamSort)
	{
	case 0: return pStudent1->GetRIN().Compare(pStudent2->GetRIN());
	case 1: return pStudent1->GetName().Compare(pStudent2->GetName());
	case 2: return 0;
	case 3: return (pStudent1->GetAff())-(pStudent2->GetAff());
	default: ASSERT(false); return 0;
	}
}

void CElectSoftView::OnInsertPrintBallot()
{
	// inserts a PrintBallot into the list
	
	if(GET_APP->m_PrintInfo.pPBallot)
	{
		InsertPrintBallot(GET_APP->m_PrintInfo.pPBallot);
		GET_APP->m_PrintInfo.pPBallot=NULL;
	}
}

void CElectSoftView::OnUpdateScanBallot()
{
	// updates a ScanBallot
	
	if(GET_APP->m_ScanInfo.pSBallot)
	{
		UpdateScanBallot(GET_APP->m_ScanInfo.pSBallot);
		GET_APP->m_ScanInfo.pSBallot=NULL;
	}
}