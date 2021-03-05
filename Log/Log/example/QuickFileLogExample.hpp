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
