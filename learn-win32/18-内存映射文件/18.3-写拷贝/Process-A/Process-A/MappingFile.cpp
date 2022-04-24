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
	//DWORD dwTest1 = *(PDWORD)lpAddr; // 读文件的开始的地方
	//DWORD dwTest2 = *((PDWORD)lpAddr+0x4); // 读文件的开始的地方+偏移
	//printf("%x, %x\n", dwTest1,dwTest2);
	//getchar();
	// 写文件
	*(PDWORD)lpAddr = 0x41414141; // 写入AAAA
	printf("Process-A写入: %x\n", *(PDWORD)lpAddr);
	getchar();
	// 强制刷新缓存
	//FlushViewOfFile(((PDWORD)lpAddr), 4);

	// 4.关闭资源
	UnmapViewOfFile(lpAddr);
	CloseHandle(hMapFile);
	CloseHandle(hFile);
	return 0;
}