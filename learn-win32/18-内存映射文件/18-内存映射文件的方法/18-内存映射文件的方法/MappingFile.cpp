#include "stdafx.h"
#include "MappingFile.h"

#define MAPPINGNAME "共享文件"

DWORD MappingFile(LPCTSTR lpcFile)
{
	HANDLE hFile;
	HANDLE hMapFile;
	LPVOID lpAddr;

	// 1.得到文件句柄
	hFile = CreateFile(lpcFile, GENERIC_READ|GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		printf("CreateFile失败 :%d\n", GetLastError());
		return 0;
	}

	// 2.创建FileMapping对象
	hMapFile = CreateFileMapping(hFile, NULL, PAGE_READWRITE, 0, 0, (LPCTSTR)MAPPINGNAME);
	if (hMapFile == NULL)
	{
		printf("CreateFileMapping 失败:%d\n", GetLastError());
		CloseHandle(hFile);
		return 0;
	}

	// 3.映射物理页到虚拟内存
	lpAddr = MapViewOfFile(hMapFile, FILE_MAP_COPY, 0, 0, 0); // FILE_MAP_ALL_ACCESS,  FILE_MAP_COPY
	if (lpAddr == NULL)
	{
		printf("MapViewOfFile 失败:%d\n", GetLastError());
		CloseHandle(hMapFile);
		CloseHandle(hFile);
		return 0;
	}

	// 接下来就可以读写文件了,就像操作自己的内存一样

	// 读文件
	DWORD dwTest1 = *(PDWORD)lpAddr; // 读文件的开始的地方
	DWORD dwTest2 = *((PDWORD)lpAddr+0x4); // 读文件的开始的地方+偏移
	printf("%x, %x\n", dwTest1, dwTest2);
	getchar();
	// 写文件
	//*(PDWORD)lpAddr = 0x41414141; // 写入AAAA
	//printf("写入: %x\n", *(PDWORD)lpAddr);
	// 强制刷新缓存
	//FlushViewOfFile(((PDWORD)lpAddr), 4);

	// 4.关闭资源
	UnmapViewOfFile(lpAddr);
	CloseHandle(hMapFile);
	CloseHandle(hFile);
	return 0;
}

/*
关于 FILE_MAP_COPY(写拷贝):

我们知道文件映射可以被共享,那么如果两个进行共享同一个文件, 如果一个进程改了文件,那另一个进程就会受影响
那我们知道我们的进行都有一些系统提供的dll, 例如kernel32.dll、user32.dll、ntdll.dll 等等,这些dll每个
进程都要使用,那么操作系统会为每个进程都为这些dll申请内存吗? 答案是肯定不会,因为这样做太浪费内存了,操作
系统也是使用的内存映射文件的方法,把每个进程都映射一份共用的dll。但是我们上面又说了,大家都用的是同一份
dll,那么另一个进程如果把它改了,那其他进程不是受影响了吗? 这岂不是危险了吗? 答,这个就是我们现在要讲的
FILE_MAP_COPY(写拷贝)。

FILE_MAP_COPY(写拷贝):
当你要写的时候,拷贝.
当你要改的时候,就改的不是原来的内存了,而是改的它复制的那一份.因此只影响自己,对别人就不影响了
*/