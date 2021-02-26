#pragma once

#include "base/LogBase.hpp"

#include <windows.h>
#include <iostream>
#include <string>

using namespace std;

class ConsoleLog : public LogBase
{
public:
	ConsoleLog() { }
	~ConsoleLog() {}

public:
	void debug(string funInfo, string logStr)
	{
		if (m_logLevel > LogLevel::DEBUG)
		{
			return;
		}

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE);

		logStr = "[DEBUG] " + funInfo + " " + logStr;
		detailOutLogStr(logStr);

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY);
	}

	void info(string logStr)
	{
		if (m_logLevel > LogLevel::INFO)
		{
			return;
		}

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE);

		logStr = "[INFO] " + logStr;
		detailOutLogStr(logStr);

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY);
	}

	void waring(string logStr)
	{
		if (m_logLevel > LogLevel::WARING)
		{
			return;
		}

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);

		logStr = "[WARING] " + logStr;
		detailOutLogStr(logStr);

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY);
	}

	void error(string logStr)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);

		logStr = "[ERROR] " + logStr;
		detailOutLogStr(logStr);

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY);
	}
};