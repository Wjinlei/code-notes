// 05-�������API.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"


int _tmain(int argc, _TCHAR* argv[])
{
	HANDLE hProcess; //HANDLE ��ʵ����DWORDֻ������WIN32��΢�������һ���µ����ֽ�HANDLE,���ڱ�����Ǿ��

	/*
	�����������,����һ�����̵�PID,д��OpenProcess�ĵ���������
	*/

	//OpenProcess����������һ������
	/*
	HANDLE OpenProcess(
		DWORD dwDesiredAccess,  // �򿪵Ľ���ϣ��ӵ��ʲôȨ��,����Ȩ����ο�MSDN API�ĵ�
		BOOL bInheritHandle,    // �Ƿ������ӽ��̼̳иý��̵��ں˶���
		DWORD dwProcessId       // PID
	);
	*/
	hProcess = OpenProcess(PROCESS_ALL_ACCESS,FALSE,0xdac); 

	//TerminateProcess���API������������ֹ�������̵�
	/*
	BOOL TerminateProcess(
		HANDLE hProcess, // ���̾��
		UINT uExitCode   // ���̵��˳�ԭ��exit code
	);
	*/
	if(!TerminateProcess(hProcess,1))
	{
		printf("��ֹ����ʧ��: %d\n",GetLastError());
	}

	/*
	DWORD GetModuleFileName(
		HMODULE hModule,    // handle to module
		LPTSTR lpFilename,  // path buffer
		DWORD nSize         // size of buffer
	);
	*/
	WCHAR strModule[256];
	GetModuleFileName(NULL,strModule,256); //�õ���ǰ��ģ��·��,˵���˾��ǵ�ǰ���е�exe���ڵ�·��
	wprintf(strModule);
	getchar();

	/*
	DWORD GetCurrentDirectory(
		DWORD nBufferLength,  // buffer�ĳ���
		LPTSTR lpBuffer       // buffer
	);
	*/
	WCHAR strWork[1000];
	int i = 1000;
	GetCurrentDirectory(1000,strWork); //�õ���ǰ�Ĺ���·��,����·���ǿ��Ըĵ�,����·���Ǵ���������̵�"��"��д��
	wprintf(strWork);

	getchar();
	return 0;
}

