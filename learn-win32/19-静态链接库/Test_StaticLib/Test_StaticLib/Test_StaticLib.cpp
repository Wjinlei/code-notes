// Test_StaticLib.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"



// 1. 直接把.lib和.h 放入项目目录
// 2. 然后把.h导入到当前项目中
// 3. include .h 文件
// 4. pragma comment(lib, ".lib文件名") // 引入.lib

#include "StaticLib.h"

#pragma comment(lib, "StaticLib.lib")

int _tmain(int argc, _TCHAR* argv[])
{
	int x = add(1, 2);
	printf("%d\n", x);
	getchar();
	return 0;
}

