// Main.cpp : 定义控制台应用程序的入口点。
//

// 互斥体也是用来解决安全问题的,它是多进程之间访问同一个内核级临界资源时使用的"锁",它是一个内核级对象

#include "stdafx.h"

// 相关API
/*
创建互斥体
HANDLE CreateMutex(
	LPSECURITY_ATTRIBUTES lpMutexAttributes,  // 安全描述符
	BOOL bInitialOwner,                       // 指定互斥体对象的初始所有者。
	LPCTSTR lpName                            // 互斥体名字,随便写
);

关于第二个参数 bInitialOwner 详解:
如果此值为TRUE,则调用者线程将获得该互斥对象的所有权,此时其他进程的无法获取到该互斥体,除非调用者主动释放

否则，调用线程不会获得互斥体的所有权,此时所有进程都可以获取该互斥体,谁先拿到谁就可以用

*/
/*
关于CreateMutex函数的返回值:
如果函数执行成功,则返回一个互斥体句柄
如果这个名字的互斥体已经存在(之前被创建过),那么返回该互斥体的句柄,并且可以通过GetLastError获取到错误为ERROR_ALREADY_EXISTS的值
其他情况的话,例如函数执行不成功,则返回NULL,可以通过GetLastError获取到错误信息
*/

int _tmain(int argc, _TCHAR* argv[])
{
	// 创建一个互斥体
	HANDLE g_hMutex = CreateMutex(NULL,FALSE,L"互斥体");

	Sleep(3000);
	// 等待互斥体
	WaitForSingleObject(g_hMutex,INFINITE);

	for(int i=0;i<10;i++)
	{
		Sleep(1000);
		printf("A进程的X线程: %d\n",i);
	}

	// 释放互斥体
	ReleaseMutex(g_hMutex);
	return 0;
}

