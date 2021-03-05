#pragma once

#include <log/QuickFileLog.hpp>
#include <thread>


//  simple QuickFileLog  -----------------------------
void simpleQuickFileLog()
{
	QuickFileLog quickFileLog;
	quickFileLog.setWorkDir("E:\\tempDir");
	quickFileLog.setLevel(LogLevel::DEBUG);

	LogDateTime curTime;

	int i = 0;
	while (true)
	{
		DEBUG_LOG(quickFileLog, "huangshangbin ----  " + std::to_string(i));
		quickFileLog.info("huangshangbin ----  " + std::to_string(i));
		quickFileLog.waring("huangshangbin ----  " + std::to_string(i));
		quickFileLog.error("huangshangbin ----  " + std::to_string(i));

		curTime.setUseCurTime();
		cout << curTime.toString() << endl;

		//Sleep(1000 * 60);
		i++;
	}

}

//  multiThreadQuickFileLog  -------------------------

QuickFileLog quickFileLog;

void debugQuickFileLogThreadFun()
{
	while (true)
	{
		DEBUG_LOG(quickFileLog, "huangshangbin debug");
	}
}

void infoQuickFileLogThreadFun()
{
	while (true)
	{
		quickFileLog.info("huangshangbin info");
	}
}

void waringQuickFileLogThreadFun()
{
	while (true)
	{
		quickFileLog.waring("huangshangbin waring");
	}
}

void errorQuickFileLogThreadFun()
{
	while (true)
	{
		quickFileLog.error("huangshangbin error");
	}
}

void multiThreadQuickFileLog()
{
	quickFileLog.setWorkDir("E:\\tempDir");

	thread debugThread(debugQuickFileLogThreadFun);
	thread infoThread(infoQuickFileLogThreadFun);
	thread waringThread(waringQuickFileLogThreadFun);
	thread errorThread(errorQuickFileLogThreadFun);

	debugThread.join();
	infoThread.join();
	waringThread.join();
	errorThread.join();
}