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
#include "ScannerInterface.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#ifdef _SIM_BALLOT  // If were're reading ballot files 

CScannerInterface::CScannerInterface()
{
	m_codes[0x00]=31; m_codes[0x10]=11;
	m_codes[0x01]=15; m_codes[0x11]=21;
	m_codes[0x02]=14; m_codes[0x12]=19;
	m_codes[0x03]=16; m_codes[0x13]= 5;
	m_codes[0x04]=13; m_codes[0x14]=24;
	m_codes[0x05]=18; m_codes[0x15]= 7;
	m_codes[0x06]=25; m_codes[0x16]= 8;
	m_codes[0x07]= 2; m_codes[0x17]=27;
	m_codes[0x08]=12; m_codes[0x18]=17;
	m_codes[0x09]=23; m_codes[0x19]=10;
	m_codes[0x0a]=22; m_codes[0x1a]= 3;
	m_codes[0x0b]= 9; m_codes[0x1b]=28;
	m_codes[0x0c]=20; m_codes[0x1c]= 1;
	m_codes[0x0d]= 4; m_codes[0x1d]=29;
	m_codes[0x0e]= 6; m_codes[0x1e]=30;
	m_codes[0x0f]=26; m_codes[0x1f]= 0;
}

BOOL CScannerInterface::OpenComm()  { return true; }
BOOL CScannerInterface::CloseComm() { return true; }
BOOL CScannerInterface::CheckHopper() { m_HopperEmpty=GET_APP->m_InputBallots.IsEmpty(); return true; }

BOOL CScannerInterface::ScanBallot()
{
	CString line;
	int x;
	
	CStdioFile SF(GET_APP->m_InputBallots.RemoveHead(), CFile::modeRead|CFile::typeText); //open next file
	
	for(int y=63; y;) //countdown from 63
	{
		y--;
		SF.ReadString(line);
		for(x=0; x<48; x++)
			m_sheet[x][y]=(line[x]=='*'); //copy info to m_sheet
	}
	
	SF.Close();
	return CheckHopper(); //Are there more ballots to be read?
}

#else // if were're actually scanning ballots  

CScannerInterface::CScannerInterface() { m_hComm=INVALID_HANDLE_VALUE; }

BOOL CScannerInterface::OpenComm()
{
	DCB	CB;
	COMMTIMEOUTS CT;
	CCommSettings CS;
	
	if(CS.DoModal()!=IDOK)  // get info about the disiered interface 
		return false;
	
	m_hComm=CreateFile(CS.m_name, GENERIC_WRITE|GENERIC_READ, 0, 0, OPEN_EXISTING, 0, NULL); // open the port
	if(m_hComm==INVALID_HANDLE_VALUE)
		return false;
	
	GetCommState(m_hComm, &CB); // configure the comm state 
	CB.BaudRate=CS.m_BaudRate;
	CB.fParity=true;
	CB.ByteSize=7;
	CB.Parity=ODDPARITY;
	CB.StopBits=2;
	SetCommState(m_hComm, &CB);
	
	GetCommTimeouts(m_hComm, &CT);  // configure the timeouts 
	CT.ReadIntervalTimeout=CS.m_RIT; 
	CT.ReadTotalTimeoutMultiplier=CS.m_RTTM;
	CT.ReadTotalTimeoutConstant=CS.m_RTTC;
	CT.WriteTotalTimeoutMultiplier=CS.m_WTTM;
	CT.WriteTotalTimeoutConstant=CS.m_WTTC;
	SetCommTimeouts(m_hComm, &CT);
	
	return true;
}

BOOL CScannerInterface::CloseComm()
{
	if(CloseHandle(m_hComm))
		m_hComm=INVALID_HANDLE_VALUE;
	
	return(m_hComm==INVALID_HANDLE_VALUE);
}

BOOL CScannerInterface::ScanBallot()
{
	int y=0;   // The row for the grid 
	BYTE head;
	
	m_CommQueue.RemoveAll();  // flush the CommQueue
	
	if(!Write(0x11)) // tell the scanner to scan a ballot 
		return false;
	
	for(int ctr=0; (ctr<200)&&(m_CommQueue.IsEmpty()); ctr++)  // fill the CommQueue with data from the scanner 
		FillCommQueue(100);
	
	FillCommQueue(100);
	
	while(y<63)  // until weel have all the data processed 
	{
		if(!ReadLine(y, head)) // fill one line 
			return false;
		
		if(head=='a')  // 'a' indicated that the line is on the front of the ballot 
			y++;
	}
	
	return CheckHopper(); // update the hopper status 
}

BOOL CScannerInterface::CheckHopper()
{
	BYTE status;
	
	m_CommQueue.RemoveAll();  //flush the CommQueue 
	
	if(!Write('s'))  // "s0" requests a status record 
		return false;
	
	if(!Write('0'))
		return false;
	
	FillCommQueue(50);  // read the data 
	
	for(int index=0; index<50; index++) // there are 50 bytes in the record 
	{
		if(!Read(status)) // get the data 
			return false;
		
		if(index==11)  // the least significant bit of the 11th byte indicates that the hopper is empty
			m_HopperEmpty=status&0x01;
	}
	
	return true;
}

BOOL CScannerInterface::Eval(char val)
{
	//determines whether of not a byte from the scanner indicated that the dot is filled in or not 
	switch(val)
	{
	case '0': return false;
	case '1': return(0x1>THRESHOLD);
	case '2': return(0x2>THRESHOLD);
	case '3': return(0x3>THRESHOLD);
	case '4': return(0x4>THRESHOLD);
	case '5': return(0x5>THRESHOLD);
	case '6': return(0x6>THRESHOLD);
	case '7': return(0x7>THRESHOLD);
	case '8': return(0x8>THRESHOLD);
	case '9': return(0x9>THRESHOLD);
	case 'A': return(0xa>THRESHOLD);
	case 'B': return(0xb>THRESHOLD);
	case 'C': return(0xc>THRESHOLD);
	case 'D': return(0xd>THRESHOLD);
	case 'E': return(0xe>THRESHOLD);
	case 'F': return(0xf>THRESHOLD);
	default:  return false;
	}
}

