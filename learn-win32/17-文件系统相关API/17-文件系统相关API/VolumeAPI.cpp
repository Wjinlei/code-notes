#include "stdafx.h"

// 获取当前系统的卷
VOID TestGetDrives()
{
	/*
	// 获取当前的卷
	DWORD GetLogicalDrives(VOID);
	如果函数成功，则返回值是表示当前可用磁盘驱动器的位掩码。
	位位置0（最低有效位）为驱动器A，位位置1为驱动器B，位位置2为驱动器C，依此类推。
	如果函数失败，返回值为零。 要获取扩展错误信息，请调用GetLastError。
	*/
	DWORD dwDrives = GetLogicalDrives();
	printf("请将它转换成2进制: %x\n", dwDrives); //10000000000000000000001100 一共28位,表示C、D、Z
}

VOID TestGetDriveString()
{
	/*
	// 获取一个所在卷的盘符的字符串
	DWORD GetLogicalDriveStrings(
		DWORD nBufferLength,  // 获取的长度
		LPTSTR lpBuffer       // 提供一个缓冲区,它会把得到的字符串复制到这个缓冲区
	);
	如果函数成功，则返回值是复制到缓冲区的字符串的长度（以字符为单位）
	，不包括终止空字符。 请注意，ANSI-ASCII空字符使用一个字节，但Unicode空字符使用两个字节。
	如果缓冲区不够大，返回值大于nBufferLength。 保持驱动器串所需的缓冲区的大小。
	如果函数失败，返回值为零。 要获取扩展错误信息，请使用GetLastError函数。
	*/

	DWORD dwMaxLength = 100;
	TCHAR szBuffer[100];
	GetLogicalDriveStrings(dwMaxLength,szBuffer);

	printf("DriveString: %s\n",szBuffer);
}

// 获取卷的类型
VOID TestGetDriveType()
{
	/*
	获取卷的类型,例如你是光驱啊,还是逻辑卷啊
	UINT GetDriveType(
		LPCTSTR lpRootPathName   //指定根目录,如果lpRootPathName为NULL，则该函数使用当前目录的根。
	);
	返回值:
	DRIVE_UNKNOWN		0	驱动类型无法确定. 
	DRIVE_NO_ROOT_DIR	1	根路径是无效的。例如，在路径上没有安装卷。
	DRIVE_REMOVABLE		2	磁盘可以从驱动器中删除。
	DRIVE_FIXED			3	磁盘不能从驱动器中删除。
	DRIVE_REMOTE		4	drive是一个远程(网络)驱动器。
	DRIVE_CDROM			5	驱动器是一个CD-ROM驱动器。
	DRIVE_RAMDISK		6	驱动器是一个RAM磁盘。 
	*/

	UINT uType = GetDriveType(TEXT("C:\\"));
	printf("%d\n", uType);
}

// 获取卷的详细信息
VOID TestGetDriveInfo()
{
	/*
	获取卷的详细信息
	BOOL GetVolumeInformation(
		LPCTSTR lpRootPathName,           // IN 根目录
		LPTSTR lpVolumeNameBuffer,        // OUT 驱动器卷标名称
		DWORD nVolumeNameSize,            // IN  卷标长度,万一上面的卷标名字特别长,那我取多少呢?就是这里指定
		LPDWORD lpVolumeSerialNumber,     // OUT 卷标序列号(不要和硬盘序列号混为一谈)
		LPDWORD lpMaximumComponentLength, // OUT 系统允许的最大文件名长度
		LPDWORD lpFileSystemFlags,        // OUT 文件系统标识
		LPTSTR lpFileSystemNameBuffer,    // OUT 文件系统名称
		DWORD nFileSystemNameSize         // OUT 文件系统名称长度,万一上面的卷文件系统名称特别长,那我取多少呢?就是这里指定
	);
	*/
	TCHAR szVolumneName[260] = {0}; // 卷标名称
	DWORD dwVolumneSerial = 0; // 卷标序列号
	DWORD MaxLength = 0; // 允许的最大文件名长度
	DWORD dwFileSystem = 0; // 文件系统标识
	TCHAR szFileSystem[260] = {0}; // 文件系统名称
	GetVolumeInformation(TEXT("C:\\"),szVolumneName,260,&dwVolumneSerial,&MaxLength,&dwFileSystem,szFileSystem,260);

	printf("卷标名: %s\n",szVolumneName);
	printf("卷标序列号: %d\n",dwVolumneSerial);
	printf("系统运行的最大文件名长度: %d\n",MaxLength);
	printf("文件系统标识: %d\n",dwFileSystem);
	printf("文件系统名称: %s\n",szFileSystem);

}