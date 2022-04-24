// 互斥体的一个防多开应用(执行目录里的.exe看能不能开两个).cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"


int _tmain(int argc, _TCHAR* argv[])
{
	// 创建一个互斥体
	HANDLE g_hMutex = CreateMutex(NULL,FALSE,L"互斥体");

	// 获得状态码
	DWORD errorInfo = GetLastError();

	if(g_hMutex) // 如果创建成功
	{
		if(ERROR_ALREADY_EXISTS == errorInfo) //判断互斥体是不是第一次创建,如果不是,则退出进程。
		{
			ReleaseMutex(g_hMutex);
			return 0;
		}
	}else //否则如果某种原因导致互斥体创建失败,那么直接退出程序
	{
		printf("创建失败,程序退出!\n");
		ReleaseMutex(g_hMutex);
		return 0;
	}

	// 如果创建成功,并且是第一次创建,则继续执行
	while(1)
	{
		Sleep(1000);
		printf("程序执行中...\n");
	}
	return 0;
}

