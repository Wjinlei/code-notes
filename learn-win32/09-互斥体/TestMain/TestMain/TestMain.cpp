// TestMain.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"


int _tmain(int argc, _TCHAR* argv[])
{
	// 获得上一个进程创建的互斥体
	HANDLE g_hMutex = CreateMutex(NULL,FALSE,L"互斥体"); //这里实际上并没有重新创建互斥体,而是使用前面进程创建的互斥体(因为互斥体名字相同)

	// 等待互斥体
	WaitForSingleObject(g_hMutex,INFINITE);

	for(int i=0;i<10;i++)
	{
		Sleep(1000);
		printf("B进程的X线程: %d\n",i);
	}

	//释放互斥体
	ReleaseMutex(g_hMutex);
	return 0;
}

