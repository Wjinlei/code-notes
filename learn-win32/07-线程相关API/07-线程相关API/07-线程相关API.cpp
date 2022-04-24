// 07-线程相关API.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

// 线程函数
DWORD WINAPI ThreadProc(LPVOID lpParameter)
{
	for(int i=0;i<10;i++)
	{
		/*
		VOID Sleep(
			DWORD dwMilliseconds   // 停止时间,单位是毫秒,它只能控制当前自己的线程,让自己停下来
		);
		*/
		Sleep(500);
		printf("++++++++++++%d\n",i);
	}
	return 0;
}

int _tmain(int argc, _TCHAR* argv[])
{
	//************************************************第一段API注释************************************************
	/*
	HANDLE CreateThread(
		LPSECURITY_ATTRIBUTES lpThreadAttributes, // 安全描述符
		SIZE_T dwStackSize,                       // 初始堆栈大小
		LPTHREAD_START_ROUTINE lpStartAddress,    // 线程函数
		LPVOID lpParameter,                       // 线程参数
		DWORD dwCreationFlags,                    // 创建标识
		LPDWORD lpThreadId                        // 线程id
	);
	*/

	/*
	// 挂起线程
	DWORD SuspendThread(
		HANDLE hThread   // 线程句柄,让别人停下来
	);

	// 唤醒线程
	DWORD ResumeThread(
		HANDLE hThread   // 线程句柄,让别人跑起来
	);
	*/

	//************************************************第一段演示代码************************************************
	HANDLE hThreadArray[2];
	hThreadArray[0] = CreateThread(NULL,0,ThreadProc,NULL,0,NULL);
	hThreadArray[1] = CreateThread(NULL,0,ThreadProc,NULL,0,NULL);

	Sleep(3000);
	printf("挂起第一个线程!\n");
	// 挂起线程,一个线程可以挂起多次
	SuspendThread(hThreadArray[0]);
	SuspendThread(hThreadArray[0]);
	
	Sleep(10000);
	printf("唤醒第一个线程!\n");
	// 唤醒线程,挂起几次就必须唤醒几次
	ResumeThread(hThreadArray[0]);
	ResumeThread(hThreadArray[0]);
	getchar();

	//************************************************第二段API注释************************************************
	// 等待线程结束,任何的对象如果被等待,那么到这里都会挂起,当状态发生变更时返回.
	/*
	DWORD WaitForSingleObject(
		HANDLE hHandle,        // 对象句柄,任何内核对象都可以作为等待的对象
		DWORD dwMilliseconds   // 想等待多长时间,如果N秒内状态仍然没有发生变更,那这个函数一样会返回(超时时间)
	);
	*/

	// 等待多个线程结束
	/*
	DWORD WaitForMultipleObjects(
		DWORD nCount,             // 等待个几内核对象
		CONST HANDLE *lpHandles,  // 等待内核对象的数组
		BOOL bWaitAll,            // 等待模式,你可以指定所有的等待对象状态都发生变更的时候,这个函数才返回,或者,有任何一个内核对象状态发生变更则返回,TRUE表示所有,FALSE表示任何一个
		DWORD dwMilliseconds      // 等待时间,超时时间
	);
	*/

	// 获取线程退出代码
	/*
	BOOL GetExitCodeThread(
		HANDLE hThread,      // 线程句柄
		LPDWORD lpExitCode   // 返回状态,他是OUT类型的参数
	);
	*/
	//************************************************第二段演示代码************************************************
	//HANDLE hThreadArray[2];
	//hThreadArray[0] = CreateThread(NULL,0,ThreadProc,NULL,0,NULL);
	//hThreadArray[1] = CreateThread(NULL,0,ThreadProc,NULL,0,NULL);

	//printf("挂起第一个线程!\n");
	//SuspendThread(hThreadArray[0]);
	//
	////等10秒再唤醒第一个线程
	//Sleep(10000);
	//printf("唤醒第一个线程!\n");
	//ResumeThread(hThreadArray[0]);
	////等待第一个线程结束,主线程才会继续
	//WaitForSingleObject(hThreadArray[0],INFINITE);
	////如果这里你不wait,把上面的wait注释,看看会发生什么?
	////当然你还可以wait所有的内核对象,具体看上面API,这里我就不演示了

	//DWORD exitcode;
	//GetExitCodeThread(hThreadArray[0],&exitcode);
	//printf("ExitCodeThread: %d\n",exitcode);

	//for(int i=0;i<=9;i++)
	//{
	//	Sleep(500);
	//	printf("主线程继续....\n");
	//}
	//printf("主线程结束,请按任意键结束!");
	//getchar();

	//************************************************第三段API注释************************************************
	// 获取线程的上下文环境
	/*
	BOOL GetThreadContext(
		HANDLE hThread,            // 线程句柄
		LPCONTEXT lpContext        // 上下文结构体
	);
	*/
	// 设置线程的上下文环境
	/*
	BOOL SetThreadContext(
		HANDLE hThread,            // 线程句柄
		CONST CONTEXT *lpContext   // 上下文结构体
	);
	*/
	//************************************************第三段演示代码************************************************

	/*
	提问: 
	如果当前电脑只有一个核(单核),那么就是说它只能同时跑一个线程。
	那当跑A线程的时候,突然间由于某个原因切换到B线程,那么请问A线程怎么办?比如说A线程跑到哪里了?你的寄存器的值是什么?
	我们都知道程序跑的时候需要依赖一堆寄存器,EAX,EBX,ECX,ESP,EBP,ESI,EDI...等等乱七八糟一大堆,那你A线程跑的时候,
	突然切换到B线程了,那A线程原来的值要不要保留?

	答:
	其实每一个线程都有一个结构体,当自己被切换的时候,会把当前运行情况这些数据的值保存在这个结构体中,这个结构体就叫做CONTEXT(上下文)
	我们说的线程上下文其实就是它。
	*/
	//HANDLE hThreadArray[2];
	//hThreadArray[0] = CreateThread(NULL,0,ThreadProc,NULL,0,NULL);
	//hThreadArray[1] = CreateThread(NULL,0,ThreadProc,NULL,0,NULL);

	////要获取某一个线程的上下文,就必须先把它挂起
	//printf("挂起第一个线程!\n");
	//SuspendThread(hThreadArray[0]);

	////创建CONTEXT结构体
	//CONTEXT context;
	//context.ContextFlags = CONTEXT_INTEGER;
	////ContextFlags是微软为我们定义好的,你想要哪一段就填哪个flag
	///*
	//例如: 鼠标选择CONTEXT,按F12转到定义,比如我想要下面Edi、Esi这一段
	//E开头的,那么Flag就可以填CONTEXT_INTEGER
	////
 //   // This section is specified/returned if the
 //   // ContextFlags word contians the flag CONTEXT_INTEGER.
 //   //

 //   DWORD   Edi;
 //   DWORD   Esi;
 //   DWORD   Ebx;
 //   DWORD   Edx;
 //   DWORD   Ecx;
 //   DWORD   Eax;
	//*/
	////获取线程上下文
	//GetThreadContext(hThreadArray[0],&context);
	//printf("EAX: %x EBX: %x ECX: %x EDX: %x\n",context.Eax,context.Ebx,context.Ecx,context.Edx);

	///*
	////这个值你可以改,通过SetThreadContext API
	//context.Eax = 0x00000000;
	//context.Ebx = 0x00000001;
	//context.Ecx = 0x00000002;
	//context.Edx = 0x00000003;
	//SetThreadContext(hThreadArray[0],&context);
	//printf("EAX: %x EBX: %x ECX: %x EDX: %x\n",context.Eax,context.Ebx,context.Ecx,context.Edx);
	//*/
	//ResumeThread(hThreadArray[0]);
	////释放资源
	//CloseHandle(hThreadArray[0]);
	//CloseHandle(hThreadArray[1]);
	//getchar();
	return 0;
}

