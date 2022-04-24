// 13-消息类型.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"


// 问: 回调函数的参数是谁传递过来的?怎么传递的?

// 答: 先由GetMessage获取到消息,再由DispatchMessage将消息传回给内核,最后由内核来调用该函数,由内核来传递参数

// 回调函数
LRESULT CALLBACK WindowProc(
							HWND hwnd,      // 窗口句柄
							UINT uMsg,      // 消息类型
							WPARAM wParam,  // 消息的详细信息,这个参数的具体含义是由消息的类型决定的
							LPARAM lParam   // 其他的辅助性信息,这个参数的具体含义是由消息的类型决定的
)
{
	TCHAR szOutBuff[0x80];

	// 如果你不知道有什么消息,可以打开这两句,然后你在窗口上操作,看它会产生什么消息
	_stprintf(szOutBuff,TEXT("消息类型: %x\n"),uMsg);
	OutputDebugString(szOutBuff);
	

	// 通常我们只需要关注我们需要的消息,在这里用switch处理即可
	switch(uMsg)
	{
	case WM_DESTROY: // 窗口被销毁消息
		{
			// 销毁窗口并退出
			PostQuitMessage(0);
			break;
		}
	case WM_KEYDOWN: // 键盘按下消息
		{
			/*
			LRESULT CALLBACK WindowProc(
				HWND hwnd,       // handle to window
				UINT uMsg,       // WM_KEYDOWN
				WPARAM wParam,   // virtual-key code
				LPARAM lParam    // key data
			);
			*/
			_stprintf(szOutBuff,TEXT("消息: %x - %x - %x\n"),uMsg,wParam,lParam);
			OutputDebugString(szOutBuff);
			break;
		}
	case WM_CHAR: // 这个消息可以返回我们按下的字符,它依赖这个TranslateMessage函数,将我们按下的虚拟码转换为字符
		{
			_stprintf(szOutBuff,TEXT("Message: %c\n"),wParam);
			OutputDebugString(szOutBuff);
			break;
		}
	}

	// 通常我们也要写上默认的窗口处理函数,这样可以省去我们的一些操作
	return DefWindowProc(hwnd,uMsg,wParam,lParam);
}

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	// 1.定义并注册窗口
	WNDCLASS wndclass = {0};
	TCHAR className[] = TEXT("MyFirstWindow");
	wndclass.lpszClassName = className;
	wndclass.hbrBackground = (HBRUSH)COLOR_BACKGROUND;
	wndclass.hInstance = hInstance;
	wndclass.lpfnWndProc = WindowProc;
	RegisterClass(&wndclass);

	// 2.创建并显示窗口
	HWND hwnd = CreateWindow(className,TEXT("我的第一个窗口"),WS_OVERLAPPEDWINDOW,10,10,800,600,NULL,NULL,hInstance,NULL);

	// 如果创建失败则打印错误信息
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
	/* 关于MSG结构体
	typedef struct tagMSG {
		HWND   hwnd;  //句柄,这个消息属于哪个窗口
		UINT   message; //消息的编号(类型)
		WPARAM wParam; //消息的详细信息,这个参数的具体含义是由消息的类型决定的(它对应回调函数的wParam参数)
		LPARAM lParam; //其他的辅助性信息,这个参数的具体含义是由消息的类型决定的(它对应回调函数的lParam参数)
		DWORD  time;  //消息产生的时间
		POINT  pt;  //消息是什么位置产生的.例如鼠标消息,那么它就指示你这个消息产生的坐标是什么
	} MSG, *PMSG; 
	*/
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
			//转换消息
			TranslateMessage(&msg); 
			DispatchMessage(&msg); 
		}
	}

	return 0;
}