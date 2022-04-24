// 08-�̰߳�ȫ����-�ٽ���.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

/*
��ν���̰߳�ȫ����? ����ʹ���ٽ���!

ʲô���ٽ���Դ? 
��: �ٽ���Դ����һ�ν�����һ���߳�ʹ�õ���Դ

ʲô���ٽ���? 
��: �����ٽ���Դ���Ƕδ����Ϊ�ٽ���

�ٽ�������α����̰߳�ȫ�����?
��:
A�̻߳�ȡ���ƺ�,B�߳̾ͻ�ȡ��������(����A�߳������ͷ�)
�õ����Ƶ��̲߳ſ��Է����ٽ���Դ,�����޷�����

���ʹ���ٽ���?
��:
1. ����CRITICAL_SECTION csȫ�ֱ���(����)
2. InitializeCriticalSection(&cs); ��ʼ������
3. EnterCriticalSection(&cs); �����ٽ���
4. ʹ���ٽ���Դ
5. LeaveCriticalSection(&cs); �뿪�ٽ���
*/

CRITICAL_SECTION cs; // �����ٽ���ȫ�ֱ���(����)
int g_dwTickets = 10; // Ʊ��(�ٽ���Դ)

// �̺߳���
DWORD WINAPI MyFirstThreadProc(LPVOID lpParameter)
{	
	/* �����ǲ������ʹ���ٽ����Ĵ���ʾ��

	while(g_dwTickets > 0)
	{
		EnterCriticalSection(&cs); //�����ٽ���
		printf("����: %d ��Ʊ\n",g_dwTickets);
		g_dwTickets--;
		printf("����һ��,����: %d ��\n",g_dwTickets);
		LeaveCriticalSection(&cs); //�뿪�ٽ���
	}

	*/

	// ������ٽ�������Ӧ���ǰѶ���ȫ�ֱ����Ķ�д�ж����е��߼�ȫ�ŵ��ٽ�������ʵ��,�������������İ�ȫ
	EnterCriticalSection(&cs); //�����ٽ���,��ȡ����

	// ���⿪ʼ�����ٽ���,g_dwTickets�����ٽ���Դ
	while(g_dwTickets > 0) // �Ѷ���ȫ�ֱ����Ķ�д�ж����е��߼�ȫ�ŵ��ٽ�������ʵ��,�������������İ�ȫ
	{
		printf("����: %d ��Ʊ\n",g_dwTickets);
		g_dwTickets--;
		printf("����һ��,����: %d ��\n",g_dwTickets);
	}// �������ٽ����ͽ���

	LeaveCriticalSection(&cs); //�뿪�ٽ���,�ͷ�����
	return 0;
}

int _tmain(int argc, _TCHAR* argv[])
{
	DWORD dwResult1;
	DWORD dwResult2;
	HANDLE aThreadHandles[2];
	// ��ʼ������
	InitializeCriticalSection(&cs);

	// ����һ�����߳�
	aThreadHandles[0] = CreateThread(NULL,0,MyFirstThreadProc,NULL,0,NULL);

	// ����һ�����߳�
	aThreadHandles[1] = CreateThread(NULL,0,MyFirstThreadProc,NULL,0,NULL);

	// �ȴ��߳�ִ�н���
	WaitForMultipleObjects(2,aThreadHandles,TRUE,INFINITE);

	// �߳�ִ�����
	GetExitCodeThread(aThreadHandles[0],&dwResult1);
	GetExitCodeThread(aThreadHandles[1],&dwResult2);
	printf("Thread1ExitCode: %d, Thread2ExitCode: %d\n",dwResult1,dwResult2);

	getchar();
	return 0;
}

