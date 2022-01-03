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


#if !defined(AFX_PRINTRACE_H__BE37A0E0_56BE_11D6_B47E_00B0D0CDB4FC__INCLUDED_)
#define AFX_PRINTRACE_H__BE37A0E0_56BE_11D6_B47E_00B0D0CDB4FC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Group.h"

class CPrintRace : public CObject
{
DECLARE_SERIAL(CPrintRace)
public:
	POSITION DescriptionStartPosition() { return m_description.GetHeadPosition(); }
	CString GetNextDecsriptionLine(POSITION& pos) { return m_description.GetNext(pos); }
	int GetDescriptionLength() { return m_description.GetCount(); }
	CPrintRace() {}
	CPrintRace(CString string, BOOL& valid);
	~CPrintRace();
	CString GetName() { return m_name; }
	CString GetCaption() { return m_caption; }
	ClassYear GetYear() { return m_year; }
	Affiliation GetAff() { return m_aff; }
	UINT GetMaxVotes() { return m_MaxVotes; }
	BOOL SetPosition(UINT col, UINT row);
	void GetLocation(UINT &col, UINT &row) { col=m_col; row=m_row; }
	int GroupCount() { return m_groups.GetCount(); }
	POSITION GetHeadGroupPosition() { return m_groups.GetHeadPosition(); }
	CGroup* GetNextGroup(POSITION& pos) { return (CGroup*)m_groups.GetNext(pos); } 
	UINT Size();
	virtual void Serialize(CArchive &ar);
private:
	void SplitString(CString string, CStringList& list, char sp);
	BOOL ReadYearCode(CString code, ClassYear& year);
	CObList m_groups; // The groups that compose the race
	UINT m_col, m_row; // The physical location of the first line of the race on the ballot
	ClassYear m_year; // The year of the eligible voters 
	Affiliation m_aff;   // The affiliation of the eligible voters 
	CString m_name, m_caption; // The name and caption of the race 
	UINT m_MaxVotes;  // The most votes that are allowed in this race 
	CStringList m_description;
};

#endif // !defined(AFX_PRINTRACE_H__BE37A0E0_56BE_11D6_B47E_00B0D0CDB4FC__INCLUDED_)