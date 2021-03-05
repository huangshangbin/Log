#pragma once

#include "LogDateTime.hpp"
#include "LogBase.hpp"
#include "LogTextFile.hpp"
#include "../utils/LogFileUtils.hpp"


class FileLogBase : public LogBase
{
protected:
	string m_workDir;

	LogTextFile m_curLogFile;
	LogTextFile m_fileIndexTimeFile;
	int m_curFileIndex;
	string m_newestLogDirPath;

public:
	FileLogBase() : LogBase()
	{
		m_workDir = "";
	}

	~FileLogBase() {}

protected:
	string getNewestLogDir(LogDateTime& curTime)
	{
		return m_workDir + "\\" + curTime.getYear() + "\\" + curTime.getMonth() + "\\" + curTime.getDay();
	}

	void createNewestLogDir(string dirPath, string curTimeStr)
	{
		LogFileUtils::recursiveCreateDir(dirPath);

		m_curLogFile.reload(dirPath + "\\1000000.txt");
		m_curLogFile.save();

		m_fileIndexTimeFile.reload(dirPath + "\\indexTime.txt");
		m_fileIndexTimeFile.push("1000000=" + curTimeStr);
		m_fileIndexTimeFile.save();

		m_curFileIndex = 1000000;

		m_newestLogDirPath = dirPath;
	}

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

	string getExeFileDir()
	{
		char pathArray[MAX_PATH] = { 0 };
		GetModuleFileName(NULL, pathArray, MAX_PATH);

		string strPath = pathArray;

		return LogFileUtils::getPreviousLayerPath(strPath);
	}
};
