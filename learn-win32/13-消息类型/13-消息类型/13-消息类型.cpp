// 13-��Ϣ����.cpp : ����Ӧ�ó������ڵ㡣
//

#include "stdafx.h"


// ��: �ص������Ĳ�����˭���ݹ�����?��ô���ݵ�?

// ��: ����GetMessage��ȡ����Ϣ,����DispatchMessage����Ϣ���ظ��ں�,������ں������øú���,���ں������ݲ���

// �ص�����
LRESULT CALLBACK WindowProc(
							HWND hwnd,      // ���ھ��
							UINT uMsg,      // ��Ϣ����
							WPARAM wParam,  // ��Ϣ����ϸ��Ϣ,��������ľ��庬��������Ϣ�����;�����
							LPARAM lParam   // �����ĸ�������Ϣ,��������ľ��庬��������Ϣ�����;�����
)
{
	TCHAR szOutBuff[0x80];

	// ����㲻֪����ʲô��Ϣ,���Դ�������,Ȼ�����ڴ����ϲ���,���������ʲô��Ϣ
	_stprintf(szOutBuff,TEXT("��Ϣ����: %x\n"),uMsg);
	OutputDebugString(szOutBuff);
	

	// ͨ������ֻ��Ҫ��ע������Ҫ����Ϣ,��������switch������
	switch(uMsg)
	{
	case WM_DESTROY: // ���ڱ�������Ϣ
		{
			// ���ٴ��ڲ��˳�
			PostQuitMessage(0);
			break;
		}
	case WM_KEYDOWN: // ���̰�����Ϣ
		{
			/*
			LRESULT CALLBACK WindowProc(
				HWND hwnd,       // handle to window
				UINT uMsg,       // WM_KEYDOWN
				WPARAM wParam,   // virtual-key code
				LPARAM lParam    // key data
			);
			*/
			_stprintf(szOutBuff,TEXT("��Ϣ: %x - %x - %x\n"),uMsg,wParam,lParam);
			OutputDebugString(szOutBuff);
			break;
		}
	case WM_CHAR: // �����Ϣ���Է������ǰ��µ��ַ�,���������TranslateMessage����,�����ǰ��µ�������ת��Ϊ�ַ�
		{
			_stprintf(szOutBuff,TEXT("Message: %c\n"),wParam);
			OutputDebugString(szOutBuff);
			break;
		}
	}

	// ͨ������ҲҪд��Ĭ�ϵĴ��ڴ�����,��������ʡȥ���ǵ�һЩ����
	return DefWindowProc(hwnd,uMsg,wParam,lParam);
}

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	// 1.���岢ע�ᴰ��
	WNDCLASS wndclass = {0};
	TCHAR className[] = TEXT("MyFirstWindow");
	wndclass.lpszClassName = className;
	wndclass.hbrBackground = (HBRUSH)COLOR_BACKGROUND;
	wndclass.hInstance = hInstance;
	wndclass.lpfnWndProc = WindowProc;
	RegisterClass(&wndclass);

	// 2.��������ʾ����
	HWND hwnd = CreateWindow(className,TEXT("�ҵĵ�һ������"),WS_OVERLAPPEDWINDOW,10,10,800,600,NULL,NULL,hInstance,NULL);

	// �������ʧ�����ӡ������Ϣ
	TCHAR szOutBuff[0x80];
	if(hwnd == NULL)
	{
		_stprintf(szOutBuff,TEXT("Error��%d"),GetLastError());
		OutputDebugString(szOutBuff);
		return 0;
	}
	
	// 3.��ʾ����
	ShowWindow(hwnd,SW_SHOW);

	// 4.������Ϣ������
	MSG msg;
	/* ����MSG�ṹ��
	typedef struct tagMSG {
		HWND   hwnd;  //���,�����Ϣ�����ĸ�����
		UINT   message; //��Ϣ�ı��(����)
		WPARAM wParam; //��Ϣ����ϸ��Ϣ,��������ľ��庬��������Ϣ�����;�����(����Ӧ�ص�������wParam����)
		LPARAM lParam; //�����ĸ�������Ϣ,��������ľ��庬��������Ϣ�����;�����(����Ӧ�ص�������lParam����)
		DWORD  time;  //��Ϣ������ʱ��
		POINT  pt;  //��Ϣ��ʲôλ�ò�����.���������Ϣ,��ô����ָʾ�������Ϣ������������ʲô
	} MSG, *PMSG; 
	*/
	BOOL bRet;
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
			TranslateMessage(&msg); 
			DispatchMessage(&msg); 
		}
	}

	return 0;
}