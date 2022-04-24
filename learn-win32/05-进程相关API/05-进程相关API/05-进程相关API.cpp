// 05-进程相关API.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"


int _tmain(int argc, _TCHAR* argv[])
{
	HANDLE hProcess; //HANDLE 其实就是DWORD只不过在WIN32中微软给了它一个新的名字叫HANDLE,用于标记它是句柄

	/*
	打开任务管理器,记下一个进程的PID,写在OpenProcess的第三个参数
	*/

	//OpenProcess函数用来打开一个进程
	/*
	HANDLE OpenProcess(
		DWORD dwDesiredAccess,  // 打开的进程希望拥有什么权利,具体权限请参考MSDN API文档
		BOOL bInheritHandle,    // 是否允许子进程继承该进程的内核对象
		DWORD dwProcessId       // PID
	);
	*/
	hProcess = OpenProcess(PROCESS_ALL_ACCESS,FALSE,0xdac); 

	//TerminateProcess这个API函数是用来终止其他进程的
	/*
	BOOL TerminateProcess(
		HANDLE hProcess, // 进程句柄
		UINT uExitCode   // 进程的退出原因exit code
	);
	*/
	if(!TerminateProcess(hProcess,1))
	{
		printf("终止进程失败: %d\n",GetLastError());
	}

	/*
	DWORD GetModuleFileName(
		HMODULE hModule,    // handle to module
		LPTSTR lpFilename,  // path buffer
		DWORD nSize         // size of buffer
	);
	*/
	WCHAR strModule[256];
	GetModuleFileName(NULL,strModule,256); //得到当前的模块路径,说白了就是当前运行的exe所在的路径
	wprintf(strModule);
	getchar();

	/*
	DWORD GetCurrentDirectory(
		DWORD nBufferLength,  // buffer的长度
		LPTSTR lpBuffer       // buffer
	);
	*/
	WCHAR strWork[1000];
	int i = 1000;
	GetCurrentDirectory(1000,strWork); //得到当前的工作路径,工作路径是可以改的,工作路径是创建这个进程的"人"填写的
	wprintf(strWork);

	getchar();
	return 0;
}

