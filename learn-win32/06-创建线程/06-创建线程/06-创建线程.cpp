// 06-创建线程.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

// 线程函数的格式
DWORD WINAPI ThreadProc(LPVOID lpParameter)
{
	// 你可以传入任意类型的指针,只要在这里转型即可
	int* p = (int*)lpParameter;
	for(int i=0;i<*p;i++)
	{
		Sleep(1000);
		printf("+++++++ %d\n",i);
	}
	return 0;
}

int _tmain(int argc, _TCHAR* argv[])
{
	HANDLE hThread;
	
	/*
	这里需要注意一点,在传递参数时,必须要保证线程函数执行的时候
	它所用到的参数的栈没有被回收,也就是说必须要保证线程在main
	函数之前执行完,比如,你把下面的n=10改成100,你看它能执行100次吗?
	*/

	int n = 10;

	// 通过CreateThread函数来创建线程
	/*
	HANDLE CreateThread( //这个函数返回的是HANDLE(句柄)
		LPSECURITY_ATTRIBUTES lpThreadAttributes, // 安全描述符,它是一个结构体的指针
		SIZE_T dwStackSize,                       // 初始堆栈大小
		LPTHREAD_START_ROUTINE lpStartAddress,    // 真正要执行的代码在哪(回调函数)
		LPVOID lpParameter,                       // 线程需要的参数,如果没有就写NULL
		DWORD dwCreationFlags,                    // 创建线程的标识符,0表示创建后立即执行,CREATE_SUSPENDED表示以挂起的形式创建,详细请参阅 https://msdn.microsoft.com/en-us/library/windows/desktop/ms684863(v=vs.85).aspx
		LPDWORD lpThreadId                        // 这个参数是个OUT类型的参数,返回刚刚创建的线程的线程ID
	);
	*/

	// 安全描述符
	/*
	typedef struct _SECURITY_ATTRIBUTES { 
		DWORD  nLength;				 //当前结构体的长度
		LPVOID lpSecurityDescriptor; //这个指针指向一个结构体,主要是控制当前这个内核对象,给谁用,不给谁用,谁能关闭,谁能访问主要是用来描述这些信息的
		BOOL   bInheritHandle;		 //当前的内核对象是否运行被继承
	} SECURITY_ATTRIBUTES, *PSECURITY_ATTRIBUTES; 
	*/

	hThread = CreateThread(NULL,0,ThreadProc,(LPVOID)&n,0,NULL);

	// 线程这个内核并不是CloseHandle就会被清理
	/*
	线程被清理的两个必要条件:
	1.线程计数器为0
	2.线程代码执行完毕
	*/
	CloseHandle(hThread);

	for(int i=0;i<20;i++)
	{
		Sleep(500);
		printf("--------%d\n",i);
	}
	return 0;
}

