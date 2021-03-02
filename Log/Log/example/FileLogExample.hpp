#pragma once

#include <log/FileLog.hpp>
#include <thread>

//  simpleFileLog  -----------------------------
void simpleFileLog()
{
	FileLog fileLog;
	fileLog.setWorkDir("E:\\tempDir");

	for (int i = 0; i < 1000; i++)
	{
		DEBUG_LOG(fileLog, "huangshangbin ----  " + std::to_string(i));
		fileLog.info("huangshangbin ----  " + std::to_string(i));
		fileLog.waring("huangshangbin ----  " + std::to_string(i));
		fileLog.error("huangshangbin ----  " + std::to_string(i));

		cout << i << endl;
	}
}