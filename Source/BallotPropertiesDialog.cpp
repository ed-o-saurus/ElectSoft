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
#include "BallotPropertiesDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CBallotPropertiesDialog::CBallotPropertiesDialog(CWnd* pParent) : CDialog(CBallotPropertiesDialog::IDD, pParent) {}

void CBallotPropertiesDialog::DoDataExchange(CDataExchange* pDX)
{
	//sets document title and class years 
	
	CString title;
	UINT curr_year;
	UINT FR_year, SO_year, JR_year, SR_year;
	
	CDialog::DoDataExchange(pDX);
	
	if(!pDX->m_bSaveAndValidate)
	{		
		title=m_pDoc->GetTitle();
		curr_year=m_pDoc->GetCurrYear();
		FR_year=m_pDoc->GetClassYear(FR);
		SO_year=m_pDoc->GetClassYear(SO);
		JR_year=m_pDoc->GetClassYear(JR);
		SR_year=m_pDoc->GetClassYear(SR);
	}
	
	DDX_Text(pDX, IDC_TITLE, title);
	DDX_Text(pDX, IDC_CURR_YEAR, curr_year);
	DDX_Text(pDX, IDC_FR_YEAR, FR_year);
	DDX_Text(pDX, IDC_SO_YEAR, SO_year);
	DDX_Text(pDX, IDC_JR_YEAR, JR_year);
	DDX_Text(pDX, IDC_SR_YEAR, SR_year);
	
	if(!pDX->m_bSaveAndValidate)
		return;
	
	if(title.IsEmpty())
	{
		MessageBox("You must enter a title", NULL, MB_ICONSTOP);
		pDX->Fail();
	}
	
	if(m_pDoc->GetTitle()!=title)
		m_pDoc->SetTitle(title);
	
	if(m_pDoc->GetCurrYear()!=curr_year)
		m_pDoc->SetCurrYear(curr_year);
	
	if(m_pDoc->GetClassYear(FR)!=FR_year)
		m_pDoc->SetClassYear(FR, FR_year);
	
	if(m_pDoc->GetClassYear(SO)!=SO_year)
		m_pDoc->SetClassYear(SO, SO_year);
	
	if(m_pDoc->GetClassYear(JR)!=JR_year)
		m_pDoc->SetClassYear(JR, JR_year);
	
	if(m_pDoc->GetClassYear(SR)!=SR_year)
		m_pDoc->SetClassYear(SR, SR_year);	
}