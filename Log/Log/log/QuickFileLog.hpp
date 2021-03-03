#pragma once

#include "base/LogBase.hpp"

#include <thread>
#include <queue>

class QuickFileLog : public LogBase
{
private:
	string m_workDir;

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

		m_workDir = "";

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