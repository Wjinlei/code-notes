// 08-线程安全问题-临界区.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

/*
如何解决线程安全问题? 可以使用临界区!

什么是临界资源? 
答: 临界资源就是一次仅允许一个线程使用的资源

什么是临界区? 
答: 访问临界资源的那段代码称为临界区

临界区是如何避免线程安全问题的?
答:
A线程获取令牌后,B线程就获取不到令牌(除非A线程主动释放)
得到令牌的线程才可以访问临界资源,否则无法访问

如何使用临界区?
答:
1. 创建CRITICAL_SECTION cs全局变量(令牌)
2. InitializeCriticalSection(&cs); 初始化令牌
3. EnterCriticalSection(&cs); 进入临界区
4. 使用临界资源
5. LeaveCriticalSection(&cs); 离开临界区
*/

CRITICAL_SECTION cs; // 创建临界区全局变量(令牌)
int g_dwTickets = 10; // 票数(临界资源)

// 线程函数
DWORD WINAPI MyFirstThreadProc(LPVOID lpParameter)
{	
	/* 以下是不合理的使用临界区的错误示范

	while(g_dwTickets > 0)
	{
		EnterCriticalSection(&cs); //进入临界区
		printf("还有: %d 张票\n",g_dwTickets);
		g_dwTickets--;
		printf("卖出一张,还有: %d 张\n",g_dwTickets);
		LeaveCriticalSection(&cs); //离开临界区
	}

	*/

	// 合理的临界区代码应该是把对于全局变量的读写判断所有的逻辑全放到临界区里来实现,这样才是真正的安全
	EnterCriticalSection(&cs); //进入临界区,获取令牌

	// 从这开始就是临界区,g_dwTickets就是临界资源
	while(g_dwTickets > 0) // 把对于全局变量的读写判断所有的逻辑全放到临界区里来实现,这样才是真正的安全
	{
		printf("还有: %d 张票\n",g_dwTickets);
		g_dwTickets--;
		printf("卖出一张,还有: %d 张\n",g_dwTickets);
	}// 到这里临界区就结束

	LeaveCriticalSection(&cs); //离开临界区,释放令牌
	return 0;
}

int _tmain(int argc, _TCHAR* argv[])
{
	DWORD dwResult1;
	DWORD dwResult2;
	HANDLE aThreadHandles[2];
	// 初始化令牌
	InitializeCriticalSection(&cs);

	// 创建一个新线程
	aThreadHandles[0] = CreateThread(NULL,0,MyFirstThreadProc,NULL,0,NULL);

	// 创建一个新线程
	aThreadHandles[1] = CreateThread(NULL,0,MyFirstThreadProc,NULL,0,NULL);

	// 等待线程执行结束
	WaitForMultipleObjects(2,aThreadHandles,TRUE,INFINITE);

	// 线程执行完毕
	GetExitCodeThread(aThreadHandles[0],&dwResult1);
	GetExitCodeThread(aThreadHandles[1],&dwResult2);
	printf("Thread1ExitCode: %d, Thread2ExitCode: %d\n",dwResult1,dwResult2);

	getchar();
	return 0;
}

