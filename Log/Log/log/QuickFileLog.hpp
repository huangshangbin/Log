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

	LogTextFile m_curLogFile;
	LogTextFile m_fileIndexTimeFile;
	int m_curFileIndex;
	string m_newestLogDirPath;

public:
	QuickFileLog() 
	{ 
		lock_guard<mutex> lockGuard(m_mutex);

		

		m_isStopThread = false;
		m_writeSpaceTime = 1000;

		thread tempThread([this]() {
			while (true)
			{
				{
					lock_guard<mutex> lockGuard(m_mutex);

					unsigned int curLogFileSize = 1024;

					while (m_logBufferQueue.empty() == false)
					{
						string* logStr = m_logBufferQueue.front();
						m_logBufferQueue.pop();

						//写入文件
						curLogFileSize = curLogFileSize + logStr->size();
						if (curLogFileSize >= 11 * 1024)
						{
							//创建新文件
							curLogFileSize = 0;
						}

						delete logStr;
					}

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
// 		if (indexFileList.size() == 0)
// 		{
// 			createNewestLogDir(curNewestLogDir, curTime.toString());
// 		}
// 		else
// 		{
// 			string curLogFilePath = getBiggestStr(indexFileList);
// 			m_curLogFile.reload(curLogFilePath);
// 
// 			m_fileIndexTimeFile.reload(curNewestLogDir + "\\indexTime.txt");
// 
// 			string curLogFileName = LogFileUtils::getFileOrDirName(curLogFilePath);
// 			m_curFileIndex = atoi(LogStringUtils::splitStringGetOneStr(curLogFileName, ".", 0).c_str());
// 
// 			m_newestLogDirPath = curNewestLogDir;
// 		}
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

		string* tempLogStr = new string(logStr);
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

};