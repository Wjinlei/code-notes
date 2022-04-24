// 03-创建进程.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

/*
什么是内核对象?
查询MSDN帮助文档中CloseHandle函数,如下这些都是内核对象

Access token
Communications device
Console input
Console screen buffer
Event //事件
File //文件
File mapping //文件映射
I/O completion port
Job
Mailslot
Memory resource notification
Mutex  //互斥体
Named pipe //命名管道
Pipe
Process //进程
Semaphore //信号量
Thread  //线程
Transaction
Waitable timer
Socket //网络编程时要用到

什么是句柄?
每个进程都有一个句柄表,0环的内核对象,默认操作系统是不允许3环直接访问的
所以为了解决这个问题,就出现了句柄表的概念,句柄表中存储的就是一种映射关系
它存储了0环内核对象的实际地址,当3环的程序想要访问0环的内核对象时,就先
访问这张句柄表,获取其句柄值(实际地址),这样就可以操作这个内核对象了

什么是PID?
一个进程里可以创建多个内核对象,比如说一个进程里，我创建多个线程
创建文件，创建事件等等
每一个进程都有一个ID号,这个ID号就是PID,一个PID唯一标识一个进程

所以总结:
PID就是进程的ID号,它唯一标识一个进程
句柄就是内核对象的实际地址,想要操作内核对象就必须获取其句柄
*/

/*
什么是进程?
进程指的是运行中的一个程序。换句话说是在内存中的一段代码

进程在操作系统中扮演一个什么角色?
答: 
为当前程序提供所需要的资源,如: 数据、代码等等
你可以把进程看成是一种空间上的概念,用现实生活
中的一个例子举例,进程就相当于是一幢房子,线程则
相当于是房子里面的人(使用这个进程的对象)
*/


/*
进程的创建过程:
1.映射exe文件(把要执行的exe文件放入一块内存中)
2.创建内核对象(EPROCESS)。
3.映射系统DLL(ntdll.dll)
4.创建一个初始线程(ETHREAD)
5.启动线程之前还要映射dll,这一次映射的dll是这个程序所用到的所有dll,而上面的ntdll是每个exe必须的dll
6.开始执行初始线程(如果创建时候指定了线程的CREATE_SUSPENDED状态则线程暂时挂起不执行)。
*/

BOOL CreateChildProcess(PTSTR szChildProcessName, PTSTR szCommandLine)
{
	// 创建进程所需要的结构体
	STARTUPINFO si;
	PROCESS_INFORMATION pi;

	// 初始化结构体
	ZeroMemory(&si, sizeof(si));
	ZeroMemory(&pi, sizeof(pi));

	// 创建进程,如果失败则打印错误代码,返回FALSE
	// 函数详细请参阅: https://msdn.microsoft.com/en-us/library/windows/desktop/ms682425(v=vs.85).aspx
	if(!CreateProcess(
		szChildProcessName, // 对象名称,你要对哪个程序创建进程
		szCommandLine, // 命令行
		NULL, // 是否可以被子进程继承进程句柄
		NULL, // 是否可以被子进程继承线程句柄
		FALSE, // 如果此参数为TRUE，则进程中的每个可继承句柄都将由新进程继承。如果该参数为FALSE，则句柄不会被继承。请注意，继承的句柄具有与原始句柄相同的值和访问权限。
		0, // 创建标识,控制优先级和创建进程的标志。有关值列表，请参阅 https://msdn.microsoft.com/en-us/library/windows/desktop/ms684863(v=vs.85).aspx
		NULL, // 是否使用父进程环境变量
		NULL, // 是否使用父进程的目录作为当前目录
		&si, // STARTUPINFO 结构体
		&pi  // PROCESS_INFORMATION 结构体
		)){
			printf("CreateChildProcess Error: %d \n",GetLastError());
			return FALSE;
	}

	//释放句柄
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
	return TRUE;
}

int _tmain(int argc, _TCHAR* argv[])
{
	PTSTR szApplicationName = TEXT("C://Program Files (x86)//Google//Chrome//Application//chrome.exe");
	PTSTR szCmdLine = TEXT("chrome.exe https://www.baidu.com");

	CreateChildProcess(szApplicationName, szCmdLine);
	getchar();

	return 0;
}

