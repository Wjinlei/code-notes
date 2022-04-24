// 10-事件.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

/*
在开始学事件之前,先说说它有什么用?
答:
如果用之前学过的知识,临界区和互斥体,你能不能做一个线程同步的案例
比如做一个生产者生产一个,消费者消费一个的案例。

什么是线程同步?
线程同步 = 互斥 + 有序
*/

HANDLE g_hSet; // 生产者事件
HANDLE g_hClean; // 消费者事件
int g_ReadyProductNumber = 10; // 准备生产的产品个数
int g_AlreadyProductNumber = 0; // 已生产的产品个数

// 生产者线程
DWORD WINAPI ProducerThread(LPVOID pM)
{
	for (int i=0; i<g_ReadyProductNumber; i++)
	{	
		// 等待g_hSet事件
		WaitForSingleObject(g_hSet,INFINITE);
		g_AlreadyProductNumber++;
		printf("生产者生产了: %d 个\n",g_AlreadyProductNumber);
		SetEvent(g_hClean); // 设置g_hClean事件可以被wait
	}
	return 0;
}

// 消费者线程
DWORD WINAPI ConsumerThread(LPVOID pM)
{
	for (int i=0; i<=g_AlreadyProductNumber;NULL)
	{	
		// 等待g_hClean事件
		WaitForSingleObject(g_hClean,INFINITE);
		g_AlreadyProductNumber--;
		printf("消费者消费了1个,还剩 %d 个\n",g_AlreadyProductNumber);
		SetEvent(g_hSet); // 设置g_hSet事件可以被wait
	}
	return 0;
}


int _tmain(int argc, _TCHAR* argv[])
{
	/*
	HANDLE WINAPI CreateEvent(
	__in_opt  LPSECURITY_ATTRIBUTES lpEventAttributes, // 安全描述符
	__in      BOOL bManualReset, // 事件类型,TRUE=通知类型,FALSE=互斥类型
	__in      BOOL bInitialState, // 创建出来的Event是否可以被wait,TRUE表示可以,FALSE表示不可以
	__in_opt  LPCTSTR lpName // 当前的Event的名字,如果只在当前的进程里用,就不需要起名字
	);

	第二个参数: bManualReset详解：
	什么是互斥类型?
	答: 其中一个wait到以后,另一个只能处于阻塞状态
	就是说SetEvent会把对方的bInitialState参数改成TRUE,同时会把自己的bInitialState改成FALSE
	这样就会造成,唤醒对方,自己变成阻塞状态。

	什么是通知类型?
	答: 其中一个wait到以后,另一个也可以wait到(前提是可以被wait)
	就是说SetEvent会把对方的bInitialState参数改成TRUE,同时自己的bInitialState保持不变
	这样就会造成,唤醒对方,自己也不阻塞
	*/

	//创建事件
	g_hSet = CreateEvent(NULL,FALSE,TRUE,NULL);
	g_hClean = CreateEvent(NULL,FALSE,FALSE,NULL);

	//创建线程
	HANDLE aThreadArray[2];
	aThreadArray[0] = ::CreateThread(NULL,0,ProducerThread,NULL,0,NULL);
	aThreadArray[1] = ::CreateThread(NULL,0,ConsumerThread,NULL,0,NULL);

	//等待2个线程都结束后,主线程再往下执行
	WaitForMultipleObjects(2,aThreadArray,TRUE,INFINITE);
	CloseHandle(aThreadArray[0]);
	CloseHandle(aThreadArray[1]);
	CloseHandle(g_hSet);
	CloseHandle(g_hClean);

	getchar();
	return 0;

	/*
	总结: 事件就是用来解决线程同步问题的(互斥 + 有序)
	*/
}

