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
	while (true)
	{
		DEBUG_LOG(consoleLog, "huangshangbin debug");
	}
}

void infoConsoleLogThreadFun()
{
	while (true)
	{
		consoleLog.info("huangshangbin info");
	}
}

void waringConsoleLogThreadFun()
{
	while (true)
	{
		consoleLog.waring("huangshangbin waring");
	}
}

void errorConsoleLogThreadFun()
{
	while (true)
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