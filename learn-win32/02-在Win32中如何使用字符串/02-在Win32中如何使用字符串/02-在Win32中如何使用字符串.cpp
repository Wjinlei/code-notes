// 02-��Win32�����ʹ���ַ���.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"


int _tmain(int argc, _TCHAR* argv[])
{
	// �ַ����ͣ�

	// Ascii
	CHAR  szStr[] = "�й�"; //CHAR ��ʵ����C�����е�char,ֻ������Win32��΢�����¸��������˸�����

	// Unicode
	WCHAR swzStr[] = L"�й�"; //WCHAR ��ʵ����C�����е�wchar_t,ֻ������Win32��΢�����¸��������˸�����

	// TCHAR��һ����,��������㵱ǰ����Ŀ�ı�����ַ���ת��Ϊ�㵱ǰ�ı���,�����ڿ�ƽ̨
	TCHAR stzSr[] = TEXT("�й�");

	// �ַ���ָ�룺
	// Ascii
	PSTR  pszStr = "�й�"; //Pͨ����ʾָ��,����ϰ����P��ͷ����ʾָ��

	// Unicode
	PWSTR pwszStr = L"�й�"; //Pͨ����ʾָ��,����ϰ����P��ͷ����ʾָ��

	// PTSTR��һ����,��������㵱ǰ����Ŀ�ı�����ַ���ת��Ϊ�㵱ǰ�ı���,�����ڿ�ƽ̨,�Ժ��ַ����Ƽ�ʹ�����
	PTSTR ptszStr = TEXT("�й�");
/*
	MassageBox�������ڵ���һ����Ϣ��

	int MessageBox(
		HWND hWnd,          // ���ھ��
		LPCTSTR lpText,     // Ҫ��ʾ����Ϣ
		LPCTSTR lpCaption,  // ��Ϣ�����
		UINT uType			// ��Ϣ����ʽ
	);
*/
	// Ascii
	CHAR szTitle[] = "����";
	CHAR szContent[] = "��ӭ�����WIN32 API������";
	printf(szContent); // ����̨����CHAR���͵���printf
	MessageBoxA(0,szContent,szTitle,MB_OK);

	// Unicode
	WCHAR swzTitle[] = L"����";
	WCHAR swzContent[] = L"��ӭ�������Win32 API����!";
	wprintf(swzContent); // ����̨����WCHAR���͵���wprintf
	MessageBoxW(0,swzContent,swzTitle,MB_OK);

	// ��
	TCHAR stzTitle[] = TEXT("����");
	TCHAR stzContent[] = TEXT("��ӭ�������Win32 API����!");

	// _tprintf��һ����,�������ú�printfһ��
	_tprintf(stzContent);
	MessageBox(0,stzContent,stzTitle,MB_OK);

	getchar();
	return 0;
}

