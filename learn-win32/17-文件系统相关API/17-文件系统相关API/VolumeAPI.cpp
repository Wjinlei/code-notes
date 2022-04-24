#include "stdafx.h"

// ��ȡ��ǰϵͳ�ľ�
VOID TestGetDrives()
{
	/*
	// ��ȡ��ǰ�ľ�
	DWORD GetLogicalDrives(VOID);
	��������ɹ����򷵻�ֵ�Ǳ�ʾ��ǰ���ô�����������λ���롣
	λλ��0�������Чλ��Ϊ������A��λλ��1Ϊ������B��λλ��2Ϊ������C���������ơ�
	�������ʧ�ܣ�����ֵΪ�㡣 Ҫ��ȡ��չ������Ϣ�������GetLastError��
	*/
	DWORD dwDrives = GetLogicalDrives();
	printf("�뽫��ת����2����: %x\n", dwDrives); //10000000000000000000001100 һ��28λ,��ʾC��D��Z
}

VOID TestGetDriveString()
{
	/*
	// ��ȡһ�����ھ���̷����ַ���
	DWORD GetLogicalDriveStrings(
		DWORD nBufferLength,  // ��ȡ�ĳ���
		LPTSTR lpBuffer       // �ṩһ��������,����ѵõ����ַ������Ƶ����������
	);
	��������ɹ����򷵻�ֵ�Ǹ��Ƶ����������ַ����ĳ��ȣ����ַ�Ϊ��λ��
	����������ֹ���ַ��� ��ע�⣬ANSI-ASCII���ַ�ʹ��һ���ֽڣ���Unicode���ַ�ʹ�������ֽڡ�
	��������������󣬷���ֵ����nBufferLength�� ����������������Ļ������Ĵ�С��
	�������ʧ�ܣ�����ֵΪ�㡣 Ҫ��ȡ��չ������Ϣ����ʹ��GetLastError������
	*/

	DWORD dwMaxLength = 100;
	TCHAR szBuffer[100];
	GetLogicalDriveStrings(dwMaxLength,szBuffer);

	printf("DriveString: %s\n",szBuffer);
}

// ��ȡ�������
VOID TestGetDriveType()
{
	/*
	��ȡ�������,�������ǹ�����,�����߼���
	UINT GetDriveType(
		LPCTSTR lpRootPathName   //ָ����Ŀ¼,���lpRootPathNameΪNULL����ú���ʹ�õ�ǰĿ¼�ĸ���
	);
	����ֵ:
	DRIVE_UNKNOWN		0	���������޷�ȷ��. 
	DRIVE_NO_ROOT_DIR	1	��·������Ч�ġ����磬��·����û�а�װ��
	DRIVE_REMOVABLE		2	���̿��Դ���������ɾ����
	DRIVE_FIXED			3	���̲��ܴ���������ɾ����
	DRIVE_REMOTE		4	drive��һ��Զ��(����)��������
	DRIVE_CDROM			5	��������һ��CD-ROM��������
	DRIVE_RAMDISK		6	��������һ��RAM���̡� 
	*/

	UINT uType = GetDriveType(TEXT("C:\\"));
	printf("%d\n", uType);
}

// ��ȡ�����ϸ��Ϣ
VOID TestGetDriveInfo()
{
	/*
	��ȡ�����ϸ��Ϣ
	BOOL GetVolumeInformation(
		LPCTSTR lpRootPathName,           // IN ��Ŀ¼
		LPTSTR lpVolumeNameBuffer,        // OUT �������������
		DWORD nVolumeNameSize,            // IN  ��곤��,��һ����ľ�������ر�,����ȡ������?��������ָ��
		LPDWORD lpVolumeSerialNumber,     // OUT ������к�(��Ҫ��Ӳ�����кŻ�Ϊһ̸)
		LPDWORD lpMaximumComponentLength, // OUT ϵͳ���������ļ�������
		LPDWORD lpFileSystemFlags,        // OUT �ļ�ϵͳ��ʶ
		LPTSTR lpFileSystemNameBuffer,    // OUT �ļ�ϵͳ����
		DWORD nFileSystemNameSize         // OUT �ļ�ϵͳ���Ƴ���,��һ����ľ��ļ�ϵͳ�����ر�,����ȡ������?��������ָ��
	);
	*/
	TCHAR szVolumneName[260] = {0}; // �������
	DWORD dwVolumneSerial = 0; // ������к�
	DWORD MaxLength = 0; // ���������ļ�������
	DWORD dwFileSystem = 0; // �ļ�ϵͳ��ʶ
	TCHAR szFileSystem[260] = {0}; // �ļ�ϵͳ����
	GetVolumeInformation(TEXT("C:\\"),szVolumneName,260,&dwVolumneSerial,&MaxLength,&dwFileSystem,szFileSystem,260);

	printf("�����: %s\n",szVolumneName);
	printf("������к�: %d\n",dwVolumneSerial);
	printf("ϵͳ���е�����ļ�������: %d\n",MaxLength);
	printf("�ļ�ϵͳ��ʶ: %d\n",dwFileSystem);
	printf("�ļ�ϵͳ����: %s\n",szFileSystem);

}