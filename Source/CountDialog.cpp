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
#include "CountDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CCountDialog::CCountDialog(CWnd* pParent) : CDialog(CCountDialog::IDD, pParent) { m_pCount=NULL; }

void CCountDialog::DoDataExchange(CDataExchange* pDX)
{
	CString title;
	CDialog::DoDataExchange(pDX);
	
	title=m_pCount->GetTitle();
	
	DDX_Text(pDX, IDC_TITLE, title);
	
	if(!pDX->m_bSaveAndValidate)
		return;
	
	if(title.IsEmpty())
	{
		MessageBox("You must enter a title", NULL, MB_ICONSTOP);
		pDX->Fail();
	}
	
	m_pCount->SetTitle(title);
}