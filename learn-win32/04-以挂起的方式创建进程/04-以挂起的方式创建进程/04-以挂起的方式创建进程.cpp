// 04-�Թ���ķ�ʽ��������.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

BOOL CreateChildProcess(PTCHAR szModuleName, PTCHAR szCommandLine)
{
	STARTUPINFO si;
	PROCESS_INFORMATION pi;

	ZeroMemory(&si, sizeof(si));
	ZeroMemory(&pi, sizeof(pi));

	if(!CreateProcess(szModuleName,szCommandLine,NULL,NULL,FALSE,CREATE_SUSPENDED,NULL,NULL,&si,&pi))
	{
		printf("Create Proecss Error: %d \n",GetLastError());
		return FALSE;
	}
	printf("PID: %d\n",pi.dwProcessId);
	printf("���̾��: %x\n",pi.hProcess);

	/* 
	�������������Ҫִ�еĴ���,��Ϊ����ִ�е����ﱻ������,
	�����ӽ����ͷ���ִ��Ȩ,��ʱ�����߳��ֵõ���ִ��Ȩ,����
	���������ǿ���д�����Լ��Ĵ��롣�ﵽ��ǰע���Ŀ�ġ�
	*/
	for(int i=0;i<5;i++)
	{
		Sleep(1000);
		printf("�������������ֽ�,ִ�������ǵĴ���\n");
	}

	// �����߳�
	ResumeThread(pi.hThread);

	// �ͷž��
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);

	return TRUE;
}

int _tmain(int argc, _TCHAR* argv[])
{
	PTSTR szAppName = TEXT("C://Program Files (x86)//Google//Chrome//Application//chrome.exe");
	PTSTR szCmdLine = TEXT("chrome.exe https://www.baidu.com");
	CreateChildProcess(szAppName, szCmdLine);
	getchar();
	return 0;
}

