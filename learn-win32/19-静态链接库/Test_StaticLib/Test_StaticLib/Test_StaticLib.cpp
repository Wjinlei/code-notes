// Test_StaticLib.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"



// 1. ֱ�Ӱ�.lib��.h ������ĿĿ¼
// 2. Ȼ���.h���뵽��ǰ��Ŀ��
// 3. include .h �ļ�
// 4. pragma comment(lib, ".lib�ļ���") // ����.lib

#include "StaticLib.h"

#pragma comment(lib, "StaticLib.lib")

int _tmain(int argc, _TCHAR* argv[])
{
	int x = add(1, 2);
	printf("%d\n", x);
	getchar();
	return 0;
}