BOOL CScannerInterface::ReadLine(int y, BYTE& head)
{
	if(!Read(head))  // a record needs a head
		return false;
	
	for(int pos=0; pos<48;)  // a line is 48 dots wide 
		if(!ReadLinePortion(y, pos))
			return false;
	
	return true;
}

BOOL CScannerInterface::ReadLinePortion(int y, int& pos)
{
	BYTE curr, rep;
	int stop_pos;
	
	if(!Read(curr))  // get the next byte 
		return false;
	
	if(curr!=0x15)  //if this is not a compressed section 
	{
		m_sheet[47-(pos++)][y]=Eval(curr);  // set the array element and increment position 
		return true;
	}
	
	if(!Read(rep))  // number of repetitions 
		return false;
	
	if(!Read(curr))  // value that is repeating 
		return false;
	
	if((stop_pos=pos+(rep&0x3f))>=48)  // if the line will be overrun 
		return false;
	
	while(pos<stop_pos)  // fill the section 
		m_sheet[47-(pos++)][y]=Eval(curr);
	
	return true;	
}

void CScannerInterface::FillCommQueue(DWORD dwMilliseconds)
{
	BYTE Buffer[BUFFER_SIZE];
	DWORD i, BytesRead=0;
	
	if(m_hComm==INVALID_HANDLE_VALUE)
		return;
	
	Sleep(dwMilliseconds); // give the scanner time to reply 
	
	do
	{
		ReadFile(m_hComm, &Buffer, BUFFER_SIZE, &BytesRead, NULL); // transfer data to buffer 
		for(i=0; i<BytesRead; i++) // transfer data to CommQueue 
			m_CommQueue.AddTail(Buffer[i]&0x7f);
	}
	while(BytesRead==BUFFER_SIZE); // while the buffer is saturated 
}

BOOL CScannerInterface::Read(BYTE& inp)
{
	//get the first byte in the CommQueue
	
	if(m_CommQueue.IsEmpty()) // is there's no more data 
		return false;
	
	inp=m_CommQueue.RemoveHead(); // get the first element 
	return true;
}

BOOL CScannerInterface::Write(BYTE output)
{
	DWORD BytesWritten;
	
	if(m_hComm==INVALID_HANDLE_VALUE) // if the port is closed 
		return false;
	
	WriteFile(m_hComm, &output, 1, &BytesWritten, NULL); // write one byte to comm port 
	return BytesWritten; // return success
}

#endif

BOOL CScannerInterface::GetRIN(CString &RIN)
{
	// gets the RIN from the ballot 
	
	int digit;
	RIN.Empty();
	
	for(int i=0; i<9; i++)  // sweep horizontilly 
	{
		for(digit=0; digit<10; digit++) // sweep vertically 
			if(m_sheet[i+38][60-digit]) // if the dot is filled in 
				RIN+=(char)(digit+'0');  // add the character to the string 
		
		if(RIN.GetLength()!=i+1) // if no digit or more than one digit was specified 
			return false;
	}
	
	return true;
}

BOOL CScannerInterface::GetSerial(ClassYear &year, int &number)
{
	// read the serial number of the ballot 
	
	BYTE cs;
	
	number=0;
	for(int bit=0; bit<16; bit++)
		number|=(m_sheet[15+bit][0]?(1<<bit):0);  // build number from the bits 
	
	cs=(m_sheet[39][49]?0x0:0x1)|(m_sheet[41][49]?0x0:0x2)|  // read the checksum 
		(m_sheet[44][49]?0x0:0x4)|(m_sheet[46][49]?0x0:0x8);
	
	if((cs^(number>>12)^(number>>8)^(number>>4)^(number))&0xf)  //verify the CS 
		return false;
	
	switch((m_sheet[11][0]?0x8:0x0)|(m_sheet[12][0]?0x4:0x0)|   // determine the year 
		(m_sheet[13][0]?0x2:0x0)|(m_sheet[14][0]?0x1:0x0))
	{
	case 0x6: year=AL; return true;
	case 0x9: year=FR; return true;
	case 0xa: year=SO; return true;
	case 0x3: year=JR; return true;
	case 0xc: year=SR; return true;
	case 0x5: year=GR; return true;
	default: return false;
	}
}

void CScannerInterface::FillCodeList(CScanRace* pSRace, CByteList* pCodeList)
{
	// fill the CodeList with the codes of candidates that were voted for 
	
	UINT col, row0;
	int length;
	BYTE pattern;
	
	pSRace->GetLocation(col, row0, length);  // physical location of the race 
	
	pCodeList->RemoveAll();
	
	for(UINT row=row0; row<row0+length; row++) // for each row the race occupies 
		if(m_sheet[col?20:2][49-row])  // if the dot is filled in 
		{
			pattern=0;                                      // build the pattern 
			pattern|=m_sheet[col?38:43][49-row]?0x10:0x00;
			pattern|=m_sheet[col?39:44][49-row]?0x08:0x00;
			pattern|=m_sheet[col?40:45][49-row]?0x04:0x00;
			pattern|=m_sheet[col?41:46][49-row]?0x02:0x00;
			pattern|=m_sheet[col?42:47][49-row]?0x01:0x00;
			
			pCodeList->AddTail(m_codes[pattern]);  // Add the code based on the pattern
		}
}