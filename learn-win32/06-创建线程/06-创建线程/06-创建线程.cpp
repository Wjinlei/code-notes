// 06-�����߳�.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

// �̺߳����ĸ�ʽ
DWORD WINAPI ThreadProc(LPVOID lpParameter)
{
	// ����Դ����������͵�ָ��,ֻҪ������ת�ͼ���
	int* p = (int*)lpParameter;
	for(int i=0;i<*p;i++)
	{
		Sleep(1000);
		printf("+++++++ %d\n",i);
	}
	return 0;
}

int _tmain(int argc, _TCHAR* argv[])
{
	HANDLE hThread;
	
	/*
	������Ҫע��һ��,�ڴ��ݲ���ʱ,����Ҫ��֤�̺߳���ִ�е�ʱ��
	�����õ��Ĳ�����ջû�б�����,Ҳ����˵����Ҫ��֤�߳���main
	����֮ǰִ����,����,��������n=10�ĳ�100,�㿴����ִ��100����?
	*/

	int n = 10;

	// ͨ��CreateThread�����������߳�
	/*
	HANDLE CreateThread( //����������ص���HANDLE(���)
		LPSECURITY_ATTRIBUTES lpThreadAttributes, // ��ȫ������,����һ���ṹ���ָ��
		SIZE_T dwStackSize,                       // ��ʼ��ջ��С
		LPTHREAD_START_ROUTINE lpStartAddress,    // ����Ҫִ�еĴ�������(�ص�����)
		LPVOID lpParameter,                       // �߳���Ҫ�Ĳ���,���û�о�дNULL
		DWORD dwCreationFlags,                    // �����̵߳ı�ʶ��,0��ʾ����������ִ��,CREATE_SUSPENDED��ʾ�Թ������ʽ����,��ϸ����� https://msdn.microsoft.com/en-us/library/windows/desktop/ms684863(v=vs.85).aspx
		LPDWORD lpThreadId                        // ��������Ǹ�OUT���͵Ĳ���,���ظոմ������̵߳��߳�ID
	);
	*/

	// ��ȫ������
	/*
	typedef struct _SECURITY_ATTRIBUTES { 
		DWORD  nLength;				 //��ǰ�ṹ��ĳ���
		LPVOID lpSecurityDescriptor; //���ָ��ָ��һ���ṹ��,��Ҫ�ǿ��Ƶ�ǰ����ں˶���,��˭��,����˭��,˭�ܹر�,˭�ܷ�����Ҫ������������Щ��Ϣ��
		BOOL   bInheritHandle;		 //��ǰ���ں˶����Ƿ����б��̳�
	} SECURITY_ATTRIBUTES, *PSECURITY_ATTRIBUTES; 
	*/

	hThread = CreateThread(NULL,0,ThreadProc,(LPVOID)&n,0,NULL);

	// �߳�����ں˲�����CloseHandle�ͻᱻ����
	/*
	�̱߳������������Ҫ����:
	1.�̼߳�����Ϊ0
	2.�̴߳���ִ�����
	*/
	CloseHandle(hThread);

	for(int i=0;i<20;i++)
	{
		Sleep(500);
		printf("--------%d\n",i);
	}
	return 0;
}

