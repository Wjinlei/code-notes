// TestDLL.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

// 1.定义函数指针
typedef int (__cdecl *lpAdd)(int, int);
typedef int (__cdecl *lpSub)(int, int);

// 2.声明函数指针类型变量
lpAdd myAdd;
lpSub mySub;

int _tmain(int argc, _TCHAR* argv[])
{
	// 3.动态加载dll到进程空间
	HINSTANCE hModule = LoadLibrary(TEXT("DLL2.dll"));

	// 4.获取函数地址
	myAdd = (lpAdd)GetProcAddress(hModule, "add"); // 有名字的函数
	mySub = (lpSub)GetProcAddress(hModule, (char*)0x2); // 写编号

	// 5.使用函数指针
	int x = myAdd(1, 2);
	int y = mySub(6, 2);
	printf("x=%d\n", x);
	printf("y=%d\n", y);

	// 6.卸载dll
	FreeLibrary(hModule);

	getchar();
	return 0;
}

