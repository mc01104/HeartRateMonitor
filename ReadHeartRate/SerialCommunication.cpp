#include "stdafx.h"
#include "SerialCommunication.h"

SerialPort::SerialPort() 
{
	serialPortHandle = INVALID_HANDLE_VALUE;
}
 
SerialPort::~SerialPort() 
{
	if (serialPortHandle!=INVALID_HANDLE_VALUE)
		CloseHandle(serialPortHandle);
 
	serialPortHandle = INVALID_HANDLE_VALUE;
}
 
int SerialPort::connect() 
{
	return connect(L"COM1");
}
 
int SerialPort::connect( wchar_t* device) 
{
	int error=0;
	DCB dcb;
 
	memset(&dcb,0,sizeof(dcb));
 
	dcb.DCBlength = sizeof(dcb);
 
	dcb.BaudRate = 115200;
	dcb.Parity = NOPARITY;
	dcb.fParity = 0;
	dcb.StopBits = ONESTOPBIT;
	dcb.ByteSize = 8;
 
	//serialPortHandle = CreateFile(device, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, NULL, NULL);
	serialPortHandle = CreateFile(device, GENERIC_READ , FILE_SHARE_WRITE, NULL, OPEN_EXISTING, NULL, NULL);
 
	if (serialPortHandle != INVALID_HANDLE_VALUE) 
	{
		//if(!SetCommState(serialPortHandle,&dcb))
		//	error=2;
		error = 0;
	}
	else 
	{
		error=1;
	}
 
	if (error!=0) 
	{
		disconnect();
	}
	else 
	{
		clear();
	}
 
	return error;
}
 
void SerialPort::disconnect(void) 
{
	CloseHandle(serialPortHandle);
	serialPortHandle = INVALID_HANDLE_VALUE;
 
	//printf("Port 1 has been CLOSED and %d is the file descriptionn", fileDescriptor);
}
 
int SerialPort::sendArray(unsigned char *buffer, int len) 
{
	unsigned long result=0;
 
	if (serialPortHandle!=INVALID_HANDLE_VALUE)
		WriteFile(serialPortHandle, buffer, len, &result, NULL);
 
	return result;
}
 
int SerialPort::getArray (unsigned char *buffer, int len) 
{
	unsigned long read_nbr;
 
	read_nbr = 0;
	if (serialPortHandle!=INVALID_HANDLE_VALUE)
		ReadFile(serialPortHandle, buffer, len, &read_nbr, NULL);
 
	return((int) read_nbr);
}
 
void SerialPort::clear() 
{
	PurgeComm (serialPortHandle, PURGE_RXCLEAR | PURGE_TXCLEAR);
}