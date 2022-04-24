// 14-子窗口.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"

/*
1. WINDOWS 提供了几个预定义的窗口类以方便我们的使用,我们一般就它们叫做子窗口控件，简称控件。

2. 控件会自己处理消息，并在自己状态发生改变时通知父窗口。
  
3. 预定义的控件有：
	
按钮、复选框、编辑框、静态字符串标签和滚动条等

说白了控件也是窗口,只不过是微软已经为我们定义好的WNDCLASS而已,不需要我们自己再去定义WNDCLASS
*/

HINSTANCE g_hInstance;
LRESULT CALLBACK WindowProc(
	HWND hwnd,      // 窗口句柄
	UINT uMsg,      // 消息类型
	WPARAM wParam,  // 消息的详细信息,这个参数的具体含义是由消息的类型决定的
	LPARAM lParam   // 其他的辅助性信息,这个参数的具体含义是由消息的类型决定的
	)
{
	// 子窗口不用我们写回调函数,控件会自己处理消息，并在自己状态发生改变时通知父窗口
	TCHAR szOutBuff[0x80];
	_stprintf(szOutBuff,TEXT("消息类型: %x\n"),uMsg); //我们点击按钮,看看它发送的是什么类型的消息
	OutputDebugString(szOutBuff);

	// 我们只需要关注我们需要的消息
	switch(uMsg)
	{
	case WM_DESTROY:
		{
			PostQuitMessage(0);
			break;
		}
	case WM_CREATE: // 当主窗口被创建时就会触发WM_CREATE这个消息,我们可以把子窗口的创建都写到这个消息里,这样主窗口创建完毕子窗口就创建好了
		{
			// 创建文本框
			CreateWindow(
				TEXT("EDIT"), // 文本框,必须带""号,这就是子窗口,这个EDIT类是微软为我们定义好的,我们只需要直接使用即可
				TEXT(""),
				WS_CHILD|WS_VISIBLE|WS_VSCROLL|ES_MULTILINE, // 子窗口WS_CHILD,创建出来能看见WS_VISIBLE,滚动条WS_VSCROLL,允许多行ES_MULTILINE
				1,
				1,
				600,
				600,
				hwnd, // 父窗口句柄
				(HMENU)0x100, // 该文本框的身份证,编号,这个可以你自己随意定义
				g_hInstance,
				NULL);

			// 创建按钮
			CreateWindow(
				TEXT("BUTTON"), // 按钮
				TEXT("设置"),
				WS_CHILD|WS_VISIBLE, // 子窗口WS_CHILD,创建出来能看见WS_VISIBLE
				610,
				520,
				80,
				30,
				hwnd, // 父窗口句柄
				(HMENU)0x101, // 该按钮的身份证,编号
				g_hInstance,
				NULL);

			// 创建按钮
			CreateWindow(
				TEXT("BUTTON"), // 按钮
				TEXT("清空"),
				WS_CHILD|WS_VISIBLE, // 子窗口WS_CHILD,创建出来能看见WS_VISIBLE
				700,
				520,
				80,
				30,
				hwnd, // 父窗口句柄
				(HMENU)0x102, // 该按钮的身份证,编号
				g_hInstance,
				NULL);
			break;
		}
	case WM_COMMAND: // 通过上面我们看到,当点击按钮控件时它发送的消息类型是111,对应的就是WM_COMMAND
		{
			/* WM_COMMAND 查看MSDN
			可以看到它的wParam参数的低16位用来标明这个子窗口的标识编号
			所以我们可以switch(LOWORD(wParam))来判断是哪个窗口的消息
			*/
			switch(LOWORD(wParam))
			{
			case (HMENU)0x100:
				{
					break;
				}
			case (HMENU)0x101:
				{
					MessageBox(0,TEXT("点击了设置按钮"),TEXT("设置"),MB_OK);
					SetDlgItemText(hwnd,0x100,TEXT("设置测试"));
					break;
				}
			case (HMENU)0x102:
				{
					MessageBox(0,TEXT("点击了清空按钮"),TEXT("清空"),MB_OK);
					SetDlgItemText(hwnd,0x100,TEXT(""));
					break;
				}
			}
		}
	}

	// 默认的窗口处理函数
	return DefWindowProc(hwnd,uMsg,wParam,lParam);
}

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	g_hInstance = hInstance;
	// 1.定义窗口
	WNDCLASS wndclass = {0};
	TCHAR className[] = TEXT("MyFirstWindow");
	wndclass.hbrBackground = (HBRUSH)COLOR_BACKGROUND;
	wndclass.lpszClassName = className;
	wndclass.hInstance = hInstance;
	wndclass.lpfnWndProc = WindowProc;
	RegisterClass(&wndclass);

	// 2.创建并显示窗口
	HWND hwnd = CreateWindow(
		className, //子窗口
		TEXT("我的第一个窗口"),
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
		_stprintf(szOutBuff,TEXT("Error：%d"),GetLastError());
		OutputDebugString(szOutBuff);
		return 0;
	}

	// 3.显示窗口
	ShowWindow(hwnd,SW_SHOW);

	// 4.接收消息并处理
	MSG msg;
	BOOL bRet;
	while( (bRet = GetMessage( &msg, NULL, 0, 0 )) != 0)
	{ 
		if (bRet == -1)
		{
			_stprintf(szOutBuff,TEXT("Error：%d"),GetLastError());
			OutputDebugString(szOutBuff);
		}
		else
		{
			// 转换消息
			TranslateMessage(&msg); 
			DispatchMessage(&msg); 
		}
	}

	return 0;
}