// 02-在Win32中如何使用字符串.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"


int _tmain(int argc, _TCHAR* argv[])
{
	// 字符类型：

	// Ascii
	CHAR  szStr[] = "中国"; //CHAR 其实就是C语言中的char,只不过在Win32中微软重新给他定义了个名字

	// Unicode
	WCHAR swzStr[] = L"中国"; //WCHAR 其实就是C语言中的wchar_t,只不过在Win32中微软重新给他定义了个名字

	// TCHAR是一个宏,他会根据你当前的项目的编码把字符串转换为你当前的编码,有利于跨平台
	TCHAR stzSr[] = TEXT("中国");

	// 字符串指针：
	// Ascii
	PSTR  pszStr = "中国"; //P通常表示指针,我们习惯用P开头来表示指针

	// Unicode
	PWSTR pwszStr = L"中国"; //P通常表示指针,我们习惯用P开头来表示指针

	// PTSTR是一个宏,他会根据你当前的项目的编码把字符串转换为你当前的编码,有利于跨平台,以后字符串推荐使用这个
	PTSTR ptszStr = TEXT("中国");
/*
	MassageBox函数用于弹出一个消息框

	int MessageBox(
		HWND hWnd,          // 窗口句柄
		LPCTSTR lpText,     // 要显示的消息
		LPCTSTR lpCaption,  // 消息框标题
		UINT uType			// 消息框样式
	);
*/
	// Ascii
	CHAR szTitle[] = "标题";
	CHAR szContent[] = "欢迎大家来WIN32 API的世界";
	printf(szContent); // 控制台操作CHAR类型的用printf
	MessageBoxA(0,szContent,szTitle,MB_OK);

	// Unicode
	WCHAR swzTitle[] = L"标题";
	WCHAR swzContent[] = L"欢迎大家来的Win32 API世界!";
	wprintf(swzContent); // 控制台操作WCHAR类型的用wprintf
	MessageBoxW(0,swzContent,swzTitle,MB_OK);

	// 宏
	TCHAR stzTitle[] = TEXT("标题");
	TCHAR stzContent[] = TEXT("欢迎大家来的Win32 API世界!");

	// _tprintf是一个宏,它的作用和printf一样
	_tprintf(stzContent);
	MessageBox(0,stzContent,stzTitle,MB_OK);

	getchar();
	return 0;
}

