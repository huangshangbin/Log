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

void debugThreadFun()
{
	while (true)
	{
		DEBUG_LOG(consoleLog, "huangshangbin debug");
	}
}

void infoThreadFun()
{
	while (true)
	{
		consoleLog.info("huangshangbin info");
	}
}

void waringThreadFun()
{
	while (true)
	{
		consoleLog.waring("huangshangbin waring");
	}
}

void errorThreadFun()
{
	while (true)
	{
		consoleLog.error("huangshangbin error");
	}
}


void multiThreadConsoleLog()
{
	thread debugThread(debugThreadFun);
	thread infoThread(infoThreadFun);
	thread waringThread(waringThreadFun);
	thread errorThread(errorThreadFun);

	debugThread.join();
	infoThread.join();
	waringThread.join();
	errorThread.join();
}