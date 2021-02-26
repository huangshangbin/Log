#include <log/ConsoleLog.hpp>



int main()
{
	cout << "src log" << endl;

	ConsoleLog consoleLog;

	consoleLog.setLevel(DEBUG);

	DEBUG_LOG(consoleLog, "huangshangbin debug");

	
	cout << "----------------"<<endl;
	consoleLog.info("huangshangbin info");
	
	cout << "----------------"<<endl;
	consoleLog.waring("huangshangbin waring");

	cout << "----------------" << endl;
	consoleLog.error("huangshangbin error");

	int a;
	cin >> a;

	return 0;
}