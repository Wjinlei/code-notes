// 10-�¼�.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

/*
�ڿ�ʼѧ�¼�֮ǰ,��˵˵����ʲô��?
��:
�����֮ǰѧ����֪ʶ,�ٽ����ͻ�����,���ܲ�����һ���߳�ͬ���İ���
������һ������������һ��,����������һ���İ�����

ʲô���߳�ͬ��?
�߳�ͬ�� = ���� + ����
*/

HANDLE g_hSet; // �������¼�
HANDLE g_hClean; // �������¼�
int g_ReadyProductNumber = 10; // ׼�������Ĳ�Ʒ����
int g_AlreadyProductNumber = 0; // �������Ĳ�Ʒ����

// �������߳�
DWORD WINAPI ProducerThread(LPVOID pM)
{
	for (int i=0; i<g_ReadyProductNumber; i++)
	{	
		// �ȴ�g_hSet�¼�
		WaitForSingleObject(g_hSet,INFINITE);
		g_AlreadyProductNumber++;
		printf("������������: %d ��\n",g_AlreadyProductNumber);
		SetEvent(g_hClean); // ����g_hClean�¼����Ա�wait
	}
	return 0;
}

// �������߳�
DWORD WINAPI ConsumerThread(LPVOID pM)
{
	for (int i=0; i<=g_AlreadyProductNumber;NULL)
	{	
		// �ȴ�g_hClean�¼�
		WaitForSingleObject(g_hClean,INFINITE);
		g_AlreadyProductNumber--;
		printf("������������1��,��ʣ %d ��\n",g_AlreadyProductNumber);
		SetEvent(g_hSet); // ����g_hSet�¼����Ա�wait
	}
	return 0;
}


int _tmain(int argc, _TCHAR* argv[])
{
	/*
	HANDLE WINAPI CreateEvent(
	__in_opt  LPSECURITY_ATTRIBUTES lpEventAttributes, // ��ȫ������
	__in      BOOL bManualReset, // �¼�����,TRUE=֪ͨ����,FALSE=��������
	__in      BOOL bInitialState, // ����������Event�Ƿ���Ա�wait,TRUE��ʾ����,FALSE��ʾ������
	__in_opt  LPCTSTR lpName // ��ǰ��Event������,���ֻ�ڵ�ǰ�Ľ�������,�Ͳ���Ҫ������
	);

	�ڶ�������: bManualReset��⣺
	ʲô�ǻ�������?
	��: ����һ��wait���Ժ�,��һ��ֻ�ܴ�������״̬
	����˵SetEvent��ѶԷ���bInitialState�����ĳ�TRUE,ͬʱ����Լ���bInitialState�ĳ�FALSE
	�����ͻ����,���ѶԷ�,�Լ��������״̬��

	ʲô��֪ͨ����?
	��: ����һ��wait���Ժ�,��һ��Ҳ����wait��(ǰ���ǿ��Ա�wait)
	����˵SetEvent��ѶԷ���bInitialState�����ĳ�TRUE,ͬʱ�Լ���bInitialState���ֲ���
	�����ͻ����,���ѶԷ�,�Լ�Ҳ������
	*/

	//�����¼�
	g_hSet = CreateEvent(NULL,FALSE,TRUE,NULL);
	g_hClean = CreateEvent(NULL,FALSE,FALSE,NULL);

	//�����߳�
	HANDLE aThreadArray[2];
	aThreadArray[0] = ::CreateThread(NULL,0,ProducerThread,NULL,0,NULL);
	aThreadArray[1] = ::CreateThread(NULL,0,ConsumerThread,NULL,0,NULL);

	//�ȴ�2���̶߳�������,���߳�������ִ��
	WaitForMultipleObjects(2,aThreadArray,TRUE,INFINITE);
	CloseHandle(aThreadArray[0]);
	CloseHandle(aThreadArray[1]);
	CloseHandle(g_hSet);
	CloseHandle(g_hClean);

	getchar();
	return 0;

	/*
	�ܽ�: �¼�������������߳�ͬ�������(���� + ����)
	*/
}

