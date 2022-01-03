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
#include "PrinterInterface.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CPrinterInterface::CPrinterInterface()
{
	m_patterns[ 0]=0x1f; m_patterns[16]=0x03;
	m_patterns[ 1]=0x1c; m_patterns[17]=0x18;
	m_patterns[ 2]=0x07; m_patterns[18]=0x05;
	m_patterns[ 3]=0x1a; m_patterns[19]=0x12;
	m_patterns[ 4]=0x0d; m_patterns[20]=0x0c;
	m_patterns[ 5]=0x13; m_patterns[21]=0x11;
	m_patterns[ 6]=0x0e; m_patterns[22]=0x0a;
	m_patterns[ 7]=0x15; m_patterns[23]=0x09;
	m_patterns[ 8]=0x16; m_patterns[24]=0x14;
	m_patterns[ 9]=0x0b; m_patterns[25]=0x06;
	m_patterns[10]=0x19; m_patterns[26]=0x0f;
	m_patterns[11]=0x10; m_patterns[27]=0x17;
	m_patterns[12]=0x08; m_patterns[28]=0x1b;
	m_patterns[13]=0x04; m_patterns[29]=0x1d;
	m_patterns[14]=0x02; m_patterns[30]=0x1e;
	m_patterns[15]=0x01; m_patterns[31]=0x00;
}

#ifdef _SIM_BALLOT

BOOL CPrinterInterface::Print(ClassYear year, CElectSoftDoc* pDoc, BOOL Sample)
{
	CString FileName, line;
	int x, y;
	
	for(x=0; x<48; x++)  // fill the sheet with spaces 
		for(y=0; y<63; y++)
			m_sheet[x][y]=' ';
	
	for(y=2; y<50; y++) // add places for votes 
		m_sheet[2][y]=m_sheet[20][y]='O';
	
	for(x=38; x<47; x++) // add an area for RIN 
		for(y=51; y<61; y++)
			m_sheet[x][y]=60-y+'0';
	
	PlotInfo(Sample, year, pDoc); // add info 
	
	if(Sample) // save the image
		FileName.Format("c:\\ballots\\%s_sample.txt", WriteYearCode(year));
	else
		FileName.Format("c:\\ballots\\%s_%05d.txt", WriteYearCode(year), pDoc->GetBallotCount(year)+1);
	
	CStdioFile SF(FileName, CFile::modeWrite|CFile::modeCreate|CFile::typeText);
	
	for(y=62; y>(-1); y--)
	{
		line.Empty();
		for(x=0; x<48; x++)
			line+=m_sheet[x][y];
		
		line+='\n';
		
		SF.WriteString(line);
	}
	
	SF.Close();
	return true;
}

void CPrinterInterface::AddSerial(ClassYear year, int number, BOOL Sample, CElectSoftDoc* pDoc)
{
	// Add the serial number to the ballot 
	
	BYTE cs;
	if(Sample)
		return;
	
	CString string;
	
	switch(year) // encode the year 
	{
	case AL: AddDot(12,0); AddDot(13,0); break;
	case FR: AddDot(11,0); AddDot(14,0); break;
	case SO: AddDot(11,0); AddDot(13,0); break;
	case JR: AddDot(13,0); AddDot(14,0); break;
	case SR: AddDot(11,0); AddDot(12,0); break;
	case GR: AddDot(12,0); AddDot(14,0); break;
	}
	
	string.Format("%s.%05d", WriteYearCode(year), number+1);  // add the text of the serial number 
	
	for(int pos=0; pos<8; pos++)
		m_sheet[pos][0]=string[pos];
	
	for(int bit=0; bit<16; bit++)  // add the number (bit by bit)
		if((1<<bit)&number) 
			AddDot(15+bit, 0);
	
	cs=(number>>12)^(number>>8)^(number>>4)^(number); // calculate the check sum
	
	// add the checksum
	if(!(cs&0x01))
		AddDot(39, 49);
	
	if(!(cs&0x02))
		AddDot(41, 49);
	
	if(!(cs&0x04))
		AddDot(44, 49);
	
	if(!(cs&0x08))
		AddDot(46, 49);
}

BOOL CPrinterInterface::PrintAlignment() { return true; }

void CPrinterInterface::AddLine(UINT col, UINT row, CString text, BOOL bold)
{
	// add a line of text at (col, row)
	
	while(text.GetLength()<17)
		text+=' ';
	
	for(int i=0; i<17; i++)
		m_sheet[(col?21:3)+i][49-row]=text[i];
}

