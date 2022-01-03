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
#include "PrintBallot.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

IMPLEMENT_SERIAL(CPrintBallot, CObject, 0)

CPrintBallot::CPrintBallot(ClassYear year, CElectSoftDoc* pDoc)
{
	m_number=pDoc->GetBallotCount(m_year=year);
}

void CPrintBallot::Serialize(CArchive &ar)
{
	CObject::Serialize(ar);
	
	if(ar.IsStoring())
		ar << m_number << m_year;
	else
		ar >> m_number >> m_year;
	
	m_EventList.Serialize(ar);
}

void CPrintBallot::AddEvent(BallotStatus status, CElectSoftDoc* pDoc)
{
	CEvent event;
	m_EventList.AddTail(event=CEvent(status));
	pDoc->SetModifiedFlag();
}

CString CPrintBallot::SerialString()
{
	CString SS;
	
	switch(m_year)
	{
	case AL: SS.Format("AL.%05d", m_number+1); break;
	case FR: SS.Format("FR.%05d", m_number+1); break;
	case SO: SS.Format("SO.%05d", m_number+1); break;
	case JR: SS.Format("JR.%05d", m_number+1); break;
	case SR: SS.Format("SR.%05d", m_number+1); break;
	case GR: SS.Format("GR.%05d", m_number+1); break;
	}
	
	return SS;
}

CPrintBallot::CEvent::CEvent(BallotStatus status)
{
	m_status=status;
	m_time=CTime::GetCurrentTime();
}