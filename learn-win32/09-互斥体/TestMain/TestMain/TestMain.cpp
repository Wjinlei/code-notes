// TestMain.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"


int _tmain(int argc, _TCHAR* argv[])
{
	// �����һ�����̴����Ļ�����
	HANDLE g_hMutex = CreateMutex(NULL,FALSE,L"������"); //����ʵ���ϲ�û�����´���������,����ʹ��ǰ����̴����Ļ�����(��Ϊ������������ͬ)

	// �ȴ�������
	WaitForSingleObject(g_hMutex,INFINITE);

	for(int i=0;i<10;i++)
	{
		Sleep(1000);
		printf("B���̵�X�߳�: %d\n",i);
	}

	//�ͷŻ�����
	ReleaseMutex(g_hMutex);
	return 0;
}