void CPrinterInterface::AddSeperator(UINT col, UINT row)
{
	// add a seperator at (col, row)
	
	for(int x=col?21:3; x<(col?38:20); x++)
		m_sheet[x][49-row]='-';
}

void CPrinterInterface::AddDot(int x, int y) { m_sheet[x][y]='*'; }
void CPrinterInterface::BallotVoid() {}
void CPrinterInterface::AddHeading(ClassYear year, CElectSoftDoc* pDoc) {}
BOOL CPrinterInterface::PrintQueue(DWORD& cJobs) { cJobs=0; return true; }
BOOL CPrinterInterface::CheckPrinterConfig() { return true; }

void CPrinterInterface::Arrow(UINT col, UINT row, CString candidate) // add a line of text with an arrow 
{ AddLine(col, row, candidate.IsEmpty()?"<-Write-In_______":"<-"+candidate, false); }

#else

BOOL CPrinterInterface::Print(ClassYear year, CElectSoftDoc* pDoc, BOOL Sample)
{
	//print a ballot 
	
	CDC DC;
	CString DocName;
	CPrintDialog PD(false, PD_RETURNDEFAULT); // get info for default printer 
	PD.DoModal();
	
	if(!DC.Attach(PD.GetPrinterDC())) // use the default printer
	{
		DeleteDC(DC.Detach());
		return false;
	}
	
	m_pDC=&DC;
	SetUpDC(); // configure the geometry of the device context
	
	if(Sample)  // set the document name as it appears in the queue
		switch(year)
		{
		case AL: DocName="Sample All Ballot";       break;
		case FR: DocName="Sample Freshmen Ballot";  break;
		case SO: DocName="Sample Sophomore Ballot"; break;
		case JR: DocName="Sample Junior Ballot";    break;
		case SR: DocName="Sample Senior Ballot";    break;
		case GR: DocName="Sample Graduate Ballot";  break;
		}
	else
		DocName.Format("%s.%05d", WriteYearCode(year), pDoc->GetBallotCount(year)+1);
	
	if(DC.StartDoc(DocName)<0) // initiate the document 
	{
		DC.AbortDoc();
		DeleteDC(DC.Detach());
		return false;
	}
	
	if(DC.StartPage()<0) // always start with a new page 
	{
		DC.AbortDoc();
		DeleteDC(DC.Detach());
		return false;
	}
	
	DC.SetTextColor(RGB(0, 0, 0)); // black text 
	PlotInfo(Sample, year, pDoc); // add everything to the page 
	
	if(DC.EndPage()<0) // finish the page 
	{
		DC.AbortDoc();
		DeleteDC(DC.Detach());
		return false;
	}
	
	if(DC.EndDoc()<0) // finish the document
	{
		DC.AbortDoc();
		DeleteDC(DC.Detach());
		return false;
	}
	
	DeleteDC(DC.Detach()); // clean up 
	return true;
}

void CPrinterInterface::AddHeading(ClassYear year, CElectSoftDoc* pDoc)
{
	// adds the info to the top of the ballot 
	
	CFont* Large=new CFont;
	Large->CreateFont(360, 0, 0, 0, FW_BOLD, false, false, false, ANSI_CHARSET, 
		OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, FF_ROMAN, "Times New Roman");
	
	CFont* OldFont=m_pDC->SelectObject(Large);
	
	CString line1, line2;
	
	switch(year)
	{
	case AL: line1="ALL CLASSES"; break;
	case GR: line1="GRADUATE"; break;
	default: line1.Format("CLASS OF %d", pDoc->GetClassYear(year));
	}
	
	line2.Format("%s %d", pDoc->GetTitle(), pDoc->GetCurrYear());
	
	TextOut(2, 60,   line1); TextOut(19, 60,   "Student Government");
	TextOut(2, 58.5, line2); TextOut(21, 58.5, "Election Ballot");
	
	delete m_pDC->SelectObject(OldFont);
}

