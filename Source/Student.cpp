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
#include "Student.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CStudent::CStudent(CString string, BOOL& eligible, BOOL& valid)
{
	//reads student info from string
	
	valid=false;
	eligible=true;
	
	if(string.GetLength()<=14)
		return;
	
	m_RIN=string.Left(9); // get the RIN 
	for(int i=0; i<9; i++) // verify the RIN is valid 
		if(!isdigit(m_RIN[i]))
			return;
	
	if((string.Mid(9, 2)=="NE")||(string.Mid(11, 2)=="NE")) // if the student is ineligable to vote
	{
		valid=true;
		eligible=false;
		return;
	}
	
	if(!ReadYearCode(string.Mid( 9, 2), m_year1)) // get the years 
		return;
	
	if(!ReadYearCode(string.Mid(11, 2), m_year2))
		return;
	
	switch(string[13]) // get the affiliation 
	{
	case 'G': m_aff=GREEK; break;
	case 'I': m_aff=INDEPENDENT; break;
	default: return;
	}
	
	if(m_year2<m_year1) // put the years in the proper order
	{
		ClassYear buffer=m_year1;
		m_year1=m_year2;
		m_year2=buffer;
	}
	
	m_name=string.Mid(14); m_name.TrimLeft(); // get the student's name 
	
	if(m_name.IsEmpty())
		return;
	
	m_name.FreeExtra();
	m_RIN.FreeExtra();
	
	valid=true;
}

CString CStudent::YearString()
{
	// return a string sutible for display 
	
	CString string;
	
	switch(m_year1)
	{
	case FR: string="Freshmen";  break;
	case SO: string="Sophomore"; break;
	case JR: string="Junior";    break;
	case SR: string="Senior";    break;
	case GR: string="Graduate";  break;
	}
	
	if(m_year1==m_year2)
		return string;
	
	switch(m_year2)
	{
	case FR: return string+", Freshmen";   break;
	case SO: return string+", Sophomore";  break;
	case JR: return string+", Junior";     break;
	case SR: return string+", Senior";     break;
	case GR: return string+", Graduate";   break;
	default: ASSERT(false); return "";
	}
}

BOOL CStudent::ReadYearCode(CString code, ClassYear &year)
{
	if(code=="FR") { year=FR; return true; }
	if(code=="SO") { year=SO; return true; }
	if(code=="JR") { year=JR; return true; }
	if(code=="SR") { year=SR; return true; }
	if(code=="GR") { year=GR; return true; }
	
	return false;
}