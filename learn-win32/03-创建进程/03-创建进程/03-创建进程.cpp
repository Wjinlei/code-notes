// 03-��������.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

/*
ʲô���ں˶���?
��ѯMSDN�����ĵ���CloseHandle����,������Щ�����ں˶���

Access token
Communications device
Console input
Console screen buffer
Event //�¼�
File //�ļ�
File mapping //�ļ�ӳ��
I/O completion port
Job
Mailslot
Memory resource notification
Mutex  //������
Named pipe //�����ܵ�
Pipe
Process //����
Semaphore //�ź���
Thread  //�߳�
Transaction
Waitable timer
Socket //������ʱҪ�õ�

ʲô�Ǿ��?
ÿ�����̶���һ�������,0�����ں˶���,Ĭ�ϲ���ϵͳ�ǲ�����3��ֱ�ӷ��ʵ�
����Ϊ�˽���������,�ͳ����˾����ĸ���,������д洢�ľ���һ��ӳ���ϵ
���洢��0���ں˶����ʵ�ʵ�ַ,��3���ĳ�����Ҫ����0�����ں˶���ʱ,����
�������ž����,��ȡ����ֵ(ʵ�ʵ�ַ),�����Ϳ��Բ�������ں˶�����

ʲô��PID?
һ����������Դ�������ں˶���,����˵һ��������Ҵ�������߳�
�����ļ��������¼��ȵ�
ÿһ�����̶���һ��ID��,���ID�ž���PID,һ��PIDΨһ��ʶһ������

�����ܽ�:
PID���ǽ��̵�ID��,��Ψһ��ʶһ������
��������ں˶����ʵ�ʵ�ַ,��Ҫ�����ں˶���ͱ����ȡ����
*/

/*
ʲô�ǽ���?
����ָ���������е�һ�����򡣻��仰˵�����ڴ��е�һ�δ���

�����ڲ���ϵͳ�а���һ��ʲô��ɫ?
��: 
Ϊ��ǰ�����ṩ����Ҫ����Դ,��: ���ݡ�����ȵ�
����԰ѽ��̿�����һ�ֿռ��ϵĸ���,����ʵ����
�е�һ�����Ӿ���,���̾��൱����һ������,�߳���
�൱���Ƿ����������(ʹ��������̵Ķ���)
*/


/*
���̵Ĵ�������:
1.ӳ��exe�ļ�(��Ҫִ�е�exe�ļ�����һ���ڴ���)
2.�����ں˶���(EPROCESS)��
3.ӳ��ϵͳDLL(ntdll.dll)
4.����һ����ʼ�߳�(ETHREAD)
5.�����߳�֮ǰ��Ҫӳ��dll,��һ��ӳ���dll������������õ�������dll,�������ntdll��ÿ��exe�����dll
6.��ʼִ�г�ʼ�߳�(�������ʱ��ָ�����̵߳�CREATE_SUSPENDED״̬���߳���ʱ����ִ��)��
*/

BOOL CreateChildProcess(PTSTR szChildProcessName, PTSTR szCommandLine)
{
	// ������������Ҫ�Ľṹ��
	STARTUPINFO si;
	PROCESS_INFORMATION pi;

	// ��ʼ���ṹ��
	ZeroMemory(&si, sizeof(si));
	ZeroMemory(&pi, sizeof(pi));

	// ��������,���ʧ�����ӡ�������,����FALSE
	// ������ϸ�����: https://msdn.microsoft.com/en-us/library/windows/desktop/ms682425(v=vs.85).aspx
	if(!CreateProcess(
		szChildProcessName, // ��������,��Ҫ���ĸ����򴴽�����
		szCommandLine, // ������
		NULL, // �Ƿ���Ա��ӽ��̼̳н��̾��
		NULL, // �Ƿ���Ա��ӽ��̼̳��߳̾��
		FALSE, // ����˲���ΪTRUE��������е�ÿ���ɼ̳о���������½��̼̳С�����ò���ΪFALSE���������ᱻ�̳С���ע�⣬�̳еľ��������ԭʼ�����ͬ��ֵ�ͷ���Ȩ�ޡ�
		0, // ������ʶ,�������ȼ��ʹ������̵ı�־���й�ֵ�б������ https://msdn.microsoft.com/en-us/library/windows/desktop/ms684863(v=vs.85).aspx
		NULL, // �Ƿ�ʹ�ø����̻�������
		NULL, // �Ƿ�ʹ�ø����̵�Ŀ¼��Ϊ��ǰĿ¼
		&si, // STARTUPINFO �ṹ��
		&pi  // PROCESS_INFORMATION �ṹ��
		)){
			printf("CreateChildProcess Error: %d \n",GetLastError());
			return FALSE;
	}

	//�ͷž��
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

