// �������һ�����࿪Ӧ��(ִ��Ŀ¼���.exe���ܲ��ܿ�����).cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"


int _tmain(int argc, _TCHAR* argv[])
{
	// ����һ��������
	HANDLE g_hMutex = CreateMutex(NULL,FALSE,L"������");

	// ���״̬��
	DWORD errorInfo = GetLastError();

	if(g_hMutex) // ��������ɹ�
	{
		if(ERROR_ALREADY_EXISTS == errorInfo) //�жϻ������ǲ��ǵ�һ�δ���,�������,���˳����̡�
		{
			ReleaseMutex(g_hMutex);
			return 0;
		}
	}else //�������ĳ��ԭ���»����崴��ʧ��,��ôֱ���˳�����
	{
		printf("����ʧ��,�����˳�!\n");
		ReleaseMutex(g_hMutex);
		return 0;
	}

	// ��������ɹ�,�����ǵ�һ�δ���,�����ִ��
	while(1)
	{
		Sleep(1000);
		printf("����ִ����...\n");
	}
	return 0;
}

