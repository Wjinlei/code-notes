// 04-以挂起的方式创建进程.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

BOOL CreateChildProcess(PTCHAR szModuleName, PTCHAR szCommandLine)
{
	STARTUPINFO si;
	PROCESS_INFORMATION pi;

	ZeroMemory(&si, sizeof(si));
	ZeroMemory(&pi, sizeof(pi));

	if(!CreateProcess(szModuleName,szCommandLine,NULL,NULL,FALSE,CREATE_SUSPENDED,NULL,NULL,&si,&pi))
	{
		printf("Create Proecss Error: %d \n",GetLastError());
		return FALSE;
	}
	printf("PID: %d\n",pi.dwProcessId);
	printf("进程句柄: %x\n",pi.hProcess);

	/* 
	在这里插入我们要执行的代码,因为进程执行到这里被挂起了,
	所以子进程释放了执行权,这时候主线程又得到了执行权,所以
	在这里我们可以写我们自己的代码。达到提前注入的目的。
	*/
	for(int i=0;i<5;i++)
	{
		Sleep(1000);
		printf("程序被我们做了手脚,执行了我们的代码\n");
	}

	// 唤醒线程
	ResumeThread(pi.hThread);

	// 释放句柄
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);

	return TRUE;
}

int _tmain(int argc, _TCHAR* argv[])
{
	PTSTR szAppName = TEXT("C://Program Files (x86)//Google//Chrome//Application//chrome.exe");
	PTSTR szCmdLine = TEXT("chrome.exe https://www.baidu.com");
	CreateChildProcess(szAppName, szCmdLine);
	getchar();
	return 0;
}

