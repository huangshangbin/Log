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
	FileLog fileLog;


	LogDateTime curDateTime;
	curDateTime.setUseCurTime();

	cout << curDateTime.toString() << endl;

	int a;
	cin >> a;

	return 0;
}