void CPrinterInterface::AddSerial(ClassYear year, int number, BOOL Sample, CElectSoftDoc* pDoc)
{
	// add the serial number to the ballot
	
	BYTE cs;
	CString name;
	CString SS;
	CFont* Serial=new CFont;
	Serial->CreateFont(200, 0, 0, 0, FW_NORMAL, false, false, false, ANSI_CHARSET, 
		OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, FF_ROMAN, "Courier New");
	
	CFont* OldFont=m_pDC->SelectObject(Serial);
	
	name.Format("%d %s", pDoc->GetCurrYear(), pDoc->GetTitle()); // identify the main document
	TextOut(1.0F, 0.4F, name);
	
	if(Sample)
	{
		// sample ballots don't have serial numbers 
		
		TextOut(1.0F, -0.4F, "Serial : "+WriteYearCode(year)+".XXXXX");
		delete m_pDC->SelectObject(OldFont);
		return;
	}
	
	switch(year) // indicate the year for scanning
	{
	case AL: AddDot(12, 0); AddDot(13, 0); break;
	case FR: AddDot(11, 0); AddDot(14, 0); break;
	case SO: AddDot(11, 0); AddDot(13, 0); break;
	case JR: AddDot(13, 0); AddDot(14, 0); break;
	case SR: AddDot(11, 0); AddDot(12, 0); break;
	case GR: AddDot(12, 0); AddDot(14, 0); break;
	}
	
	SS.Format("Serial : %s.%05d", WriteYearCode(year), number+1); // print the serial number 
	TextOut(1.0F, -0.4F, SS);
	
	for(int bit=0; bit<16; bit++) // add the number section for scanning 
		if((1<<bit)&number) 
			AddDot(15+bit, 0);
	
	cs=(number>>12)^(number>>8)^(number>>4)^(number); //check sum
	
	if(!(cs&0x01))
		AddDot(39, 49);
	
	if(!(cs&0x02))
		AddDot(41, 49);
	
	if(!(cs&0x04))
		AddDot(44, 49);
	
	if(!(cs&0x08))
		AddDot(46, 49);
	
	delete m_pDC->SelectObject(OldFont);
}

void CPrinterInterface::BallotVoid()
{
	// Add the VOID marks to the ballot 
	
	CFont* WM=new CFont;
	WM->CreateFont(810, 0, -450, -450, FW_BOLD, false, false, false, ANSI_CHARSET, 
		OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS|CLIP_LH_ANGLES, PROOF_QUALITY, FF_ROMAN, "Arial");
	
	CFont* OldFont=m_pDC->SelectObject(WM);
	m_pDC->SetTextColor(RGB(WATER_MARK, WATER_MARK, WATER_MARK));
	
	for(float y=-50; y<63; y+=4)
		TextOut(0.0F, y, "ID VOID VOID VOID VOID VOID VOID VOID VOID VO");
	
	delete m_pDC->SelectObject(OldFont);
	m_pDC->SetTextColor(RGB(0, 0, 0));
}

BOOL CPrinterInterface::TextOut(float x, float y, CString string)
{
	// add text to the ballot
	
	CPoint pos=GET_APP->m_AlignInfo.translate(x, y);
	return m_pDC->TextOut(pos.x, pos.y, string); 
}

void CPrinterInterface::AddAlignment()
{
	// adds four dots used for printer alignment
	
	CFont* Large=new CFont;
	Large->CreateFont(360, 0, 0, 0, FW_BOLD, false, false, false, ANSI_CHARSET, 
		OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, FF_ROMAN, "Times New Roman");
	
	CFont* OldFont=m_pDC->SelectObject(Large);
	
	TextOut(21, 58.5, "Alignment Form");
	AddDot(2, 49); AddDot(47, 49);
	AddDot(2,  2); AddDot(47,  2);
	
	delete m_pDC->SelectObject(OldFont);
}

BOOL CPrinterInterface::PrintAlignment()
{
	//print an alignment ballot
	//same structure as PrintBallot method
	
	CDC DC;
	CPrintDialog PD(false, PD_RETURNDEFAULT);
	PD.DoModal();
	
	if(!DC.Attach(PD.GetPrinterDC()))
	{
		DeleteDC(DC.Detach());
		return false;
	}
	
	m_pDC=&DC;
	SetUpDC();
	
	if(DC.StartDoc("Alignment Test")<0)
	{
		DC.AbortDoc();
		DeleteDC(DC.Detach());
		return false;
	}
	
	if(DC.StartPage()<0)
	{
		DC.AbortDoc();
		DeleteDC(DC.Detach());
		return false;
	}
	
	DC.SetTextColor(RGB(0, 0, 0));
	AddAlignment();
	
	if(DC.EndPage()<0)
	{
		DC.AbortDoc();
		DeleteDC(DC.Detach());
		return false;
	}
	
	if(DC.EndDoc()<0)
	{
		DC.AbortDoc();
		DeleteDC(DC.Detach());
		return false;
	}
	
	DeleteDC(DC.Detach());
	return true;
}

