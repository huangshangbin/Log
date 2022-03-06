#pragma once

#include<time.h>

#include "LogStringUtils.hpp"

class LogDateTime
{
private:
	tm m_time;

public:
	LogDateTime()
	{
		initTime();
	}

	LogDateTime(long timeStamp)
	{
		initTime();
		setTime(timeStamp);
	}

	LogDateTime(string timeStr)// "2020-09-27 11:54:12"
	{
		initTime();

		setYear(atoi(LogStringUtils::getStringUseCharEnd(timeStr, '-').c_str()));

		timeStr = LogStringUtils::getStringUseCharStart(timeStr, '-');
		setMonth(atoi(LogStringUtils::getStringUseCharEnd(timeStr, '-').c_str()));

		timeStr = LogStringUtils::getStringUseCharStart(timeStr, '-');
		setDay(atoi(LogStringUtils::getStringUseCharEnd(timeStr, ' ').c_str()));

		timeStr = LogStringUtils::getStringUseCharStart(timeStr, ' ');
		setHour(atoi(LogStringUtils::getStringUseCharEnd(timeStr, ':').c_str()));

		timeStr = LogStringUtils::getStringUseCharStart(timeStr, ':');
		setMinute(atoi(LogStringUtils::getStringUseCharEnd(timeStr, ':').c_str()));

		timeStr = LogStringUtils::getStringUseCharStart(timeStr, ':');
		setSecond(atoi(timeStr.c_str()));
	}


public:
	void setUseCurTime()
	{
		time_t curTime;
		time(&curTime);

		setTime(curTime);
	}

	void setYear(int year)
	{
		m_time.tm_year = year - 1900;
	}

	void setMonth(int month)
	{
		m_time.tm_mon = month - 1;
	}

	void setDay(int day)
	{
		m_time.tm_mday = day;
	}

	void setHour(int hour)
	{
		m_time.tm_hour = hour;
	}

	void setMinute(int minute)
	{
		m_time.tm_min = minute;
	}

	void setSecond(int second)
	{
		m_time.tm_sec = second;
	}

	string getYear()
	{
		return std::to_string(1900 + m_time.tm_year);
	}

	string getMonth()
	{
		return std::to_string(1 + m_time.tm_mon);
	}

	string getDay()
	{
		return std::to_string(m_time.tm_mday);
	}

	string getHour()
	{
		return std::to_string(m_time.tm_hour);
	}

	string getMinute()
	{
		return std::to_string(m_time.tm_min);
	}

	string getSecond()
	{
		return std::to_string(m_time.tm_sec);
	}

public:
	long toLong()
	{
		return mktime(&m_time);
	}

	string toString()
	{
		string dateStr = std::to_string(1900 + m_time.tm_year);
		dateStr = dateStr + "-" + getStringTime(1 + m_time.tm_mon);
		dateStr = dateStr + "-" + getStringTime(m_time.tm_mday);

		dateStr = dateStr + " " + getStringTime(m_time.tm_hour);
		dateStr = dateStr + ":" + getStringTime(m_time.tm_min);
		dateStr = dateStr + ":" + getStringTime(m_time.tm_sec);

		return dateStr;
	}



	//DateTime
private:
	void initTime()
	{
		m_time.tm_isdst = 0;

		m_time.tm_year = 2000 - 1900;
		m_time.tm_mon = 1 - 1;
		m_time.tm_mday = 1;

		m_time.tm_hour = 0;
		m_time.tm_min = 0;
		m_time.tm_sec = 0;
	}

	void setTime(long timeStamp)
	{
		time_t timeT = timeStamp;
		tm* tempTm = localtime(&timeT);
		if (tempTm == nullptr)
		{
			return;
		}

		m_time.tm_year = tempTm->tm_year;
		m_time.tm_mon = tempTm->tm_mon;
		m_time.tm_mday = tempTm->tm_mday;

		m_time.tm_hour = tempTm->tm_hour;
		m_time.tm_min = tempTm->tm_min;
		m_time.tm_sec = tempTm->tm_sec;
	}

	//toString
private:
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
};