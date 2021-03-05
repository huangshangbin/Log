#include <example/ConsoleLogExample.hpp>
#include <example/FileLogExample.hpp>


#include <log/QuickFileLog.hpp>






int main()
{
	//multiThreadConsoleLog();

	
	//multiThreadFileLog();

	QuickFileLog* quickFileLog = new QuickFileLog();
	quickFileLog->setWorkDir("E:\\tempDir");

	unsigned int i = 0;
	while (true)
	{
		quickFileLog->info("huangshangbinzxc");

		if ((i % 10000) == 0)
		{
			cout << "添加日志数 " << i << endl;
		}
		i++;

		Sleep(1000);
	}

	delete quickFileLog;


	cout << "complete" << endl;
	int a;
	cin >> a;

	return 0;
}