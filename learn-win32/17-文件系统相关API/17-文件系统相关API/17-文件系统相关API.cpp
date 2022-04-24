// 17-文件系统相关API.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "FileApi.h"
#include "DirectoryAPI.h"
#include "VolumeAPI.h"

int _tmain(int argc, _TCHAR* argv[])
{
	// 创建文件
	//TestCreateFileApi();

	// 获取文件大小
	//TestGetFileSize();

	// 获取文件属性
	//TestGetFileAttributesEx();

	// 写文件
	//TestWriteFile();

	// 读取文件
	//TestReadFile();

	// 复制文件
	//TestCopyFile();

	// 删除文件
	//DeleteFile(TEXT("TestFile.txt.COPY"));

	// 查找文件
	//FindFile();

	// 创建目录
	//TestCreateDir();

	// 删除目录
	//TestDelDir();

	// 重命名目录
	//TestRenameDir();

	// 获取程序的当前目录
	//TestGetCurrDir();

	// 设置程序的当前目录
	//TestSetCurrDir();

	// 获取当前系统的卷
	//TestGetDrives();

	// 获取所在卷的盘符的字符串
	//TestGetDriveString();

	// 获取卷的类型
	//TestGetDriveType();

	// 获取卷的详细信息
	TestGetDriveInfo();


	getchar();
	return 0;
}

