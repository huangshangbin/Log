#pragma once

#include "LogDateTime.hpp"
#include "LogBase.hpp"


class FileLogBase : public LogBase
{
protected:
	string m_workDir;

public:
	FileLogBase() : LogBase()
	{
		m_workDir = "";
	}

	~FileLogBase() {}

public:
	string getNewestLogDir(LogDateTime& curTime)
	{
		return m_workDir + "\\" + curTime.getYear() + "\\" + curTime.getMonth() + "\\" + curTime.getDay();
	}
};
