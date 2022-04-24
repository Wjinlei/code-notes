// Main.cpp : �������̨Ӧ�ó������ڵ㡣
//

// ������Ҳ�����������ȫ�����,���Ƕ����֮�����ͬһ���ں˼��ٽ���Դʱʹ�õ�"��",����һ���ں˼�����

#include "stdafx.h"

// ���API
/*
����������
HANDLE CreateMutex(
	LPSECURITY_ATTRIBUTES lpMutexAttributes,  // ��ȫ������
	BOOL bInitialOwner,                       // ָ�����������ĳ�ʼ�����ߡ�
	LPCTSTR lpName                            // ����������,���д
);

���ڵڶ������� bInitialOwner ���:
�����ֵΪTRUE,��������߳̽���øû�����������Ȩ,��ʱ�������̵��޷���ȡ���û�����,���ǵ����������ͷ�

���򣬵����̲߳����û����������Ȩ,��ʱ���н��̶����Ի�ȡ�û�����,˭���õ�˭�Ϳ�����

*/
/*
����CreateMutex�����ķ���ֵ:
�������ִ�гɹ�,�򷵻�һ����������
���������ֵĻ������Ѿ�����(֮ǰ��������),��ô���ظû�����ľ��,���ҿ���ͨ��GetLastError��ȡ������ΪERROR_ALREADY_EXISTS��ֵ
��������Ļ�,���纯��ִ�в��ɹ�,�򷵻�NULL,����ͨ��GetLastError��ȡ��������Ϣ
*/

int _tmain(int argc, _TCHAR* argv[])
{
	// ����һ��������
	HANDLE g_hMutex = CreateMutex(NULL,FALSE,L"������");

	Sleep(3000);
	// �ȴ�������
	WaitForSingleObject(g_hMutex,INFINITE);

	for(int i=0;i<10;i++)
	{
		Sleep(1000);
		printf("A���̵�X�߳�: %d\n",i);
	}

	// �ͷŻ�����
	ReleaseMutex(g_hMutex);
	return 0;
}

