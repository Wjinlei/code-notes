// 12-第一个窗口程序.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"

// 句柄:
// 就是个DWORD类型的编号(真正的对象在0环,句柄只是个编号)

// 已学习过的句柄:
// HANDLE 指向一个内核对象的句柄
// HWND   指向一个窗口的句柄
// HDC    指向一个设备上下文的句柄

// 今天要新学习的:
// HINSTANCE 指向一个模块的句柄


// 回调函数
LRESULT CALLBACK WindowProc(
	HWND hwnd,      // 窗口句柄
	UINT uMsg,      // 消息标识符
	WPARAM wParam,  // 参数1
	LPARAM lParam   // 参数2
	)
{
	// 默认的窗口处理函数
	return DefWindowProc(hwnd,uMsg,wParam,lParam);
}

int APIENTRY WinMain(HINSTANCE hInstance,     // 当前这个模块在进程(内存)中的位置
					 HINSTANCE hPrevInstance, // 第二个参数永远为NULL,不用管它
					 LPSTR lpCmdLine,         // 命令行参数
					 int nCmdShow             // 如何显示?最大化,最小化,隐藏?
					 )
{
	// 创建窗口的流程
	// 1.第一步,定义你的窗口是什么样的?  WNDCLASS这个类用来描述窗口的属性

	/* 关于WNDCLASS结构体,先理解下面4个参数,其他参数的意思可具体查Google研究
	typedef struct _WNDCLASS { 
		UINT       style; 
		WNDPROC    lpfnWndProc;   // 这个窗口的函数(称为窗口函数,回调函数),每一个窗口都应该对应一个窗口函数
		int        cbClsExtra; 
		int        cbWndExtra; 
		HINSTANCE  hInstance;	  // 当前这个窗口属于哪个模块?
		HICON      hIcon; 
		HCURSOR    hCursor; 
		HBRUSH     hbrBackground; // 窗口的背景颜色
		LPCTSTR    lpszMenuName; 
		LPCTSTR    lpszClassName; // 类的名字
	} WNDCLASS, *PWNDCLASS; 
	*/

	// 初始化WNDCLASS结构体
	WNDCLASS wndclass = {0};

	// 给当前的WNDCLASS取一个名字
	TCHAR className[] = TEXT("MyFirstWindow");
	wndclass.lpszClassName = className;

	// 窗口的背景颜色
	wndclass.hbrBackground = (HBRUSH)COLOR_BACKGROUND;
	
	// 当前窗口属于本模块
	wndclass.hInstance = hInstance;

	// 回调函数
	wndclass.lpfnWndProc = WindowProc; // 像线程函数,我们都是自己创建,自己通过CreateThread来调用,通俗讲就是自己创建自己调用,而窗口函数我们只需要创建,调用是由操作系统来完成的。所以这称为回调函数
	
	// 注册窗口类,这个函数的目的就是把我们刚刚定义好也赋完值的结构体告诉操作系统,让操作系统能找到它
	RegisterClass(&wndclass); 

	// 2.第二步,创建并显示窗口
	/*
	HWND CreateWindow(
		LPCTSTR lpClassName,  // 注册的那个类的名字
		LPCTSTR lpWindowName, // 窗口的标题
		DWORD dwStyle,        // 窗口的风格,具体请看API
		int x,                // 相对于父窗口的X坐标
		int y,                // 相对于父窗口的Y坐标
		int nWidth,           // 窗口的宽度,单位是像素
		int nHeight,          // 窗口的高度,单位是像素
		HWND hWndParent,      // 父窗口的句柄
		HMENU hMenu,          // 菜单句柄
		HINSTANCE hInstance,  // 当前的模块句柄
		LPVOID lpParam        // 附加数据
	);
	// 如果成功返回当前窗口的句柄,否则返回NULL,可以通过GetLastError查看因为什么原因失败
	*/
	HWND hwnd = CreateWindow(
		className,
		TEXT("我的第一个窗口"),
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
	
	// 如果窗口创建失败,则打印错误信息
	TCHAR szOutBuff[0x80];
	if(hwnd == NULL)
	{
		_stprintf(szOutBuff,TEXT("Error：%d"),GetLastError());
		OutputDebugString(szOutBuff);
		return 0;
	}
	
	//3.显示窗口
	/*
	BOOL ShowWindow(
		HWND hWnd,     // 要显示的窗口句柄
		int nCmdShow   // 以什么形式显示,具体请参考API
	);
	*/
	ShowWindow(hwnd,SW_SHOW);

	// 4.接收消息并处理
	/*
	什么是消息队列?
	答:
	简单来说,就是操作系统维护的一个容器,它里面存放的是所有窗口的消息,
	所有对于窗口的操作,例如,点击最大化、最小化、关闭这些按钮,都会产生
	一个消息,而这个消息就会被存储到消息队列中,这个消息包含了是什么类型
	的消息，是由哪个窗口产生的等等信息。

	GetMessage函数的作用是从消息队列中取出一个消息

	BOOL GetMessage(
		LPMSG lpMsg,         // 这个指针指向一个叫做MSG的结构体,它是OUT型参数,从消息队列中取出的消息就会存储在这个结构体中
		HWND hWnd,           // 窗口句柄,因为一个线程可能拥有多个窗口,所以从消息队列取消息的时候你应该告诉操作系统你要的是哪个窗口的消息,如果写NULL表示你要取所有的消息
		UINT wMsgFilterMin,  // 指定被检索的最小消息值的整数，通常使用WM_KEYFIRST指定第一键盘消息或WM_MOUSEFIRST指定鼠标消息。Windows XP中：在此处使用的是WM_INPUT，同时wMsgFilterMax指定的消息也只有WM_INPUT。
		UINT wMsgFilterMax   // 指定被检索的最大消息值的整数，通常使用WM_KEYLAST指定最末键盘消息或WM_MOUSELAST指定最末鼠标消息。Windows XP中：在此处使用的是WM_INPUT，同时wMsgFilterMin指定的消息也只有WM_INPUT。
	);
	*/
	MSG msg;
	BOOL bRet;

	// 为了能够一直接受消息,通常我们的GetMessage函数都是写循环来重复获取,以便能一直获取消息
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
			TranslateMessage(&msg); //它的作用是将虚拟键消息转换为字符消息。字符消息被送到消息队列中，在下一次线程调用函数GetMessage或PeekMessage时被读出。
			//分发消息,DispatchMessage拿着消息中的hwnd回到0环,看看这个hwnd属于哪个窗口,然后内核再回头调用哪个窗口函数,所以窗口函数又叫做回调函数
			DispatchMessage(&msg); 
		}
	}

	return 0;
}