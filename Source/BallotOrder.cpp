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
#include "BallotOrder.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#endif

CBallotOrder::CBallotOrder(CWnd* pParent) : CDialog(CBallotOrder::IDD, pParent)
{ m_year=AL; m_size=100; m_AlignmentRate=50; }

void CBallotOrder::DoDataExchange(CDataExchange* pDX)
{
	int year=-1;
	
	CDialog::DoDataExchange(pDX);
	
	if(!pDX->m_bSaveAndValidate)
		switch(m_year)
		{
		case AL: year=0; break;
		case FR: year=1; break;
		case SO: year=2; break;
		case JR: year=3; break;
		case SR: year=4; break;
		case GR: year=5; break;
		default: year=-1; 
		}
	
	DDX_Radio(pDX, IDC_AL, year);
	DDX_Text(pDX, IDC_ORDER, m_size);
	DDX_Text(pDX, IDC_AR, m_AlignmentRate);
	
	if(!pDX->m_bSaveAndValidate)
		return;
	
	if(year==(-1))
	{
		MessageBox("You must select a class year", NULL, MB_ICONSTOP);
		pDX->Fail();
	}
	
	switch(year)
	{
	case 0: m_year=AL; break;
	case 1: m_year=FR; break;
	case 2: m_year=SO; break;
	case 3: m_year=JR; break;
	case 4: m_year=SR; break;
	case 5: m_year=GR; break;
	default:
		MessageBox("You must select a year", NULL, MB_ICONSTOP);
		pDX->Fail();
	}
	
	if((m_size<1)||(m_size>65535))
	{
		MessageBox("Invaid Order Size", NULL, MB_ICONSTOP);
		pDX->Fail();
	}
	
	if((m_AlignmentRate<1)||(m_AlignmentRate>1000))
	{
		MessageBox("Invalid Alignment Rate", NULL, MB_ICONSTOP);
		pDX->Fail();
	}
}

BOOL CBallotOrder::OnInitDialog() 
{
	if(!CDialog::OnInitDialog())
		return false;
	
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN_AR))->SetRange32(1, 1000);
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN_ORDER))->SetRange32(1, 65535);
	
	return true; 
}