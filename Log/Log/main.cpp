#include <example/ConsoleLogExample.hpp>
#include <example/FileLogExample.hpp>


#include <log/QuickFileLog.hpp>






int main()
{
	//multiThreadConsoleLog();

	
	//multiThreadFileLog();

	QuickFileLog* quickFileLog = new QuickFileLog();

	for (int i = 0; i < 1000000; i++)
	{
		quickFileLog->info("huangshangbinzxc");

		if ((i % 10000) == 0)
		{
			cout << "添加日志数 " << i << endl;
		}
	}

	delete quickFileLog;


	cout << "complete" << endl;
	int a;
	cin >> a;

	return 0;
}