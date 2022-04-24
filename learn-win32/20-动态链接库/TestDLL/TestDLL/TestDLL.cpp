// TestDLL.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

// 1.���庯��ָ��
typedef int (__cdecl *lpAdd)(int, int);
typedef int (__cdecl *lpSub)(int, int);

// 2.��������ָ�����ͱ���
lpAdd myAdd;
lpSub mySub;

int _tmain(int argc, _TCHAR* argv[])
{
	// 3.��̬����dll�����̿ռ�
	HINSTANCE hModule = LoadLibrary(TEXT("DLL2.dll"));

	// 4.��ȡ������ַ
	myAdd = (lpAdd)GetProcAddress(hModule, "add"); // �����ֵĺ���
	mySub = (lpSub)GetProcAddress(hModule, (char*)0x2); // д���

	// 5.ʹ�ú���ָ��
	int x = myAdd(1, 2);
	int y = mySub(6, 2);
	printf("x=%d\n", x);
	printf("y=%d\n", y);

	// 6.ж��dll
	FreeLibrary(hModule);

	getchar();
	return 0;
}