void CPrinterInterface::SetUpDC()
{
	//places the origin at the lower left and sets the map mode to TWIP
	
	POINT PrintingOffset;
	
	m_pDC->Escape(GETPRINTINGOFFSET, 0, NULL, &PrintingOffset);
	m_pDC->SetMapMode(MM_TWIPS);
	m_pDC->SetTextAlign(TA_LEFT|TA_BOTTOM);
	m_pDC->SetBkMode(TRANSPARENT);
	m_pDC->DPtoLP(&PrintingOffset);
	m_pDC->SetWindowOrg(CPoint(0, 15840)+PrintingOffset);
}

void CPrinterInterface::AddLine(UINT col, UINT row, CString text, BOOL bold)
{
	// adds a line of text at (col, row)
	
	CFont* pFont=new CFont;
	pFont->CreateFont(bold?240:200, 0, 0, 0, bold?FW_BOLD:FW_NORMAL, false, false, false, 
		ANSI_CHARSET, OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, FF_ROMAN, 
		"Times New Roman");
	
	CFont* OldFont=m_pDC->SelectObject(pFont);
	TextOut(col?20.55F:2.55F, (bold?48.5F:48.58F)-row, text);
	delete m_pDC->SelectObject(OldFont);	
}

void CPrinterInterface::AddSeperator(UINT col, UINT row)
{
	// adds a seperator at (col, row)
	
	CPen* pOldPen=m_pDC->SelectObject(new CPen(PS_SOLID, 20, RGB(0, 0, 0)));
	m_pDC->MoveTo(GET_APP->m_AlignInfo.translate(col?20.5F:2.5F,  49.0F-row));
	m_pDC->LineTo(GET_APP->m_AlignInfo.translate(col?37.5F:19.5F, 49.0F-row));
	delete m_pDC->SelectObject(pOldPen);
}

void CPrinterInterface::AddDot(int x, int y)
{
	// adds a dot at (x, y)
	
	CPen* pOldPen=m_pDC->SelectObject(new CPen(PS_SOLID, 1, RGB(0, 0, 0)));
	CBrush* OldBrush=m_pDC->SelectObject(new CBrush(RGB(0, 0, 0)));
	m_pDC->Ellipse(CRect(-94, -94, 94, 94)+GET_APP->m_AlignInfo.translate((float)x, (float)y));
	delete m_pDC->SelectObject(OldBrush);
	delete m_pDC->SelectObject(pOldPen);
}

BOOL CPrinterInterface::PrintQueue(DWORD& cJobs)
{
	// checks the number of jobs in the print queue of the default printer 
	
	HANDLE hPrinter;
	LPBYTE pPrinter;
	DWORD cbNeeded, cbBuf=1;
	
	CPrintDialog PD(false, PD_RETURNDEFAULT);
	PD.DoModal();
	
	if(!OpenPrinter(PD.GetDeviceName().GetBuffer(0), &hPrinter, NULL))
		return false;
	
	DeleteDC(PD.GetPrinterDC());
	
	while(!GetPrinter(hPrinter, 2, pPrinter=new BYTE[cbBuf], cbBuf, &cbNeeded))
	{
		delete [] pPrinter;
		
		if(cbNeeded<=cbBuf)
			return false;
		
		cbBuf*=2;
	}
	
	cJobs=((PRINTER_INFO_2*)pPrinter)->cJobs;
	delete [] pPrinter; 
	
	return ClosePrinter(hPrinter);
}

BOOL CPrinterInterface::CheckPrinterConfig()
{
	// verifies that the default printer prints pages that are 8 1/2 x 11 inches 
	
	POINT PhysPageSize;
	CDC DC;
	CPrintDialog PD(false, PD_RETURNDEFAULT);
	PD.DoModal();
	
	if(!DC.Attach(PD.GetPrinterDC()))
	{
		DeleteDC(DC.Detach());
		return true;
	}
	
	try
	{		
		DC.Escape(GETPHYSPAGESIZE, 0, NULL, &PhysPageSize);
	}
	catch(CException*)
	{
		DeleteDC(DC.Detach());
		return true;
	}
	
	DC.SetMapMode(MM_TWIPS);	
	DC.DPtoLP(&PhysPageSize);
	
	DeleteDC(DC.Detach());
	return((PhysPageSize.x==12240)&&(PhysPageSize.y==(-15840)));
}

