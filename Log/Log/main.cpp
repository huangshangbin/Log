#include <log/ConsoleLog.hpp>
#include <log/FileLog.hpp>




void consoleLogTest()
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


int main()
{
	//consoleLogTest();

	FileLog fileLog;
	fileLog.setWorkDir("E:\\tempDir");

	for(int i = 0; i < 100000; i++)
	{
		fileLog.info("huangshangbin ----  " + std::to_string(i));
	}
	fileLog.info("huang");

	int a;
	cin >> a;

	return 0;
}