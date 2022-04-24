// 隐式链接.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

/* 隐式链接的步骤: */

// 1. 把.dll和 .lib放到工程目录中

// 2. 添加 #pragma comment(lib, "DLL名.lib")
#pragma comment(lib, "DLL.lib")

// 3. 加入函数声明
// 使用.def文件导出时使用 __declspec(dllimport) 函数声明
__declspec(dllimport) int add(int x, int y);
__declspec(dllimport) int sub(int x, int y);
// 使用extern "C" __declspec(dllexport) 导出时使用 extern "C" __declspec(dllimport) 函数声明

int _tmain(int argc, _TCHAR* argv[])
{
	// 然后就可以直接使用
	int x = add(1,2);
	int y = sub(5,1);

	printf("%d\n", x);
	printf("%d\n", y);

	getchar();
	return 0;
}

