#include "stdafx.h"
#include "MappingFile.h"

#define MAPPINGNAME "�����ļ�"

DWORD MappingFile(LPCTSTR lpcFile)
{
	HANDLE hFile;
	HANDLE hMapFile;
	LPVOID lpAddr;

	// 1.�õ��ļ����
	hFile = CreateFile(lpcFile, GENERIC_READ|GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		printf("CreateFileʧ�� :%d\n", GetLastError());
		return 0;
	}

	// 2.����FileMapping����
	hMapFile = CreateFileMapping(hFile, NULL, PAGE_READWRITE, 0, 0, (LPCTSTR)MAPPINGNAME);
	if (hMapFile == NULL)
	{
		printf("CreateFileMapping ʧ��:%d\n", GetLastError());
		CloseHandle(hFile);
		return 0;
	}

	// 3.ӳ������ҳ�������ڴ�
	lpAddr = MapViewOfFile(hMapFile, FILE_MAP_COPY, 0, 0, 0); // FILE_MAP_ALL_ACCESS,  FILE_MAP_COPY
	if (lpAddr == NULL)
	{
		printf("MapViewOfFile ʧ��:%d\n", GetLastError());
		CloseHandle(hMapFile);
		CloseHandle(hFile);
		return 0;
	}

	// �������Ϳ��Զ�д�ļ���,��������Լ����ڴ�һ��

	// ���ļ�
	DWORD dwTest1 = *(PDWORD)lpAddr; // ���ļ��Ŀ�ʼ�ĵط�
	DWORD dwTest2 = *((PDWORD)lpAddr+0x4); // ���ļ��Ŀ�ʼ�ĵط�+ƫ��
	printf("%x, %x\n", dwTest1, dwTest2);
	getchar();
	// д�ļ�
	//*(PDWORD)lpAddr = 0x41414141; // д��AAAA
	//printf("д��: %x\n", *(PDWORD)lpAddr);
	// ǿ��ˢ�»���
	//FlushViewOfFile(((PDWORD)lpAddr), 4);

	// 4.�ر���Դ
	UnmapViewOfFile(lpAddr);
	CloseHandle(hMapFile);
	CloseHandle(hFile);
	return 0;
}

/*
���� FILE_MAP_COPY(д����):

����֪���ļ�ӳ����Ա�����,��ô����������й���ͬһ���ļ�, ���һ�����̸����ļ�,����һ�����̾ͻ���Ӱ��
������֪�����ǵĽ��ж���һЩϵͳ�ṩ��dll, ����kernel32.dll��user32.dll��ntdll.dll �ȵ�,��Щdllÿ��
���̶�Ҫʹ��,��ô����ϵͳ��Ϊÿ�����̶�Ϊ��Щdll�����ڴ���? ���ǿ϶�����,��Ϊ������̫�˷��ڴ���,����
ϵͳҲ��ʹ�õ��ڴ�ӳ���ļ��ķ���,��ÿ�����̶�ӳ��һ�ݹ��õ�dll����������������˵��,��Ҷ��õ���ͬһ��
dll,��ô��һ�����������������,���������̲�����Ӱ������? ������Σ������? ��,���������������Ҫ����
FILE_MAP_COPY(д����)��

FILE_MAP_COPY(д����):
����Ҫд��ʱ��,����.
����Ҫ�ĵ�ʱ��,�͸ĵĲ���ԭ�����ڴ���,���Ǹĵ������Ƶ���һ��.���ֻӰ���Լ�,�Ա��˾Ͳ�Ӱ����
*/