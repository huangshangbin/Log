#pragma once

#include "base/FileLogBase.hpp"
#include "base/LogTextFile.hpp"
#include "base/LogDateTime.hpp"
#include "utils/LogFileUtils.hpp"
#include "utils/LogStringUtils.hpp"



class FileLog : public FileLogBase
{
public:
	FileLog() { m_workDir = "";}
	~FileLog() {}


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