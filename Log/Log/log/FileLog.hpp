#pragma once

#include "base/LogBase.hpp"
#include "base/LogTextFile.hpp"
#include "utils/LogDateTime.hpp"
#include "utils/LogFileUtils.hpp"
#include "utils/LogStringUtils.hpp"



class FileLog : public LogBase
{
public:
	FileLog() { m_workDir = "";}
	~FileLog() {}

private:
	LogTextFile m_curLogFile;
	LogTextFile m_fileIndexTimeFile;

	string m_workDir;
	int m_curFileIndex;
	string m_newestLogDirPath;

public:
	void setWorkDir(string workDir)
	{
		m_workDir = workDir;

		LogDateTime curTime;
		curTime.setUseCurTime();

		string curNewestLogDir = getNewestLogDir(curTime);

		deque<string> indexFileList = LogFileUtils::getPathFirstLayerFilePath(curNewestLogDir);
		if (indexFileList.size() == 0)
		{
			createNewestLogDir(curNewestLogDir, curTime.toString());
		}
		else
		{
			string curLogFilePath = getBiggestStr(indexFileList);
			m_curLogFile.reload(curLogFilePath);

			m_fileIndexTimeFile.reload(curNewestLogDir + "\\indexTime.txt");

			string curLogFileName = LogFileUtils::getFileOrDirName(curLogFilePath);
			m_curFileIndex = atoi(LogStringUtils::splitStringGetOneStr(curLogFileName, ".", 0).c_str());

			m_newestLogDirPath = curNewestLogDir;
		}	
	}

public:
	void debug(string funInfo, string logStr)
	{
		lock_guard<mutex> lockGuard(m_mutex);

		if (m_logLevel > LogLevel::DEBUG)
		{
			return;
		}

		addLog("[DEBUG] " + funInfo + " " + logStr);
	}

	void info(string logStr)
	{
		lock_guard<mutex> lockGuard(m_mutex);

		if (m_logLevel > LogLevel::INFO)
		{
			return;
		}

		addLog("[INFO] " + logStr);
	}

	void waring(string logStr)
	{
		lock_guard<mutex> lockGuard(m_mutex);

		if (m_logLevel > LogLevel::WARING)
		{
			return;
		}

		addLog("[WARING] " + logStr);
	}

	void error(string logStr)
	{
		lock_guard<mutex> lockGuard(m_mutex);

		if (m_logLevel > LogLevel::ERROR_)
		{
			return;
		}

		addLog("[ERROR] " + logStr);
	}

private:
	string getExeFileDir()
	{
		char pathArray[MAX_PATH] = { 0 };
		GetModuleFileName(NULL, pathArray, MAX_PATH);

		string strPath = pathArray;

		return LogFileUtils::getPreviousLayerPath(strPath);
	}


//setWorkDir
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

//debug
private:
	void addLog(string baseLogStr)
	{
		if (m_workDir == "")
		{
			setWorkDir(getExeFileDir());
		}

		LogDateTime curTime;
		curTime.setUseCurTime();

		string curNewestLogDir = getNewestLogDir(curTime);
		if (curNewestLogDir != m_newestLogDirPath)
		{
			createNewestLogDir(curNewestLogDir, curTime.toString());
		}


		string detailLogStr = getDetailLogStr(baseLogStr);
		if (LogFileUtils::getFileSize(m_curLogFile.getFilePath()) < 11 * 1024)
		{
			m_curLogFile.push(detailLogStr);
			m_curLogFile.save();
		}
		else
		{
			m_curLogFile.reload(m_newestLogDirPath + "\\" + std::to_string(m_curFileIndex + 1) + ".txt");
			m_curLogFile.push(detailLogStr);
			m_curLogFile.save();

			m_fileIndexTimeFile.push(std::to_string(m_curFileIndex + 1) + "=" + curTime.toString());
			m_fileIndexTimeFile.save();

			m_curFileIndex = m_curFileIndex + 1;
		}
	}
};