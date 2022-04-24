// Process-B.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

#define MAPPINGNAME "�����ļ�"

int _tmain(int argc, _TCHAR* argv[])
{
	HANDLE hMapFile;
	LPVOID lpAddr;

	// 1.��FileMapping����
	// ��ΪProcess-A�Ѿ�������FileMapping����,�������ǲ���Ҫ�ٴ���,ֱ�Ӵ򿪼���
	hMapFile = OpenFileMapping(FILE_MAP_ALL_ACCESS, FALSE, (LPCTSTR)MAPPINGNAME);
	if (hMapFile == NULL)
	{
		printf("OpenFileMapping ʧ��:%d\n", GetLastError());
		return 0;
	}

	// 2.ӳ������ҳ�������ڴ�
	lpAddr = MapViewOfFile(hMapFile, FILE_MAP_COPY, 0, 0, 0);

	// 3.��ȡ����
	DWORD dwTest1 = *(PDWORD)lpAddr;
	DWORD dwTest2 = *((PDWORD)lpAddr+0x4);
	printf("%x, %x\n", dwTest1, dwTest2);
	getchar();

	UnmapViewOfFile(lpAddr);
	CloseHandle(hMapFile);
	return 0;
}

