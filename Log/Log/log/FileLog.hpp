#pragma once

#include "base/LogBase.hpp"
#include "base/LogTextFile.hpp"
#include "utils/LogDateTime.hpp"
#include "utils/LogFileUtils.hpp"
#include "utils/LogStringUtils.hpp"



class FileLog : public LogBase
{
public:
	FileLog() {}

	~FileLog() {}

public:
	LogTextFile m_curLogFile;
	LogTextFile m_fileIndexTimeFile;

	int m_curFileIndex;
	string m_lastCreateDirPath;

public:
	void setWorkDir(string workDir)
	{
		m_workDir = workDir;

		LogDateTime curTime;
		curTime.setUseCurTime();

		string dirPath = workDir + "\\" + curTime.getYear() + "\\" + curTime.getMonth() + "\\" + curTime.getDay();
		LogFileUtils::recursiveCreateDir(dirPath);

		m_lastCreateDirPath = dirPath;

		deque<string> indexFileList = LogFileUtils::getPathFirstLayerFilePath(dirPath);
		if (indexFileList.size() == 0)
		{
			m_curLogFile.reload(dirPath + "\\1000000.txt");
			m_curLogFile.save();

			m_fileIndexTimeFile.reload(dirPath + "\\indexTime.txt");
			m_fileIndexTimeFile.push("1000000 " + curTime.getHour() + ":" + curTime.getMinute() + ":" + curTime.getSecond());
			m_fileIndexTimeFile.save();

			setCurFileIndex();
		}
		else
		{
			string curLogFileStr = getBiggestStr(indexFileList);
			m_curLogFile.reload(curLogFileStr);

			m_fileIndexTimeFile.reload(dirPath + "\\indexTime.txt");

			setCurFileIndex();
		}
	}


public:
	void debug(string funInfo, string logStr)
	{
		LogDateTime curTime;
		curTime.setUseCurTime();


	}

	void info(string logStr)
	{
		lock_guard<mutex> lockGuard(m_mutex);

		if (m_logLevel > LogLevel::INFO)
		{
			return;
		}

		string detailLogStr = getDetailLogStr("[INFO] " + logStr);

		LogDateTime curTime;
		curTime.setUseCurTime();

		string dirPath = m_workDir + "\\" + curTime.getYear() + "\\" + curTime.getMonth() + "\\" + curTime.getDay();
		if (dirPath != m_lastCreateDirPath)
		{
			LogFileUtils::recursiveCreateDir(dirPath);

			m_curLogFile.reload(dirPath + "\\1000000.txt");
			m_curLogFile.save();

			m_fileIndexTimeFile.reload(dirPath + "\\indexTime.txt");
			m_fileIndexTimeFile.push("1000000 " + curTime.getHour() + ":" + curTime.getMinute() + ":" + curTime.getSecond());
			m_fileIndexTimeFile.save();

			setCurFileIndex();

			m_lastCreateDirPath = dirPath;
		}

		
		if (LogFileUtils::getFileSize(m_curLogFile.getFilePath()) < 11 * 1024)
		{
			m_curLogFile.push(detailLogStr);
			m_curLogFile.save();
		}
		else
		{
			m_curLogFile.reload(m_lastCreateDirPath + "\\" + std::to_string(m_curFileIndex + 1) + ".txt");
			m_curLogFile.push(detailLogStr);
			m_curLogFile.save();

			m_fileIndexTimeFile.push(std::to_string(m_curFileIndex + 1) + " " + curTime.getHour() + ":" + curTime.getMinute() + ":" + curTime.getSecond());
			m_fileIndexTimeFile.save();

			setCurFileIndex();
		}
	}

	void waring(string logStr)
	{

	}

	void error(string logStr)
	{

	}


private:
	string getBiggestStr(deque<string>& strList)
	{
		string biggestStr = strList[0];
		for (int i = 1; i < strList.size(); i++)
		{
			if (LogStringUtils::isExistStringInString(strList[i], "indexTime.txt"))
			{
				continue;
			}

			if (biggestStr < strList[i])
			{
				biggestStr = strList[i];
			}
		}

		return biggestStr;
	}

	void setCurFileIndex()
	{
		string fileName = LogFileUtils::getFileOrDirName(m_curLogFile.getFilePath());
		m_curFileIndex = atoi(LogStringUtils::splitStringGetOneStr(fileName, ".", 0).c_str());
	}
};