void CPrinterInterface::Arrow(UINT col, UINT row, CString candidate)
{
	// adds a line of text at (row, col) with an arrow prceeding
	
	CPoint points[7], tip=GET_APP->m_AlignInfo.translate(col?20.0F:2.0F, 49.0F-row)+CPoint(150, 0);
	points[0]=tip+CPoint(200,  10);
	points[1]=tip+CPoint(100,  10);
	points[2]=tip+CPoint(100,  40);
	points[3]=tip;
	points[4]=tip+CPoint(100, -40);
	points[5]=tip+CPoint(100, -10);
	points[6]=tip+CPoint(200, -10);
	
	CBrush* OldBrush=m_pDC->SelectObject(new CBrush(RGB(0, 0, 0)));	
	m_pDC->Polygon(points, 7);
	delete m_pDC->SelectObject(OldBrush);
	
	CFont* pFont=new CFont;
	pFont->CreateFont(200, 0, 0, 0, FW_NORMAL, false, false, false, 
		ANSI_CHARSET, OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, FF_ROMAN, 
		"Times New Roman");
	
	CFont* OldFont=m_pDC->SelectObject(pFont);
	TextOut((col?20.55F:2.55F)+1.0F, 48.58F-row, candidate.IsEmpty()?"Write-In: ________________________________":candidate);
	delete m_pDC->SelectObject(OldFont);
}

#endif

void CPrinterInterface::PlotInfo(BOOL Sample, ClassYear year, CElectSoftDoc* pDoc)
{
	// adds all the needed info to the ballot  
	
	int position;
	
	if(Sample)
		BallotVoid(); // add void markes if needed
	
	AddSerial(year, pDoc->GetBallotCount(year), Sample, pDoc); // adds the serial number 
	AddHeading(year, pDoc); // adds the header 
	
	for(position=0; position<pDoc->RaceCount(AL); position++)  // for each general race 
		AddRace(pDoc->GetRaceAt(AL, position), Sample);
	
	if(year==AL) 
		return;
	
	for(position=0; position<pDoc->RaceCount(year); position++) // for each year specific race
		AddRace(pDoc->GetRaceAt(year, position), Sample);
}

void CPrinterInterface::AddRace(CPrintRace* pPRace, BOOL Sample)
{
	// adds a particular race to the ballot 
	
	CByteList RandList;
	CString string;
	CGroup* pGroup;
	UINT col, row;
	CString candidate;
	POSITION pos;
	
	pPRace->GetLocation(col, row);
	
	AddSeperator(col, row++); // start with a seperator from the previous race 
	AddLine(col, row++, pPRace->GetCaption(), true); // the caption 
	
	for(pos=pPRace->DescriptionStartPosition(); pos;)
		AddLine(col, row++, pPRace->GetNextDecsriptionLine(pos), false); // the description 
	
	string.Format("Vote for up to %d below:", pPRace->GetMaxVotes()); // number of votes 
	AddLine(col, row++, string, false);
	
	for(pos=pPRace->GetHeadGroupPosition(); pos;) // for each group
	{
		pGroup=pPRace->GetNextGroup(pos);
		FillRandList(&RandList, pGroup->GetSize()); // the random ordering of the group 
		while(!RandList.IsEmpty()) // add the candidates 
			AddCandidate(col, row++, Sample, pGroup, RandList.RemoveHead());
	}
}

void CPrinterInterface::FillRandList(CByteList* pRandList, int size)
{
	// fills pRandList with the numbers 0 to size-1 inclusive in a random order
	
	BYTE entry;
	
	while(!pRandList->IsEmpty())
		pRandList->RemoveHead();
	
	while(pRandList->GetCount()<size)
		if(!pRandList->Find(entry=rand()%size))
			pRandList->AddTail(entry);
}

CString CPrinterInterface::WriteYearCode(ClassYear year)
{
	switch(year)
	{
	case AL: return "AL";
	case FR: return "FR";
	case SO: return "SO";
	case JR: return "JR";
	case SR: return "SR";
	case GR: return "GR";
	default: ASSERT(false); return "";
	}
}

void CPrinterInterface::AddCandidate(UINT col, UINT row, BOOL Sample, CGroup* pGroup, int cc)
{
	// adds a candidate and code at (col, row)	
	
	CString candidate;
	BYTE code;
	
	pGroup->GetCandCodeAt(cc, candidate, code);
	Arrow(col, row, candidate);
	
	if(Sample) // sample ballots don't have codes
		return;
	
	if(m_patterns[code]&0x10) { AddDot(col?38:43, 49-row); }
	if(m_patterns[code]&0x08) { AddDot(col?39:44, 49-row); }
	if(m_patterns[code]&0x04) { AddDot(col?40:45, 49-row); }
	if(m_patterns[code]&0x02) { AddDot(col?41:46, 49-row); }
	if(m_patterns[code]&0x01) { AddDot(col?42:47, 49-row); }
}