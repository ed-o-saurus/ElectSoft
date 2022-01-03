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


#if !defined(AFX_PRINTBALLOT_H__17759280_F7FF_11D5_B47E_00B0D0CDB4FC__INCLUDED_)
#define AFX_PRINTBALLOT_H__17759280_F7FF_11D5_B47E_00B0D0CDB4FC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CPrintBallot : public CObject
{
DECLARE_SERIAL(CPrintBallot)
public:
	class CEvent
	{
	// This class stores a single event in a ballot's history.  
	public:
		CEvent() {};
		CEvent(BallotStatus status);
		void GetTimeType(CTime& time, BallotStatus& status) { time=m_time; status=m_status; }
	private:
		BallotStatus m_status;  //The type of event 
		CTime m_time; //The time the event occured 
	};
	CString SerialString();
	void AddEvent(CEvent event) { m_EventList.AddTail(event); }
	ClassYear GetYear() { return m_year; }
	POSITION GetHeadEventPosition() { return m_EventList.GetHeadPosition(); }
	CEvent GetNextEvent(POSITION& pos) { return m_EventList.GetNext(pos); }
	void AddEvent(BallotStatus status, CElectSoftDoc* pDoc);
	CPrintBallot(ClassYear year, CElectSoftDoc* pDoc);
	CPrintBallot(ClassYear year, int number) { m_year=year; m_number=number; }
	CPrintBallot() {};
	virtual void Serialize(CArchive &ar);
private:
	int m_number;
	ClassYear m_year;
	CList<CEvent, CEvent> m_EventList;
};

#endif // !defined(AFX_PRINTBALLOT_H__17759280_F7FF_11D5_B47E_00B0D0CDB4FC__INCLUDED_)