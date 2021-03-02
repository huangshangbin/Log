#pragma once

#include <log/FileLog.hpp>
#include <thread>

//  simpleFileLog  -----------------------------
void simpleFileLog()
{
	FileLog fileLog;
	fileLog.setWorkDir("E:\\tempDir");
	fileLog.setLevel(LogLevel::DEBUG);

	for (int i = 0; i < 1000; i++)
	{
		DEBUG_LOG(fileLog, "huangshangbin ----  " + std::to_string(i));
		fileLog.info("huangshangbin ----  " + std::to_string(i));
		fileLog.waring("huangshangbin ----  " + std::to_string(i));
		fileLog.error("huangshangbin ----  " + std::to_string(i));

		cout << i << endl;
	}
}

//  multiThreadFileLog  -------------------------

FileLog fileLog;

void debugFileLogThreadFun()
{
	while (true)
	{
		DEBUG_LOG(fileLog, "huangshangbin debug");
	}
}

void infoFileLogThreadFun()
{
	while (true)
	{
		fileLog.info("huangshangbin info");
	}
}

void waringFileLogThreadFun()
{
	while (true)
	{
		fileLog.waring("huangshangbin waring");
	}
}

void errorFileLogThreadFun()
{
	while (true)
	{
		fileLog.error("huangshangbin error");
	}
}

void multiThreadFileLog()
{
	fileLog.setWorkDir("E:\\tempDir");

	thread debugThread(debugFileLogThreadFun);
	thread infoThread(infoFileLogThreadFun);
	thread waringThread(waringFileLogThreadFun);
	thread errorThread(errorFileLogThreadFun);

	debugThread.join();
	infoThread.join();
	waringThread.join();
	errorThread.join();
}