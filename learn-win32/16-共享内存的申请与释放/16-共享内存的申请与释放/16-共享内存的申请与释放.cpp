// 16-�����ڴ���������ͷ�.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

// �ȿ���صĺ���
/*
HANDLE CreateFileMapping(
	HANDLE hFile,                       // ���ָ�����ļ�,��ô�Ὣ���������ҳ������ļ������
	LPSECURITY_ATTRIBUTES lpAttributes, // ��ȫ������
	DWORD flProtect,                    
	// ׼���������ڴ�ʲô����
		PAGE_READONLY(ֻ��,)��
		PAGE_READWRITE(�ɶ�д)��
		PAGE_WRITECOPY(д����)
	DWORD dwMaximumSizeHigh,            // ��32λ��ֵ,32λ����������ֵû����,��0����,��Ϊ32λ����������ܳ���32λ
	DWORD dwMaximumSizeLow,             // ��32λ��ֵ,�ò���ָ����Ҫ�����ڴ�
	LPCTSTR lpName                      // ����ں˶��������,�����Ҫ�ڶ�������ﹲ������ں˶����ʱ��,�Ϳ��Ը�һ������,���ֻ�����Լ��Ľ�����ʹ��,������NULL����

  ����ɹ�����FileMapping������,����ö����Ѿ�����,��Ȼ���ش��ڵĶ�����,ֻ������ʱ����GetLastEerror�᷵��һ��ERROR_ALREADY_EXISTS
);
*/

/*
LPVOID MapViewOfFile(
	HANDLE hFileMappingObject,   // ��Ҫӳ���FileMapping����ľ��
	DWORD dwDesiredAccess,       
	// ����Ȩ��,����ָ�����������ڴ������
		FILE_MAP_WRITE(��д,ǰ������PAGE_READWRITE����������ҳ����)��
		FILE_MAP_READ(ֻ��,ǰ����PAGE_READONLY��PAGE_READWRITE)
	DWORD dwFileOffsetHigh,      // ��32λ��ֵ,32λ����������ֵû����,��0����,��Ϊ32λ����������ܳ���32λ
	DWORD dwFileOffsetLow,       // ��32λ��ֵ,�ò���ָ����Ҫ�����￪ʼӳ��,�����Ҫ�ӿ�ʼ����ʼӳ�����0,����һ��ƫ��
	SIZE_T dwNumberOfBytesToMap  // ����ָ����Ҫӳ�����,��ô������dwMaximumSizeLow�Ƕ���,�����ӳ�����

// ��������ķ���ֵ��һ�� ӳ��õ������ַ
);
*/

HANDLE g_hMapFile;
LPTSTR g_lpBuff;

int _tmain(int argc, _TCHAR* argv[])
{
	// ������������Ҫһ�������ڴ�,��ô��һ����������дINVALID_HANDLE_VALUE,����ʵ��һ����,����ʾ��Ч���ļ����
	g_hMapFile = CreateFileMapping(INVALID_HANDLE_VALUE,NULL,PAGE_READWRITE,0,0x1000,TEXT("�����ڴ�"));

	// ӳ�������ַ,��Ϊ������������ҳ,û�н�����ϵ��û�취��,�൱�������ڴ������ҳ֮���ӳ��
	g_lpBuff = (LPTSTR)MapViewOfFile(g_hMapFile,FILE_MAP_WRITE,0,0,0x1000);

	// ��g_lpBuff����ڴ��ַ��ֵ,������ֵΪ0x12345678(����Ǹ��������ʹ��)
	*(PDWORD)g_lpBuff = 0x12345678; 

	// ��ӡ����ڴ��ַ,ע�ⲻ�Ǵ�ӡֵ
	printf("%p",g_lpBuff); 

	getchar();

	// �ر�ӳ��
	UnmapViewOfFile(g_lpBuff); // ����ǰ������ҳ����������ڴ��ַ֮���ӳ���ϵȥ��

	// �رվ��
	CloseHandle(g_hMapFile); // �رվ����һ����ʾ���ں˶���һ��������

	getchar();
	return 0;
}

