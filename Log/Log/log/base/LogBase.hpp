#pragma once

#include "LogLevel.hpp"
#include "../utils/LogStringUtils.hpp"

#include <iostream>
#include <thread>
#include <mutex>
#include <string>
#include <deque>

using namespace std;


#include <time.h>
#include <sys/timeb.h>

#pragma warning(disable:4996)


#define DEBUG_LOG(logObj, logStr)\
{\
\
deque<string> fileStrList = LogStringUtils::splitString(__FILE__, "\\");\
string fileFunStr = "[" + fileStrList[fileStrList.size() - 1] + "][" + string(__func__);\
fileFunStr = fileFunStr + "][" + std::to_string(__LINE__) + "]";\
logObj.debug(fileFunStr, logStr);\
\
}



class LogBase
{
protected:
	LogLevel m_logLevel;
	mutex m_mutex;

public:
	LogBase() { m_logLevel = LogLevel::DEBUG; }
	~LogBase() {}


public:
	virtual void debug(string funInfo, string logStr) = 0;
	virtual void info(string logStr) = 0;
	virtual void waring(string logStr) = 0;
	virtual void error(string logStr) = 0;

public:
	void setLevel(LogLevel logLevel) { m_logLevel = logLevel; }

	string getDetailLogStr(string logStr)
	{
		return getDateTimeStr() + " " + logStr;
	}

//getDetailLogStr
private:
	string getDateTimeStr()
	{
		timeb curTimeStamp;
		ftime(&curTimeStamp);

		tm* curTime = localtime(&curTimeStamp.time);

		string timeStr = std::to_string(1900 + curTime->tm_year);
		timeStr = timeStr + "-" + getStringTime(1 + curTime->tm_mon);
		timeStr = timeStr + "-" + getStringTime(curTime->tm_mday);

		timeStr = timeStr + " " + getStringTime(curTime->tm_hour);
		timeStr = timeStr + ":" + getStringTime(curTime->tm_min);
		timeStr = timeStr + ":" + getStringTime(curTime->tm_sec);

		timeStr = timeStr + "." + getMilliTmStr(curTimeStamp.millitm);

		return "[" + timeStr + "]";
	}

	string getStringTime(int number)
	{
		if (number < 10)
		{
			return "0" + std::to_string(number);
		}
		else
		{
			return std::to_string(number);
		}
	}

	string getMilliTmStr(unsigned short milliTm)
	{
		if (milliTm < 10)
		{
			return "00" + std::to_string(milliTm);
		}

		if (milliTm < 100)
		{
			return "0" + std::to_string(milliTm);
		}
		
		return std::to_string(milliTm);
	}

};

