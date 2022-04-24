#include "stdafx.h"

// 创建目录
VOID TestCreateDir()
{
	/*
	// 创建目录
	BOOL CreateDirectory(
		LPCTSTR lpPathName,                         // 目录名称,注意这里是完整的路径
		LPSECURITY_ATTRIBUTES lpSecurityAttributes  // 安全描述符
	);
	成功返回非0,失败返回0, 可以用GetLastError来查看原因. 
	
	*/
	CreateDirectory(TEXT("TestDirectory"),NULL);
}

// 删除目录
VOID TestDelDir()
{
	//删除目录
	/*
	BOOL RemoveDirectory(
		LPCTSTR lpPathName   // 目录名称,注意这里是完整的路径
		);
	返回值同上
	*/

	RemoveDirectory(TEXT("TestDirectory"));

}

// 重命名目录
VOID TestRenameDir()
{
	//修改目录名称
	/*
	BOOL MoveFile(
		LPCTSTR lpExistingFileName, // 原文件名,注意这里是完整的路径
		LPCTSTR lpNewFileName       // 新文件名,注意这里是完整的路径
		);
	返回值同上
	*/

	MoveFile(TEXT("TestDirectory"), TEXT("NewDir"));
}

// 获取程序的当前路径
VOID TestGetCurrDir()
{
	/*
	//获取程序当前目录
	DWORD GetCurrentDirectory(
		DWORD nBufferLength,  // 取多长
		LPTSTR lpBuffer       // 取到的字符串会存储在这个Buffer中
	);
	*/
	TCHAR szDirNameBuffer[200] = {0};

	// 注意: 中文路径它获取不到
	GetCurrentDirectory(200,szDirNameBuffer);

	_tprintf(szDirNameBuffer);
}

// 设置程序的当前目录
VOID TestSetCurrDir()
{
	/*
	//设置程序当前目录
	BOOL SetCurrentDirectory(
		LPCTSTR lpPathName   // 新的目录名,注意这里是完整的路径
	);
	*/
	SetCurrentDirectory(TEXT("C:\\Users\\Administrator\\Desktop"));
	CreateDirectory(TEXT("TestDir"),NULL);
}