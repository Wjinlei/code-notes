// Process-B.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#define MAPPINGNAME "共享文件"

int _tmain(int argc, _TCHAR* argv[])
{
	HANDLE hMapFile;
	LPVOID lpAddr;

	// 1.打开FileMapping对象
	// 因为Process-A已经创建了FileMapping对象,所以我们不需要再创建,直接打开即可
	hMapFile = OpenFileMapping(FILE_MAP_ALL_ACCESS, FALSE, (LPCTSTR)MAPPINGNAME);
	if (hMapFile == NULL)
	{
		printf("OpenFileMapping 失败:%d\n", GetLastError());
		return 0;
	}

	// 2.映射物理页到虚拟内存
	lpAddr = MapViewOfFile(hMapFile, FILE_MAP_ALL_ACCESS, 0, 0, 0);

	// 3.读取数据
	DWORD dwTest1 = *(PDWORD)lpAddr;
	DWORD dwTest2 = *((PDWORD)lpAddr+0x4);
	printf("%x, %x\n", dwTest1, dwTest2);
	getchar();

	UnmapViewOfFile(lpAddr);
	CloseHandle(hMapFile);
	return 0;
}

