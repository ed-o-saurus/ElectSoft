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
#include "AlignDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CAlignDialog::CAlignDialog(CWnd* pParent) : CDialog(CAlignDialog::IDD, pParent) {}

#ifdef _SIM_BALLOT

void CAlignDialog::DoDataExchange(CDataExchange* pDX)
{
	// in SIM_BALLOT mode, do nothing 
	CDialog::DoDataExchange(pDX);
	m_changed=false;
}

#else

void CAlignDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	
	if(pDX->m_bSaveAndValidate)
		if(m_changed=m_Tpos||m_Rpos||m_Lpos||m_Bpos) // if anything has been moved 
			GET_APP->m_AlignInfo.ChangeParameters(m_Tpos, m_Rpos, m_Lpos, m_Bpos); // recalculate alignment
}

#endif

BEGIN_MESSAGE_MAP(CAlignDialog, CDialog)
	ON_WM_PAINT()
	ON_WM_CREATE()
	ON_WM_TIMER()
END_MESSAGE_MAP()

BOOL CAlignDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	((CSliderCtrl*)GetDlgItem(IDC_SLIDER_T))->SetRange(-240, 240, true); // set slider ranges 
	((CSliderCtrl*)GetDlgItem(IDC_SLIDER_T))->SetPos(0);
	
	((CSliderCtrl*)GetDlgItem(IDC_SLIDER_R))->SetRange(-240, 240, true);
	((CSliderCtrl*)GetDlgItem(IDC_SLIDER_R))->SetPos(0);
	
	((CSliderCtrl*)GetDlgItem(IDC_SLIDER_L))->SetRange(-240, 240, true);
	((CSliderCtrl*)GetDlgItem(IDC_SLIDER_L))->SetPos(0);
	
	((CSliderCtrl*)GetDlgItem(IDC_SLIDER_B))->SetRange(-240, 240, true);
	((CSliderCtrl*)GetDlgItem(IDC_SLIDER_B))->SetPos(0);
	
	m_Tpos=0; m_Rpos=0; m_Lpos=0; m_Bpos=0; // center sliders 
	
	return true;
}

void CAlignDialog::DrawImage()
{
	CWnd* pBox=GetDlgItem(IDC_IMAGE);
	CPaintDC DC(pBox);
	CRect rect;
	pBox->GetClientRect(rect);
	
	int width=rect.Width();
	int height=rect.Height();
	
	// add the four moveable dots 
	AddDot(&DC, &rect, CPoint(width*(240+m_Lpos)/960, height*(240-m_Tpos)/960), CRect(0, 0, width/2, height/2));
	AddDot(&DC, &rect, CPoint(width*(720+m_Rpos)/960, height*(240-m_Tpos)/960), CRect(width/2, 0, width, height/2));
	AddDot(&DC, &rect, CPoint(width*(240+m_Lpos)/960, height*(720-m_Bpos)/960), CRect(0, height/2, width/2, height));
	AddDot(&DC, &rect, CPoint(width*(720+m_Rpos)/960, height*(720-m_Bpos)/960), CRect(width/2, height/2, width, height));
	
	AddCircles(&DC, &rect);	// add the static circles 
	AddGrid(&DC, &rect); // add the grid 
}

int CAlignDialog::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if(CDialog::OnCreate(lpCreateStruct)==(-1))
		return -1;
	
	SetTimer(1, 100, NULL);	// timer causes a refresh ten times a second 
	
	return 0;
}

void CAlignDialog::OnTimer(UINT nIDEvent) 
{
	if(UpdatePos()) // read pos variables 
		RedrawWindow();
	
	CDialog::OnTimer(nIDEvent);
}

BOOL CAlignDialog::UpdatePos()
{
	// read pos variables 
	
	int Tpos=-1*((CSliderCtrl*)GetDlgItem(IDC_SLIDER_T))->GetPos();
	int Rpos=((CSliderCtrl*)GetDlgItem(IDC_SLIDER_R))->GetPos();
	int Lpos=((CSliderCtrl*)GetDlgItem(IDC_SLIDER_L))->GetPos();
	int Bpos=-1*((CSliderCtrl*)GetDlgItem(IDC_SLIDER_B))->GetPos();
	
	if((m_Tpos==Tpos)&&(m_Rpos==Rpos)&&(m_Lpos==Lpos)&&(m_Bpos==Bpos))
		return false;
	
	m_Tpos=Tpos; m_Rpos=Rpos;
	m_Lpos=Lpos; m_Bpos=Bpos;
	return true;
}

CPoint CAlignDialog::Angle(CRect rect, int angle)
{
	// return the point in rect at angle
	
	float f_angle=3.14159F*angle/180;
	return rect.CenterPoint()+CPoint((int)(rect.Width()*cos(f_angle)/2), (int)(rect.Height()*sin(f_angle)/2));
}

CPoint CAlignDialog::PushInto(CPoint point, CRect BoundingRect)
{
	// return the point in BoundingRect closest to point
	
	point.x=min(max(point.x, BoundingRect.left), BoundingRect.right);
	point.y=min(max(point.y, BoundingRect.top), BoundingRect.bottom);
	
	return point;
}

