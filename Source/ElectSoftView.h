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


#if !defined(AFX_ELECTSOFTVIEW_H__69E5602C_562F_11D6_B47E_00B0D0CDB4FC__INCLUDED_)
#define AFX_ELECTSOFTVIEW_H__69E5602C_562F_11D6_B47E_00B0D0CDB4FC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "AlignDialog.h"
#include "BallotOrder.h"
#include "BallotPropertiesDialog.h"
#include "Count.h"
#include "CountDialog.h"
#include "CountReport.h"
#include "ElectSoftDoc.h"
#include "PrintBallotDialog.h"
#include "PrinterInterface.h"
#include "RaceDialog.h"
#include "ScanBallotDialog.h"
#include "TimeServerDialog.h"
#include "TimeSocket.h"

class CElectSoftView : public CFormView
{
protected: // create from serialization only
	CElectSoftView();
	DECLARE_DYNCREATE(CElectSoftView)

private:
	enum { IDD = IDD_ELECTSOFT_FORM };
	CTabCtrl m_MainTab;
	CListCtrl m_RaceList_AL;
	CListCtrl m_RaceList_FR;
	CListCtrl m_RaceList_SO;
	CListCtrl m_RaceList_JR;
	CListCtrl m_RaceList_SR;
	CListCtrl m_RaceList_GR;
	CListCtrl m_PrintBallotList_AL;
	CListCtrl m_PrintBallotList_FR;
	CListCtrl m_PrintBallotList_SO;
	CListCtrl m_PrintBallotList_JR;
	CListCtrl m_PrintBallotList_SR;
	CListCtrl m_PrintBallotList_GR;
	CListCtrl m_StudentList;
	CListCtrl m_ScanBallotList;
public:
	CElectSoftDoc* GetDocument();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate(); // called first time after construct
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
public:
	void UpdateScanBallot(CScanBallot* pSBallot);
	void InsertPrintBallot(CPrintBallot* pPBallot);

protected:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSelchangeMaintab(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnRacesProperties();
	afx_msg void OnUpdateRacesProperties(CCmdUI* pCmdUI) { pCmdUI->Enable(GetSelectedRace()!=NULL); }
	afx_msg void OnRacesLoad();
	afx_msg void OnUpdateRacesLoad(CCmdUI* pCmdUI) { pCmdUI->Enable(!GetDocument()->RacesLoaded()); }
	afx_msg void OnRacesBallotProperties();
	afx_msg void OnPrintingAlign();
	afx_msg void OnPrintingPrint();
	afx_msg void OnUpdatePrintingPrint(CCmdUI* pCmdUI);
	afx_msg void OnPrintingHistory();
	afx_msg void OnUpdatePrintingHistory(CCmdUI* pCmdUI) { pCmdUI->Enable(GetSelectedPrintBallot()!=NULL); }
	afx_msg void OnSampleBallotAL() { SampleBallot(AL); }
	afx_msg void OnSampleBallotFR() { SampleBallot(FR); }
	afx_msg void OnSampleBallotSO() { SampleBallot(SO); }
	afx_msg void OnSampleBallotJR() { SampleBallot(JR); }
	afx_msg void OnSampleBallotSR() { SampleBallot(SR); }
	afx_msg void OnSampleBallotGR() { SampleBallot(GR); }
	afx_msg void OnUpdateSampleBallot(CCmdUI* pCmdUI) { pCmdUI->Enable(GetDocument()->RacesLoaded()); }
	afx_msg void OnPrintingLock();
	afx_msg void OnUpdatePrintingLock(CCmdUI* pCmdUI);
	afx_msg void OnCountingStudents();
	afx_msg void OnUpdateCountingStudents(CCmdUI* pCmdUI);
	afx_msg void OnCountingNew();
	afx_msg void OnUpdateCountingNew(CCmdUI* pCmdUI) { pCmdUI->Enable(GetDocument()->BallotsLocked()); }
	afx_msg void OnCountingOpen();
	afx_msg void OnCountingSave() { GetDocument()->GetCount()->Save(false); }
	afx_msg void OnUpdateCountingSave(CCmdUI* pCmdUI) { pCmdUI->Enable(GetDocument()->GetCount()!=NULL); }
	afx_msg void OnCountingSaveAs() { GetDocument()->GetCount()->Save(true); }
	afx_msg void OnCountingProperties();
	afx_msg void OnUpdateCountingProperties(CCmdUI* pCmdUI) { pCmdUI->Enable(GetDocument()->GetCount()!=NULL); }
	afx_msg void OnCountingScan();
	afx_msg void OnUpdateCountingScan(CCmdUI* pCmdUI);
	afx_msg void OnCountingReportLD();
	afx_msg void OnUpdateCountingReportLD(CCmdUI* pCmdUI) { pCmdUI->Enable(GetSelectedScanBallot()!=NULL); }
	afx_msg void OnCountingExport();
	afx_msg void OnUpdateCountingExport(CCmdUI* pCmdUI) { pCmdUI->Enable((GetDocument()->GetCount())&&(GetDocument()->StudentsLoaded())); }
	afx_msg void OnCountingInformation();
	afx_msg void OnUpdateCountingInformation(CCmdUI* pCmdUI) { pCmdUI->Enable((GetSelectedScanBallot()!=NULL)?(GetSelectedScanBallot()->GetStatus()==COUNTED):false); }
	afx_msg void OnTimeSync() { m_TS.TrasRequest(true); }
	afx_msg void OnTimeAutosync();
	afx_msg void OnUpdateTimeAutosync(CCmdUI* pCmdUI) { pCmdUI->SetCheck(m_AutoSyncTime); }
	afx_msg void OnTimeServer();
	afx_msg void OnSetfocusRacelistAL(NMHDR* pNMHDR, LRESULT* pResult) { m_RaceListSelected=AL; *pResult=0; }
	afx_msg void OnSetfocusRacelistFR(NMHDR* pNMHDR, LRESULT* pResult) { m_RaceListSelected=FR; *pResult=0; }
	afx_msg void OnSetfocusRacelistSO(NMHDR* pNMHDR, LRESULT* pResult) { m_RaceListSelected=SO; *pResult=0; }
	afx_msg void OnSetfocusRacelistJR(NMHDR* pNMHDR, LRESULT* pResult) { m_RaceListSelected=JR; *pResult=0; }
	afx_msg void OnSetfocusRacelistSR(NMHDR* pNMHDR, LRESULT* pResult) { m_RaceListSelected=SR; *pResult=0; }
	afx_msg void OnSetfocusRacelistGR(NMHDR* pNMHDR, LRESULT* pResult) { m_RaceListSelected=GR; *pResult=0; }
	afx_msg void OnSetfocusPrintballotsAL(NMHDR* pNMHDR, LRESULT* pResult) { m_PrintBallotListSelected=AL; *pResult=0; }
	afx_msg void OnSetfocusPrintballotsFR(NMHDR* pNMHDR, LRESULT* pResult) { m_PrintBallotListSelected=FR; *pResult=0; }
	afx_msg void OnSetfocusPrintballotsSO(NMHDR* pNMHDR, LRESULT* pResult) { m_PrintBallotListSelected=SO; *pResult=0; }
	afx_msg void OnSetfocusPrintballotsJR(NMHDR* pNMHDR, LRESULT* pResult) { m_PrintBallotListSelected=JR; *pResult=0; }
	afx_msg void OnSetfocusPrintballotsSR(NMHDR* pNMHDR, LRESULT* pResult) { m_PrintBallotListSelected=SR; *pResult=0; }
	afx_msg void OnSetfocusPrintballotsGR(NMHDR* pNMHDR, LRESULT* pResult) { m_PrintBallotListSelected=GR; *pResult=0; }
	afx_msg void OnDblclkRacelist(NMHDR* pNMHDR, LRESULT* pResult) { OnRacesProperties(); *pResult = 0; }
	afx_msg void OnDblclkPrintBallots(NMHDR* pNMHDR, LRESULT* pResult) { OnPrintingHistory(); *pResult = 0; }
	afx_msg void OnDblclkScanBallots(NMHDR* pNMHDR, LRESULT* pResult) { OnCountingInformation(); *pResult = 0; }
	afx_msg void OnReturn();
	afx_msg void OnColumnclickScanballots(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnColumnclickStudentlist(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnInsertPrintBallot();
	afx_msg void OnUpdateScanBallot();
	DECLARE_MESSAGE_MAP()
private:
	CListCtrl* RaceList(ClassYear year);
	CListCtrl* PrintBallotList(ClassYear year);
	
	void PrintBallotListCols(ClassYear year);
	void RaceListCols(ClassYear year);
	
	CPrintRace* GetSelectedRace();
	CPrintBallot* GetSelectedPrintBallot();
	CScanBallot* GetSelectedScanBallot();
	
	int InsertRace(CPrintRace* pPRace);
	void InsertStudent(CStudent* pStudent);
	void InsertScanBallot(CScanBallot* pSBallot);
	
	void DisplayRaces();
	void DisplayPrintBallots();
	void DisplayStudents();
	void DisplayScanBallots();
	
	void RefreshRaceList(ClassYear year, CPrintRace* focus=NULL);
	void RefreshStudentList();
	void RefreshScanBallotList();
	void RefreshPrintBallotList(ClassYear year);
	
	void SampleBallot(ClassYear year);
	
	static int CALLBACK ScanBallotsCompareFunc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);
	static int CALLBACK StudentListCompareFunc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);
	
	BOOL m_AutoSyncTime;
	CTimeSocket m_TS;
	ClassYear m_RaceListSelected;
	ClassYear m_PrintBallotListSelected;
};

#ifndef _DEBUG  // debug version in ElectSoftView.cpp
inline CElectSoftDoc* CElectSoftView::GetDocument() { return (CElectSoftDoc*)m_pDocument; }
#endif

#endif // !defined(AFX_ELECTSOFTVIEW_H__69E5602C_562F_11D6_B47E_00B0D0CDB4FC__INCLUDED_)