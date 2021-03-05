#pragma once

#include "base/FileLogBase.hpp"

#include <thread>
#include <queue>

class QuickFileLog : public FileLogBase
{
private:
	thread m_thread;
	bool m_isStopThread;
	int m_writeSpaceTime;

	queue<string*> m_logBufferQueue;
	
	unsigned int m_curFileBufferSize;

public:
	QuickFileLog() 
	{ 
		lock_guard<mutex> lockGuard(m_mutex);

		m_isStopThread = false;
		m_writeSpaceTime = 1000;

		m_curFileBufferSize = 0;

		thread tempThread([this]() {
			while (true)
			{
				{
					lock_guard<mutex> lockGuard(m_mutex);

					while (m_logBufferQueue.empty() == false)
					{
						string* logStr = m_logBufferQueue.front();
						m_logBufferQueue.pop();

						addLog(*logStr);

						delete logStr;
					}

					m_curLogFile.save();

					if (m_isStopThread)
					{
						return;
					}
				}

				Sleep(m_writeSpaceTime);
			}
		});

		m_thread = std::move(tempThread);
	}

	~QuickFileLog()
	{
		{
			lock_guard<mutex> lockGuard(m_mutex);
			m_isStopThread = true;
		}

		m_thread.join();
	}

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

			m_curFileBufferSize = 0;
		}
		else
		{
			string curLogFilePath = getBiggestStr(indexFileList);
			m_curLogFile.reload(curLogFilePath);

			m_curFileBufferSize = LogFileUtils::getFileSize(curLogFilePath);

			m_fileIndexTimeFile.reload(curNewestLogDir + "\\indexTime.txt");

			string curLogFileName = LogFileUtils::getFileOrDirName(curLogFilePath);
			m_curFileIndex = atoi(LogStringUtils::splitStringGetOneStr(curLogFileName, ".", 0).c_str());

			m_newestLogDirPath = curNewestLogDir;
		}
	}

	void setWriteSpaceTime(int writeSpaceTime)//millisecond
	{
		m_writeSpaceTime = writeSpaceTime;
	}

public:
	void debug(string funInfo, string logStr)
	{
		lock_guard<mutex> lockGuard(m_mutex);

		string* tempLogStr = new string(logStr);
		m_logBufferQueue.push(tempLogStr);
	}

	void info(string logStr)
	{
		lock_guard<mutex> lockGuard(m_mutex);

		string* tempLogStr = new string(getDetailLogStr("[INFO] " + logStr));
		m_logBufferQueue.push(tempLogStr);
	}

	void waring(string logStr)
	{
		lock_guard<mutex> lockGuard(m_mutex);

		string* tempLogStr = new string(logStr);
		m_logBufferQueue.push(tempLogStr);
	}

	void error(string logStr)
	{
		lock_guard<mutex> lockGuard(m_mutex);

		string* tempLogStr = new string(logStr);
		m_logBufferQueue.push(tempLogStr);
	}

private:
	void addLog(string detailLogStr)
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

			m_curLogFile.save();
			m_curFileBufferSize = 0;
		}

		if (m_curFileBufferSize < 11 * 1024)
		{
			m_curLogFile.push(detailLogStr);
			m_curFileBufferSize = m_curFileBufferSize + detailLogStr.size();
		}
		else
		{
			m_curLogFile.save();

			m_curLogFile.reload(m_newestLogDirPath + "\\" + std::to_string(m_curFileIndex + 1) + ".txt");
			m_curLogFile.push(detailLogStr);

			m_curFileBufferSize = detailLogStr.size();

			m_fileIndexTimeFile.push(std::to_string(m_curFileIndex + 1) + "=" + curTime.toString());
			m_fileIndexTimeFile.save();

			m_curFileIndex = m_curFileIndex + 1;
		}
	}
};