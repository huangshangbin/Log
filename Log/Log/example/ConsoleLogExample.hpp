#pragma once

#include <log/ConsoleLog.hpp>
#include <thread>

//  simpleConsoleLog  -----------------------------
void simpleConsoleLog()
{
	ConsoleLog consoleLog;

	consoleLog.setLevel(DEBUG);

	DEBUG_LOG(consoleLog, "huangshangbin debug");


	cout << "----------------" << endl;
	consoleLog.info("huangshangbin info");

	cout << "----------------" << endl;
	consoleLog.waring("huangshangbin waring");

	cout << "----------------" << endl;
	consoleLog.error("huangshangbin error");
}


//  multiThreadConsoleLog  -------------------------
ConsoleLog consoleLog;

void debugConsoleLogThreadFun()
{
	for(int i = 0; i < 100000; i++)
	{
		DEBUG_LOG(consoleLog, "huangshangbin debug");
	}
}

void infoConsoleLogThreadFun()
{
	for (int i = 0; i < 100000; i++)
	{
		consoleLog.info("huangshangbin info");
	}
}

void waringConsoleLogThreadFun()
{
	for (int i = 0; i < 100000; i++)
	{
		consoleLog.waring("huangshangbin waring");
	}
}

void errorConsoleLogThreadFun()
{
	for (int i = 0; i < 100000; i++)
	{
		consoleLog.error("huangshangbin error");
	}
}


void multiThreadConsoleLog()
{
	thread debugThread(debugConsoleLogThreadFun);
	thread infoThread(infoConsoleLogThreadFun);
	thread waringThread(waringConsoleLogThreadFun);
	thread errorThread(errorConsoleLogThreadFun);

	debugThread.join();
	infoThread.join();
	waringThread.join();
	errorThread.join();
}