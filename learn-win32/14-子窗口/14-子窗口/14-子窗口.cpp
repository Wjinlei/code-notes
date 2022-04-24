// 14-�Ӵ���.cpp : ����Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

/*
1. WINDOWS �ṩ�˼���Ԥ����Ĵ������Է������ǵ�ʹ��,����һ������ǽ����Ӵ��ڿؼ�����ƿؼ���

2. �ؼ����Լ�������Ϣ�������Լ�״̬�����ı�ʱ֪ͨ�����ڡ�
  
3. Ԥ����Ŀؼ��У�
	
��ť����ѡ�򡢱༭�򡢾�̬�ַ�����ǩ�͹�������

˵���˿ؼ�Ҳ�Ǵ���,ֻ������΢���Ѿ�Ϊ���Ƕ���õ�WNDCLASS����,����Ҫ�����Լ���ȥ����WNDCLASS
*/

HINSTANCE g_hInstance;
LRESULT CALLBACK WindowProc(
	HWND hwnd,      // ���ھ��
	UINT uMsg,      // ��Ϣ����
	WPARAM wParam,  // ��Ϣ����ϸ��Ϣ,��������ľ��庬��������Ϣ�����;�����
	LPARAM lParam   // �����ĸ�������Ϣ,��������ľ��庬��������Ϣ�����;�����
	)
{
	// �Ӵ��ڲ�������д�ص�����,�ؼ����Լ�������Ϣ�������Լ�״̬�����ı�ʱ֪ͨ������
	TCHAR szOutBuff[0x80];
	_stprintf(szOutBuff,TEXT("��Ϣ����: %x\n"),uMsg); //���ǵ����ť,���������͵���ʲô���͵���Ϣ
	OutputDebugString(szOutBuff);

	// ����ֻ��Ҫ��ע������Ҫ����Ϣ
	switch(uMsg)
	{
	case WM_DESTROY:
		{
			PostQuitMessage(0);
			break;
		}
	case WM_CREATE: // �������ڱ�����ʱ�ͻᴥ��WM_CREATE�����Ϣ,���ǿ��԰��Ӵ��ڵĴ�����д�������Ϣ��,���������ڴ�������Ӵ��ھʹ�������
		{
			// �����ı���
			CreateWindow(
				TEXT("EDIT"), // �ı���,�����""��,������Ӵ���,���EDIT����΢��Ϊ���Ƕ���õ�,����ֻ��Ҫֱ��ʹ�ü���
				TEXT(""),
				WS_CHILD|WS_VISIBLE|WS_VSCROLL|ES_MULTILINE, // �Ӵ���WS_CHILD,���������ܿ���WS_VISIBLE,������WS_VSCROLL,�������ES_MULTILINE
				1,
				1,
				600,
				600,
				hwnd, // �����ھ��
				(HMENU)0x100, // ���ı�������֤,���,����������Լ����ⶨ��
				g_hInstance,
				NULL);

			// ������ť
			CreateWindow(
				TEXT("BUTTON"), // ��ť
				TEXT("����"),
				WS_CHILD|WS_VISIBLE, // �Ӵ���WS_CHILD,���������ܿ���WS_VISIBLE
				610,
				520,
				80,
				30,
				hwnd, // �����ھ��
				(HMENU)0x101, // �ð�ť�����֤,���
				g_hInstance,
				NULL);

			// ������ť
			CreateWindow(
				TEXT("BUTTON"), // ��ť
				TEXT("���"),
				WS_CHILD|WS_VISIBLE, // �Ӵ���WS_CHILD,���������ܿ���WS_VISIBLE
				700,
				520,
				80,
				30,
				hwnd, // �����ھ��
				(HMENU)0x102, // �ð�ť�����֤,���
				g_hInstance,
				NULL);
			break;
		}
	case WM_COMMAND: // ͨ���������ǿ���,�������ť�ؼ�ʱ�����͵���Ϣ������111,��Ӧ�ľ���WM_COMMAND
		{
			/* WM_COMMAND �鿴MSDN
			���Կ�������wParam�����ĵ�16λ������������Ӵ��ڵı�ʶ���
			�������ǿ���switch(LOWORD(wParam))���ж����ĸ����ڵ���Ϣ
			*/
			switch(LOWORD(wParam))
			{
			case (HMENU)0x100:
				{
					break;
				}
			case (HMENU)0x101:
				{
					MessageBox(0,TEXT("��������ð�ť"),TEXT("����"),MB_OK);
					SetDlgItemText(hwnd,0x100,TEXT("���ò���"));
					break;
				}
			case (HMENU)0x102:
				{
					MessageBox(0,TEXT("�������հ�ť"),TEXT("���"),MB_OK);
					SetDlgItemText(hwnd,0x100,TEXT(""));
					break;
				}
			}
		}
	}

	// Ĭ�ϵĴ��ڴ�����
	return DefWindowProc(hwnd,uMsg,wParam,lParam);
}

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	g_hInstance = hInstance;
	// 1.���崰��
	WNDCLASS wndclass = {0};
	TCHAR className[] = TEXT("MyFirstWindow");
	wndclass.hbrBackground = (HBRUSH)COLOR_BACKGROUND;
	wndclass.lpszClassName = className;
	wndclass.hInstance = hInstance;
	wndclass.lpfnWndProc = WindowProc;
	RegisterClass(&wndclass);

	// 2.��������ʾ����
	HWND hwnd = CreateWindow(
		className, //�Ӵ���
		TEXT("�ҵĵ�һ������"),
		WS_OVERLAPPEDWINDOW,
		10,
		10,
		800,
		600,
		NULL,
		NULL,
		hInstance,
		NULL);
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
			// ת����Ϣ
			TranslateMessage(&msg); 
			DispatchMessage(&msg); 
		}
	}

	return 0;
}