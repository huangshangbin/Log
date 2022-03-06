#pragma once

#include "LogByteStreamFile.hpp"
#include "../utils/LogStringUtils.hpp"


class LogTextFile
{
private:
	string m_filePath;
	deque<string> m_dataList;

public:
	LogTextFile() {}

	LogTextFile(string filePath)
	{
		m_filePath = filePath;
		initDataList();
	}
	~LogTextFile() {}

public:
	void reload(string filePath)
	{
		m_filePath = filePath;
		initDataList();
	}

	void reWrite(deque<string>& dataList)
	{
		copyDeque(m_dataList, dataList);
	}

	void exportDataList(deque<string>& dataList)
	{
		copyDeque(dataList, m_dataList);
	}

	void push(string str)
	{
		m_dataList.push_back(str);
	}

	void set(int row, string data)
	{
		if (row >= m_dataList.size() || row < 0)
		{
			return;
		}

		m_dataList[row] = data;
	}

	string get(int row)
	{
		if (row >= m_dataList.size() || row < 0)
		{
			return "";
		}

		return m_dataList[row];
	}

	void erase(int row)
	{
		if (row < 0 || row >= m_dataList.size())
		{
			return;
		}

		auto eraseIt = m_dataList.begin();
		for (int i = 0; i < row; i++)
		{
			eraseIt++;
		}

		m_dataList.erase(eraseIt);
	}

public:
	string getFilePath()
	{
		return m_filePath;
	}

	int size()
	{
		return m_dataList.size();
	}

	void save()
	{
		string data;
		if (m_dataList.size() > 0)
		{
			data = m_dataList[0];
			for (int i = 1; i < m_dataList.size(); i++)
			{
				data = data + "\r\n" + m_dataList[i];
			}
		}

		LogByteStreamFile::writeFile(m_filePath, data.c_str(), data.length());
	}

	void clear()
	{
		m_dataList.clear();
	}


private:
	void initDataList()
	{
		m_dataList.clear();

		ifstream inFileStream(m_filePath, std::ios::binary);

		inFileStream.seekg(0, std::ios::end);
		int fileLength = inFileStream.tellg();

		inFileStream.seekg(0, std::ios::beg);
		char* fileBuffer = new char[fileLength + 1];
		inFileStream.read(fileBuffer, fileLength);

		fileBuffer[fileLength] = '\0';

		string data(fileBuffer);
		if (fileLength > 0)
		{
			m_dataList = LogStringUtils::splitString(data, "\r\n");
		}
	}


private:
	template<class T>
	void copyDeque(deque<T>& targetDeque, deque<T>& srcDeque)
	{
		targetDeque.clear();
		for (T& data : srcDeque)
		{
			targetDeque.push_back(data);
		}
	}
};

