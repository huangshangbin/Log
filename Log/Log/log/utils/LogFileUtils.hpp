#pragma once

#include "LogStringUtils.hpp"

#include <string>
#include <io.h>

#include <iostream>
using namespace std;

class LogFileUtils
{
public:
	static string getFileOrDirName(string path)
	{
		int index;
		for (int i = path.length(); i > 0; i--)
		{
			if (i == 0)
			{
				return path;
			}

			if (path[i] == '\\')
			{
				index = i;
				break;
			}
		}

		string result = LogStringUtils::getStringUsePos(path, index + 1, path.length());
		return result;
	}

	static string getPreviousLayerPath(string path)
	{
		int index;
		for (int i = path.length(); i > 0; i--)
		{
			if (i == 0)
			{
				return path;
			}

			if (path[i] == '\\')
			{
				index = i;
				break;
			}
		}

		return LogStringUtils::getStringUsePos(path, 0, index - 1);
	}

	static deque<string> getPathFirstLayerFilePath(string srcPath)
	{
		deque<string> filePathList;

		string path = srcPath + "\\*.*";

		_finddata_t findData;
		intptr_t findHandle = _findfirst(path.c_str(), &findData);
		intptr_t flag = findHandle;

		while (flag != -1)
		{
			if (findData.attrib == _A_ARCH)
			{
				filePathList.push_back(srcPath + "\\" + findData.name);
			}

			flag = _findnext(findHandle, &findData);
		}

		_findclose(findHandle);

		return std::move(filePathList);
	}

//file
public:
	static long getFileSize(string filePath)
	{
		GET_FILEEX_INFO_LEVELS fInfoLevelId = GetFileExInfoStandard;
		WIN32_FILE_ATTRIBUTE_DATA fileInformation{ 0 };

		GetFileAttributesEx(filePath.c_str(), fInfoLevelId, &fileInformation);

		return fileInformation.nFileSizeLow;
	}


//dir
public:
	static void recursiveCreateDir(string dirPath)
	{
		deque<string> dirPathList = LogStringUtils::splitString(dirPath, "\\");

		string createDirPath = dirPathList[0];
		for (int i = 1; i < dirPathList.size(); i++)
		{
			createDirPath = createDirPath + "\\" + dirPathList[i];

			CreateDirectory(createDirPath.c_str(), NULL);
		}
	}



};
