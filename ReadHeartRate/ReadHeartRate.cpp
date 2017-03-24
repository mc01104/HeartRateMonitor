// ReadHeartRate.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "SerialCommunication.h"
#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>

::std::vector<::std::string> ReadLinesFromFile(const ::std::string& pathToFile)
{
	::std::vector< ::std::string> linesVector;

	::std::ifstream inputFile(pathToFile.c_str());
	
	::std::string tempLine;
	while(::std::getline(inputFile, tempLine))
		linesVector.push_back(tempLine);

	return linesVector;
}

//::std::vector<unsigned char*> readMeasurementsFromFile(::std::string filename)
//{
//	::std::vector<::std::string> lines = ReadLinesFromFile(filename);	
//	::std::vector<unsigned char*> result;
//	result.resize(lines.size());
//
//	char tmp[200];
//	for (int i = 0; i < lines.size(); ++i)
//		::std::strcpy( (char*) &result[i], lines[i].c_str());
//	
//	return result;
//}

::std::vector<::std::string> splitStr(::std::string inputStr, char delim)
{
	::std::vector<::std::string> result;
	::std::stringstream ss;
	ss.str(inputStr);
	::std::string tmp;
	while (::std::getline(ss, tmp, delim))
	{
		result.push_back(tmp);
	}

	return result;
}

void testSerial()
{
	SerialPort sPort;
	sPort.connect();

	unsigned char m_testRead[200];
	::std::vector<::std::string> strings;
	while (true)
	{
		int bytesRead = sPort.getArray(m_testRead, 200);

		::std::string str(m_testRead, m_testRead + bytesRead);
		strings = splitStr(str, ',');
		::std::cout << "Heart rate [bpm]:" << strings[4].c_str() << ::std::endl;

	}
	sPort.clear();
	sPort.disconnect();

}

void testStringParsing()
{
	::std::vector<::std::string> lines = ReadLinesFromFile("working.TXT");	
	::std::vector<::std::string> strings;

	unsigned char* val = new unsigned char[200];
	::std::string tmpStr;

	for (int i = 0; i < lines.size(); ++i)
	{
		::std::copy(lines[i].begin(), lines[i].end(), val);

		::std::string my_std_string(val, val + 200);

		//strings = splitStr(lines[i], ',');
		strings = splitStr(my_std_string, ',');
		::std::cout << "Heart rate [bpm]:" << strings[4].c_str() << ::std::endl;
	}



	//::std::vector<::std::string> strings;
	//for (int i = 0; i < measurements.size(); ++i)
	//{
	//	::std::string str(measurements[i], measurements[i] + 200);
	//	strings = splitStr(str, ',');
	//	::std::cout << "Heart rate [bpm]:" << strings[4].c_str() << ::std::endl;
	//}


}

int _tmain(int argc, _TCHAR* argv[])
{
//	testStringParsing();
	testSerial();
}

