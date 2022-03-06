#pragma once
#include <string>
#include <fstream>

#include <iostream>
using namespace std;

class LogByteStreamFile
{
private:
	char* m_buffer;
	long m_length;


public:
	LogByteStreamFile(string filePath)
	{
		ifstream inFileStream(filePath, std::ios::binary);

		inFileStream.seekg(0, std::ios::end);
		m_length = inFileStream.tellg();

		inFileStream.seekg(0, std::ios::beg);
		m_buffer = new char[m_length];
		memset(m_buffer, 0, m_length);

		inFileStream.read(m_buffer, m_length);

		inFileStream.close();
	}

	~LogByteStreamFile()
	{
		if (m_buffer != nullptr)
		{
			delete[] m_buffer;
		}
	}

public:
	char* getBuffer()
	{
		return m_buffer;
	}

	long getLength()
	{
		return m_length;
	}

public:
	static void writeFile(string filePath, const char* buffer, long bufferLength)
	{
		ofstream outFileStream(filePath, std::ios::binary);
		outFileStream.write(buffer, bufferLength);

		outFileStream.close();
	}

private:
	LogByteStreamFile(const LogByteStreamFile& byteStreamFile) {}
	void operator = (const LogByteStreamFile& byteStreamFile) {}
};
