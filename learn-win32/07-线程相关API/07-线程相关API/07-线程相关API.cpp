// 07-�߳����API.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

// �̺߳���
DWORD WINAPI ThreadProc(LPVOID lpParameter)
{
	for(int i=0;i<10;i++)
	{
		/*
		VOID Sleep(
			DWORD dwMilliseconds   // ֹͣʱ��,��λ�Ǻ���,��ֻ�ܿ��Ƶ�ǰ�Լ����߳�,���Լ�ͣ����
		);
		*/
		Sleep(500);
		printf("++++++++++++%d\n",i);
	}
	return 0;
}

int _tmain(int argc, _TCHAR* argv[])
{
	//************************************************��һ��APIע��************************************************
	/*
	HANDLE CreateThread(
		LPSECURITY_ATTRIBUTES lpThreadAttributes, // ��ȫ������
		SIZE_T dwStackSize,                       // ��ʼ��ջ��С
		LPTHREAD_START_ROUTINE lpStartAddress,    // �̺߳���
		LPVOID lpParameter,                       // �̲߳���
		DWORD dwCreationFlags,                    // ������ʶ
		LPDWORD lpThreadId                        // �߳�id
	);
	*/

	/*
	// �����߳�
	DWORD SuspendThread(
		HANDLE hThread   // �߳̾��,�ñ���ͣ����
	);

	// �����߳�
	DWORD ResumeThread(
		HANDLE hThread   // �߳̾��,�ñ���������
	);
	*/

	//************************************************��һ����ʾ����************************************************
	HANDLE hThreadArray[2];
	hThreadArray[0] = CreateThread(NULL,0,ThreadProc,NULL,0,NULL);
	hThreadArray[1] = CreateThread(NULL,0,ThreadProc,NULL,0,NULL);

	Sleep(3000);
	printf("�����һ���߳�!\n");
	// �����߳�,һ���߳̿��Թ�����
	SuspendThread(hThreadArray[0]);
	SuspendThread(hThreadArray[0]);
	
	Sleep(10000);
	printf("���ѵ�һ���߳�!\n");
	// �����߳�,���𼸴ξͱ��뻽�Ѽ���
	ResumeThread(hThreadArray[0]);
	ResumeThread(hThreadArray[0]);
	getchar();

	//************************************************�ڶ���APIע��************************************************
	// �ȴ��߳̽���,�κεĶ���������ȴ�,��ô�����ﶼ�����,��״̬�������ʱ����.
	/*
	DWORD WaitForSingleObject(
		HANDLE hHandle,        // ������,�κ��ں˶��󶼿�����Ϊ�ȴ��Ķ���
		DWORD dwMilliseconds   // ��ȴ��೤ʱ��,���N����״̬��Ȼû�з������,���������һ���᷵��(��ʱʱ��)
	);
	*/

	// �ȴ�����߳̽���
	/*
	DWORD WaitForMultipleObjects(
		DWORD nCount,             // �ȴ������ں˶���
		CONST HANDLE *lpHandles,  // �ȴ��ں˶��������
		BOOL bWaitAll,            // �ȴ�ģʽ,�����ָ�����еĵȴ�����״̬�����������ʱ��,��������ŷ���,����,���κ�һ���ں˶���״̬��������򷵻�,TRUE��ʾ����,FALSE��ʾ�κ�һ��
		DWORD dwMilliseconds      // �ȴ�ʱ��,��ʱʱ��
	);
	*/

	// ��ȡ�߳��˳�����
	/*
	BOOL GetExitCodeThread(
		HANDLE hThread,      // �߳̾��
		LPDWORD lpExitCode   // ����״̬,����OUT���͵Ĳ���
	);
	*/
	//************************************************�ڶ�����ʾ����************************************************
	//HANDLE hThreadArray[2];
	//hThreadArray[0] = CreateThread(NULL,0,ThreadProc,NULL,0,NULL);
	//hThreadArray[1] = CreateThread(NULL,0,ThreadProc,NULL,0,NULL);

	//printf("�����һ���߳�!\n");
	//SuspendThread(hThreadArray[0]);
	//
	////��10���ٻ��ѵ�һ���߳�
	//Sleep(10000);
	//printf("���ѵ�һ���߳�!\n");
	//ResumeThread(hThreadArray[0]);
	////�ȴ���һ���߳̽���,���̲߳Ż����
	//WaitForSingleObject(hThreadArray[0],INFINITE);
	////��������㲻wait,�������waitע��,�����ᷢ��ʲô?
	////��Ȼ�㻹����wait���е��ں˶���,���忴����API,�����ҾͲ���ʾ��

	//DWORD exitcode;
	//GetExitCodeThread(hThreadArray[0],&exitcode);
	//printf("ExitCodeThread: %d\n",exitcode);

	//for(int i=0;i<=9;i++)
	//{
	//	Sleep(500);
	//	printf("���̼߳���....\n");
	//}
	//printf("���߳̽���,�밴���������!");
	//getchar();

	//************************************************������APIע��************************************************
	// ��ȡ�̵߳������Ļ���
	/*
	BOOL GetThreadContext(
		HANDLE hThread,            // �߳̾��
		LPCONTEXT lpContext        // �����Ľṹ��
	);
	*/
	// �����̵߳������Ļ���
	/*
	BOOL SetThreadContext(
		HANDLE hThread,            // �߳̾��
		CONST CONTEXT *lpContext   // �����Ľṹ��
	);
	*/
	//************************************************��������ʾ����************************************************

	/*
	����: 
	�����ǰ����ֻ��һ����(����),��ô����˵��ֻ��ͬʱ��һ���̡߳�
	�ǵ���A�̵߳�ʱ��,ͻȻ������ĳ��ԭ���л���B�߳�,��ô����A�߳���ô��?����˵A�߳��ܵ�������?��ļĴ�����ֵ��ʲô?
	���Ƕ�֪�������ܵ�ʱ����Ҫ����һ�ѼĴ���,EAX,EBX,ECX,ESP,EBP,ESI,EDI...�ȵ����߰���һ���,����A�߳��ܵ�ʱ��,
	ͻȻ�л���B�߳���,��A�߳�ԭ����ֵҪ��Ҫ����?

	��:
	��ʵÿһ���̶߳���һ���ṹ��,���Լ����л���ʱ��,��ѵ�ǰ���������Щ���ݵ�ֵ����������ṹ����,����ṹ��ͽ���CONTEXT(������)
	����˵���߳���������ʵ��������
	*/
	//HANDLE hThreadArray[2];
	//hThreadArray[0] = CreateThread(NULL,0,ThreadProc,NULL,0,NULL);
	//hThreadArray[1] = CreateThread(NULL,0,ThreadProc,NULL,0,NULL);

	////Ҫ��ȡĳһ���̵߳�������,�ͱ����Ȱ�������
	//printf("�����һ���߳�!\n");
	//SuspendThread(hThreadArray[0]);

	////����CONTEXT�ṹ��
	//CONTEXT context;
	//context.ContextFlags = CONTEXT_INTEGER;
	////ContextFlags��΢��Ϊ���Ƕ���õ�,����Ҫ��һ�ξ����ĸ�flag
	///*
	//����: ���ѡ��CONTEXT,��F12ת������,��������Ҫ����Edi��Esi��һ��
	//E��ͷ��,��ôFlag�Ϳ�����CONTEXT_INTEGER
	////
 //   // This section is specified/returned if the
 //   // ContextFlags word contians the flag CONTEXT_INTEGER.
 //   //

 //   DWORD   Edi;
 //   DWORD   Esi;
 //   DWORD   Ebx;
 //   DWORD   Edx;
 //   DWORD   Ecx;
 //   DWORD   Eax;
	//*/
	////��ȡ�߳�������
	//GetThreadContext(hThreadArray[0],&context);
	//printf("EAX: %x EBX: %x ECX: %x EDX: %x\n",context.Eax,context.Ebx,context.Ecx,context.Edx);

	///*
	////���ֵ����Ը�,ͨ��SetThreadContext API
	//context.Eax = 0x00000000;
	//context.Ebx = 0x00000001;
	//context.Ecx = 0x00000002;
	//context.Edx = 0x00000003;
	//SetThreadContext(hThreadArray[0],&context);
	//printf("EAX: %x EBX: %x ECX: %x EDX: %x\n",context.Eax,context.Ebx,context.Ecx,context.Edx);
	//*/
	//ResumeThread(hThreadArray[0]);
	////�ͷ���Դ
	//CloseHandle(hThreadArray[0]);
	//CloseHandle(hThreadArray[1]);
	//getchar();
	return 0;
}

