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

	queue<string*> m_logBufferQueue;
	unsigned int m_logBufferSize;

public:
	QuickFileLog() 
	{ 
		lock_guard<mutex> lockGuard(m_mutex);

		m_isStopThread = false;
		m_workDir = "";

		m_logBufferSize = 0;

		thread tempThread([this]() {
			while (true)
			{
				{
					lock_guard<mutex> lockGuard(m_mutex);

					if (m_isStopThread)
					{
						while (m_logBufferQueue.empty() == false)
						{
							string* logStr = m_logBufferQueue.front();
							m_logBufferQueue.pop();

							delete logStr;
						}
						

						cout << "thread stop...... " << endl;

						m_logBufferSize = 0;

						return;
					}

					if (m_logBufferSize >= 15 * 1024)
					{
						while (m_logBufferQueue.empty() == false)
						{
							string* logStr = m_logBufferQueue.front();
							m_logBufferQueue.pop();

							delete logStr;
						}
						

						cout << "clear log queue m_logBufferSize = " << m_logBufferSize <<" ---- "<<m_logBufferSize / 1024
							<<" * 1024"<< endl;

						m_logBufferSize = 0;
					}
				}

				Sleep(1000);

				//cout << "thread working...........  m_logBufferSize = "<< m_logBufferSize << "----  "<< m_logBufferSize/1024 << " * 1024" << endl;
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
	void debug(string funInfo, string logStr)
	{
		lock_guard<mutex> lockGuard(m_mutex);

		string* tempLogStr = new string(logStr);
		m_logBufferQueue.push(tempLogStr);
		m_logBufferSize = m_logBufferSize + logStr.size();
	}

	void info(string logStr)
	{
		lock_guard<mutex> lockGuard(m_mutex);

		string* tempLogStr = new string(logStr);
		m_logBufferQueue.push(tempLogStr);
		m_logBufferSize = m_logBufferSize + logStr.size();
	}

	void waring(string logStr)
	{
		lock_guard<mutex> lockGuard(m_mutex);

		string* tempLogStr = new string(logStr);
		m_logBufferQueue.push(tempLogStr);
		m_logBufferSize = m_logBufferSize + logStr.size();
	}

	void error(string logStr)
	{
		lock_guard<mutex> lockGuard(m_mutex);

		string* tempLogStr = new string(logStr);
		m_logBufferQueue.push(tempLogStr);
		m_logBufferSize = m_logBufferSize + logStr.size();
	}

private:

};