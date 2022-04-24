// 12-��һ�����ڳ���.cpp : ����Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

// ���:
// ���Ǹ�DWORD���͵ı��(�����Ķ�����0��,���ֻ�Ǹ����)

// ��ѧϰ���ľ��:
// HANDLE ָ��һ���ں˶���ľ��
// HWND   ָ��һ�����ڵľ��
// HDC    ָ��һ���豸�����ĵľ��

// ����Ҫ��ѧϰ��:
// HINSTANCE ָ��һ��ģ��ľ��


// �ص�����
LRESULT CALLBACK WindowProc(
	HWND hwnd,      // ���ھ��
	UINT uMsg,      // ��Ϣ��ʶ��
	WPARAM wParam,  // ����1
	LPARAM lParam   // ����2
	)
{
	// Ĭ�ϵĴ��ڴ�����
	return DefWindowProc(hwnd,uMsg,wParam,lParam);
}

int APIENTRY WinMain(HINSTANCE hInstance,     // ��ǰ���ģ���ڽ���(�ڴ�)�е�λ��
					 HINSTANCE hPrevInstance, // �ڶ���������ԶΪNULL,���ù���
					 LPSTR lpCmdLine,         // �����в���
					 int nCmdShow             // �����ʾ?���,��С��,����?
					 )
{
	// �������ڵ�����
	// 1.��һ��,������Ĵ�����ʲô����?  WNDCLASS����������������ڵ�����

	/* ����WNDCLASS�ṹ��,���������4������,������������˼�ɾ����Google�о�
	typedef struct _WNDCLASS { 
		UINT       style; 
		WNDPROC    lpfnWndProc;   // ������ڵĺ���(��Ϊ���ں���,�ص�����),ÿһ�����ڶ�Ӧ�ö�Ӧһ�����ں���
		int        cbClsExtra; 
		int        cbWndExtra; 
		HINSTANCE  hInstance;	  // ��ǰ������������ĸ�ģ��?
		HICON      hIcon; 
		HCURSOR    hCursor; 
		HBRUSH     hbrBackground; // ���ڵı�����ɫ
		LPCTSTR    lpszMenuName; 
		LPCTSTR    lpszClassName; // �������
	} WNDCLASS, *PWNDCLASS; 
	*/

	// ��ʼ��WNDCLASS�ṹ��
	WNDCLASS wndclass = {0};

	// ����ǰ��WNDCLASSȡһ������
	TCHAR className[] = TEXT("MyFirstWindow");
	wndclass.lpszClassName = className;

	// ���ڵı�����ɫ
	wndclass.hbrBackground = (HBRUSH)COLOR_BACKGROUND;
	
	// ��ǰ�������ڱ�ģ��
	wndclass.hInstance = hInstance;

	// �ص�����
	wndclass.lpfnWndProc = WindowProc; // ���̺߳���,���Ƕ����Լ�����,�Լ�ͨ��CreateThread������,ͨ�׽������Լ������Լ�����,�����ں�������ֻ��Ҫ����,�������ɲ���ϵͳ����ɵġ��������Ϊ�ص�����
	
	// ע�ᴰ����,���������Ŀ�ľ��ǰ����Ǹոն����Ҳ����ֵ�Ľṹ����߲���ϵͳ,�ò���ϵͳ���ҵ���
	RegisterClass(&wndclass); 

	// 2.�ڶ���,��������ʾ����
	/*
	HWND CreateWindow(
		LPCTSTR lpClassName,  // ע����Ǹ��������
		LPCTSTR lpWindowName, // ���ڵı���
		DWORD dwStyle,        // ���ڵķ��,�����뿴API
		int x,                // ����ڸ����ڵ�X����
		int y,                // ����ڸ����ڵ�Y����
		int nWidth,           // ���ڵĿ��,��λ������
		int nHeight,          // ���ڵĸ߶�,��λ������
		HWND hWndParent,      // �����ڵľ��
		HMENU hMenu,          // �˵����
		HINSTANCE hInstance,  // ��ǰ��ģ����
		LPVOID lpParam        // ��������
	);
	// ����ɹ����ص�ǰ���ڵľ��,���򷵻�NULL,����ͨ��GetLastError�鿴��Ϊʲôԭ��ʧ��
	*/
	HWND hwnd = CreateWindow(
		className,
		TEXT("�ҵĵ�һ������"),
		WS_OVERLAPPEDWINDOW,
		10,
		10,
		800,
		600,
		NULL,
		NULL,
		hInstance,
		NULL
		);
	
	// ������ڴ���ʧ��,���ӡ������Ϣ
	TCHAR szOutBuff[0x80];
	if(hwnd == NULL)
	{
		_stprintf(szOutBuff,TEXT("Error��%d"),GetLastError());
		OutputDebugString(szOutBuff);
		return 0;
	}
	
	//3.��ʾ����
	/*
	BOOL ShowWindow(
		HWND hWnd,     // Ҫ��ʾ�Ĵ��ھ��
		int nCmdShow   // ��ʲô��ʽ��ʾ,������ο�API
	);
	*/
	ShowWindow(hwnd,SW_SHOW);

	// 4.������Ϣ������
	/*
	ʲô����Ϣ����?
	��:
	����˵,���ǲ���ϵͳά����һ������,�������ŵ������д��ڵ���Ϣ,
	���ж��ڴ��ڵĲ���,����,�����󻯡���С�����ر���Щ��ť,�������
	һ����Ϣ,�������Ϣ�ͻᱻ�洢����Ϣ������,�����Ϣ��������ʲô����
	����Ϣ�������ĸ����ڲ����ĵȵ���Ϣ��

	GetMessage�����������Ǵ���Ϣ������ȡ��һ����Ϣ

	BOOL GetMessage(
		LPMSG lpMsg,         // ���ָ��ָ��һ������MSG�Ľṹ��,����OUT�Ͳ���,����Ϣ������ȡ������Ϣ�ͻ�洢������ṹ����
		HWND hWnd,           // ���ھ��,��Ϊһ���߳̿���ӵ�ж������,���Դ���Ϣ����ȡ��Ϣ��ʱ����Ӧ�ø��߲���ϵͳ��Ҫ�����ĸ����ڵ���Ϣ,���дNULL��ʾ��Ҫȡ���е���Ϣ
		UINT wMsgFilterMin,  // ָ������������С��Ϣֵ��������ͨ��ʹ��WM_KEYFIRSTָ����һ������Ϣ��WM_MOUSEFIRSTָ�������Ϣ��Windows XP�У��ڴ˴�ʹ�õ���WM_INPUT��ͬʱwMsgFilterMaxָ������ϢҲֻ��WM_INPUT��
		UINT wMsgFilterMax   // ָ���������������Ϣֵ��������ͨ��ʹ��WM_KEYLASTָ����ĩ������Ϣ��WM_MOUSELASTָ����ĩ�����Ϣ��Windows XP�У��ڴ˴�ʹ�õ���WM_INPUT��ͬʱwMsgFilterMinָ������ϢҲֻ��WM_INPUT��
	);
	*/
	MSG msg;
	BOOL bRet;

	// Ϊ���ܹ�һֱ������Ϣ,ͨ�����ǵ�GetMessage��������дѭ�����ظ���ȡ,�Ա���һֱ��ȡ��Ϣ
	while( (bRet = GetMessage( &msg, NULL, 0, 0 )) != 0)
	{ 
		if (bRet == -1)
		{
			_stprintf(szOutBuff,TEXT("Error��%d"),GetLastError());
			OutputDebugString(szOutBuff);
		}
		else
		{
			//ת����Ϣ
			TranslateMessage(&msg); //���������ǽ��������Ϣת��Ϊ�ַ���Ϣ���ַ���Ϣ���͵���Ϣ�����У�����һ���̵߳��ú���GetMessage��PeekMessageʱ��������
			//�ַ���Ϣ,DispatchMessage������Ϣ�е�hwnd�ص�0��,�������hwnd�����ĸ�����,Ȼ���ں��ٻ�ͷ�����ĸ����ں���,���Դ��ں����ֽ����ص�����
			DispatchMessage(&msg); 
		}
	}

	return 0;
}