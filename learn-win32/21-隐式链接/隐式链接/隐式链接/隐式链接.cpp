// ��ʽ����.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

/* ��ʽ���ӵĲ���: */

// 1. ��.dll�� .lib�ŵ�����Ŀ¼��

// 2. ��� #pragma comment(lib, "DLL��.lib")
#pragma comment(lib, "DLL.lib")

// 3. ���뺯������
// ʹ��.def�ļ�����ʱʹ�� __declspec(dllimport) ��������
__declspec(dllimport) int add(int x, int y);
__declspec(dllimport) int sub(int x, int y);
// ʹ��extern "C" __declspec(dllexport) ����ʱʹ�� extern "C" __declspec(dllimport) ��������

int _tmain(int argc, _TCHAR* argv[])
{
	// Ȼ��Ϳ���ֱ��ʹ��
	int x = add(1,2);
	int y = sub(5,1);

	printf("%d\n", x);
	printf("%d\n", y);

	getchar();
	return 0;
}