void CAlignDialog::AddDot(CPaintDC* pDC, CRect Rect, CPoint center, CRect BoundingRect)
{
	// draws a gray dot at center 
	
	int i;
	CPoint points[60];
	
	int width=Rect.Width();
	int height=Rect.Height();
	
	CRect eRect(-31*width/320, -31*height/320, 31*width/320, 31*height/320); // the rectangle the same size as the dot 
	CPen* pOldPen=pDC->SelectObject(new CPen(PS_SOLID, 1, RGB(128, 128, 128)));
	CBrush* pOldBrush=pDC->SelectObject(new CBrush(RGB(128, 128, 128)));
	
	for(i=0; i<60; i++)
		points[i]=PushInto(Angle(eRect+center, 6*i), BoundingRect); // points around the dot
	
	pDC->Polygon(points, 60); // draw the dot 
	
	delete pDC->SelectObject(pOldPen);
	delete pDC->SelectObject(pOldBrush);
}

void CAlignDialog::AddCircles(CPaintDC* pDC, CRect Rect)
{
	//adds the static circles in the dialog box
	
	CPen* pOldPen=pDC->SelectObject(new CPen(PS_SOLID, 1, RGB(0, 0, 0)));
	
	int width=Rect.Width();
	int height=Rect.Height();
	
	CPoint A(0, 0);
	CPoint B(width, 0);
	CPoint C(0, height);
	CPoint D(width, height);
	CPoint offsetX, offsetY;
	
	CRect eRect(-31*width/320, -31*height/320, 31*width/320, 31*height/320);
	
	offsetY=CPoint(0, 0);
	offsetX=CPoint(        0, 0); pDC->Arc(eRect+offsetX+offsetY, C, B);
	offsetX=CPoint(  width/4, 0); pDC->Arc(eRect+offsetX+offsetY, A, B);
	offsetX=CPoint(  width/2, 0); pDC->Arc(eRect+offsetX+offsetY, A, B);
	offsetX=CPoint(3*width/4, 0); pDC->Arc(eRect+offsetX+offsetY, A, B);
	offsetX=CPoint(  width  , 0); pDC->Arc(eRect+offsetX+offsetY, A, D);
	
	offsetY=CPoint(0, height/4);
	offsetX=CPoint(        0, 0); pDC->Arc(eRect+offsetX+offsetY, C, A);
	offsetX=CPoint(  width/4, 0); pDC->Arc(eRect+offsetX+offsetY, A, A);
	offsetX=CPoint(  width/2, 0); pDC->Arc(eRect+offsetX+offsetY, A, A);
	offsetX=CPoint(3*width/4, 0); pDC->Arc(eRect+offsetX+offsetY, A, A);
	offsetX=CPoint(  width  , 0); pDC->Arc(eRect+offsetX+offsetY, B, D);
	
	offsetY=CPoint(0, height/2);
	offsetX=CPoint(        0, 0); pDC->Arc(eRect+offsetX+offsetY, C, A);
	offsetX=CPoint(  width/4, 0); pDC->Arc(eRect+offsetX+offsetY, A, A);
	offsetX=CPoint(  width/2, 0); pDC->Arc(eRect+offsetX+offsetY, A, A);
	offsetX=CPoint(3*width/4, 0); pDC->Arc(eRect+offsetX+offsetY, A, A);
	offsetX=CPoint(  width  , 0); pDC->Arc(eRect+offsetX+offsetY, B, D);
	
	offsetY=CPoint(0, 3*height/4);
	offsetX=CPoint(        0, 0); pDC->Arc(eRect+offsetX+offsetY, C, A);
	offsetX=CPoint(  width/4, 0); pDC->Arc(eRect+offsetX+offsetY, A, A);
	offsetX=CPoint(  width/2, 0); pDC->Arc(eRect+offsetX+offsetY, A, A);
	offsetX=CPoint(3*width/4, 0); pDC->Arc(eRect+offsetX+offsetY, A, A);
	offsetX=CPoint(  width  , 0); pDC->Arc(eRect+offsetX+offsetY, B, D);
	
	offsetY=CPoint(0, height);
	offsetX=CPoint(        0, 0); pDC->Arc(eRect+offsetX+offsetY, D, A);
	offsetX=CPoint(  width/4, 0); pDC->Arc(eRect+offsetX+offsetY, D, C);
	offsetX=CPoint(  width/2, 0); pDC->Arc(eRect+offsetX+offsetY, D, C);
	offsetX=CPoint(3*width/4, 0); pDC->Arc(eRect+offsetX+offsetY, D, C);
	offsetX=CPoint(  width  , 0); pDC->Arc(eRect+offsetX+offsetY, B, C);
	
	delete pDC->SelectObject(pOldPen);
}

void CAlignDialog::AddGrid(CPaintDC* pDC, CRect Rect)
{
	//add the grid to the dialog box
	
	CPen* pOldPen=pDC->SelectObject(new CPen(PS_SOLID, 2, RGB(0, 0, 0)));
	
	int width=Rect.Width();
	int height=Rect.Height();
	
	pDC->MoveTo(CPoint(0, 0));
	pDC->LineTo(CPoint(width, 0));
	pDC->LineTo(CPoint(width, height));
	pDC->LineTo(CPoint(0, height));
	pDC->LineTo(CPoint(0, 0));
	
	pDC->MoveTo(CPoint(0, height/2)); pDC->LineTo(CPoint(width, height/2));
	pDC->MoveTo(CPoint(width/2,  0)); pDC->LineTo(CPoint(width/2, height));
	
	delete pDC->SelectObject(pOldPen);
}