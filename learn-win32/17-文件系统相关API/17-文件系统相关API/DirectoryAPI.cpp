#include "stdafx.h"

// ����Ŀ¼
VOID TestCreateDir()
{
	/*
	// ����Ŀ¼
	BOOL CreateDirectory(
		LPCTSTR lpPathName,                         // Ŀ¼����,ע��������������·��
		LPSECURITY_ATTRIBUTES lpSecurityAttributes  // ��ȫ������
	);
	�ɹ����ط�0,ʧ�ܷ���0, ������GetLastError���鿴ԭ��. 
	
	*/
	CreateDirectory(TEXT("TestDirectory"),NULL);
}

// ɾ��Ŀ¼
VOID TestDelDir()
{
	//ɾ��Ŀ¼
	/*
	BOOL RemoveDirectory(
		LPCTSTR lpPathName   // Ŀ¼����,ע��������������·��
		);
	����ֵͬ��
	*/

	RemoveDirectory(TEXT("TestDirectory"));

}

// ������Ŀ¼
VOID TestRenameDir()
{
	//�޸�Ŀ¼����
	/*
	BOOL MoveFile(
		LPCTSTR lpExistingFileName, // ԭ�ļ���,ע��������������·��
		LPCTSTR lpNewFileName       // ���ļ���,ע��������������·��
		);
	����ֵͬ��
	*/

	MoveFile(TEXT("TestDirectory"), TEXT("NewDir"));
}

// ��ȡ����ĵ�ǰ·��
VOID TestGetCurrDir()
{
	/*
	//��ȡ����ǰĿ¼
	DWORD GetCurrentDirectory(
		DWORD nBufferLength,  // ȡ�೤
		LPTSTR lpBuffer       // ȡ�����ַ�����洢�����Buffer��
	);
	*/
	TCHAR szDirNameBuffer[200] = {0};

	// ע��: ����·������ȡ����
	GetCurrentDirectory(200,szDirNameBuffer);

	_tprintf(szDirNameBuffer);
}

// ���ó���ĵ�ǰĿ¼
VOID TestSetCurrDir()
{
	/*
	//���ó���ǰĿ¼
	BOOL SetCurrentDirectory(
		LPCTSTR lpPathName   // �µ�Ŀ¼��,ע��������������·��
	);
	*/
	SetCurrentDirectory(TEXT("C:\\Users\\Administrator\\Desktop"));
	CreateDirectory(TEXT("TestDir"),NULL);
}