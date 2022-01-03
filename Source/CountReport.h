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


#if !defined(AFX_COUNTREPORT_H__EFA41140_A326_11D6_B481_00B0D0CDB4FC__INCLUDED_)
#define AFX_COUNTREPORT_H__EFA41140_A326_11D6_B481_00B0D0CDB4FC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CCountReport
{
public:
	void WriteReport(CElectSoftDoc* pDoc, CStdioFile* pSF);
private:
	void AddVoter(CScanBallot* pSBallot);
	void AddUpVoters();
	void AddRepeatVotersToReport();
	void AddOutstandingBallotsToReport();
	void PrintRaces();
	void AddStatusCounts();
	void AddBallots(CElectSoftDoc* pDoc);
	static void SortList(CStringList* pList);
	CArray<CUIntArray*, CUIntArray*>* RaceArray(ClassYear year);
	void DeleteRaces(ClassYear year);
	struct ballot_types
	{
	public:
		ballot_types() { m_Outstanding=0; m_Counted=0; m_Lost_Destroyed=0; m_Voided=0; }
		void IncrementCount(BallotStatus status);
		CString StatusCount();
	private:
		UINT m_Outstanding, m_Counted, m_Lost_Destroyed, m_Voided;
	};
	
	void AddOutstandingBallotToReport(ClassYear year);
	void AddSeperator() { AddLine("---+------------------+------------------+------------------+------------------+"); }
	ballot_types* GetBallotTypes(ClassYear year);
	void AddRace(ClassYear year, int position, CByteList* pCodeList, CStudent* pStudent);
	void AddBallot(ClassYear year, int number, CElectSoftDoc* pDoc);
	void SetUpRaces(ClassYear year);
	void PrintRace(ClassYear year, int position);
	void AddLine(CString text) { m_pSF->WriteString(text+"\n"); }
	void AddLine() { AddLine(""); }
	
	CCount* m_pCount;
	CStdioFile* m_pSF;
	
	struct ballot_types m_types_AL, m_types_FR, m_types_SO, m_types_JR, m_types_SR, m_types_GR;	
	CArray<CUIntArray*, CUIntArray*> m_races_AL, m_races_FR, m_races_SO, m_races_JR, m_races_SR, m_races_GR;
	
	CMap<CString, CString, UINT, UINT> m_voters;
};

#endif // !defined(AFX_COUNTREPORT_H__EFA41140_A326_11D6_B481_00B0D0CDB4FC__INCLUDED_)