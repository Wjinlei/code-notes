#include "stdafx.h"

// 创建文件
VOID TestCreateFileApi()
{
	/* 创建文件
	HANDLE CreateFile(
		LPCTSTR lpFileName,                         // 文件名,完整的路径
		DWORD dwDesiredAccess,                      // 访问模式,具体参考API
		DWORD dwShareMode,                          
		// 共享模式,
			FILE_SHARE_DELETE在我没有操作完之前别人可以删,
			FILE_SHARE_READ同理可以读,
			FILE_SHARE_WRITE同理可以写,
			如果填0,表示在我没有操作完之前,其他人什么操作也做不了,相当于互斥
		LPSECURITY_ATTRIBUTES lpSecurityAttributes, // 安全描述符
		DWORD dwCreationDisposition,                // 什么时候创建,具体参考API
		DWORD dwFlagsAndAttributes,                 // 文件属性,具体参考API
		HANDLE hTemplateFile                        // handle to template file 这个填写NULL即可,一般用不着
	);
	*/
	HANDLE hFile = CreateFile(
		TEXT("TestFile.txt"),
		GENERIC_READ|GENERIC_WRITE,
		0,
		NULL,
		CREATE_ALWAYS, 
		// 创建文件用: CREATE_ALWAYS
		// 打开文件用: OPEN_ALWAYS
		FILE_ATTRIBUTE_NORMAL,
		NULL
		);

	// 关闭文件
	CloseHandle(hFile);
}

// 获取文件大小
VOID TestGetFileSize()
{
	HANDLE hFile = CreateFile(
		TEXT("TestFile.txt"),
		GENERIC_READ|GENERIC_WRITE,
		0,
		NULL,
		OPEN_ALWAYS, 
		// 创建文件用: CREATE_ALWAYS
		// 打开文件用: OPEN_ALWAYS
		FILE_ATTRIBUTE_NORMAL,
		NULL
		);

	/*
	// 获取文件大小
	DWORD GetFileSize(
		HANDLE hFile,           // 文件句柄
		LPDWORD lpFileSizeHigh  // 这个值填NULL即可
	*/
	DWORD dwSize = GetFileSize(hFile,NULL);
	DWORD r = GetLastError();
	printf("GetLastError: %d\n",r);
	printf("文件大小: %d\n",dwSize);

	// 关闭文件
	CloseHandle(hFile);
}

// 获取文件的属性
VOID TestGetFileAttributesEx()
{
/*
//获取文件的属性和信息
BOOL GetFileAttributesEx(
	LPCTSTR lpFileName,                   // 文件或目录名,完整的路径
	GET_FILEEX_INFO_LEVELS fInfoLevelId,  // 这里只能写这个,没有可选的GetFileExInfoStandard
	LPVOID lpFileInformation              // 获取到的结果会存储到这个结构体中
);
*/

/*
typedef struct _WIN32_FILE_ATTRIBUTE_DATA {
DWORD    dwFileAttributes; // 属性值
FILETIME ftCreationTime; // 最后创建时间
FILETIME ftLastAccessTime; // 最后访问时间
FILETIME ftLastWriteTime; // 最后修改时间
DWORD    nFileSizeHigh; // 文件大小, 高32位
DWORD    nFileSizeLow; // 文件大小, 低32位
} WIN32_FILE_ATTRIBUTE_DATA, *LPWIN32_FILE_ATTRIBUTE_DATA;
*/
	WIN32_FILE_ATTRIBUTE_DATA data = {0};
	GetFileAttributesEx(TEXT("TestFile.txt"),GetFileExInfoStandard,&data);

	printf("dwFileAttributes = %d\n",data.dwFileAttributes);
	printf("ftCreationTime = %d\n",data.ftCreationTime);
	printf("ftLastAccessTime = %d\n",data.ftLastAccessTime);
	printf("ftLastWriteTime = %d\n",data.ftLastWriteTime);
	printf("nFileSizeHigh = %d\n",data.nFileSizeHigh);
	printf("nFileSizeLow = %d\n",data.nFileSizeLow);

	// 本地时间与系统时间的都是用SYSTEMTIME结构来存储的
	SYSTEMTIME utctime;
	SYSTEMTIME ltime;
	// 将FILETIME转换为SYSTEMTIME(系统时间)
	FileTimeToSystemTime(&data.ftCreationTime,&utctime);
	// 将SYSTEMTIME转换为LOCALTIME(本地时间)
	SystemTimeToTzSpecificLocalTime(NULL,&utctime,&ltime);

	/* 时间转换相关API
	// 将FILETIME(文件时间)转换为SYSTEMTIME(系统时间)
	FileTimeToSystemTime(&data.ftCreationTime,&utctime);

	// 将SYSTEMTIME(系统时间)转换为FILETIME(文件时间)
	SystemTimeToFileTime

	// 将SYSTEMTIME(系统时间)转换为LOCALTIME(本地时间)
	SystemTimeToTzSpecificLocalTime(NULL,&utctime,&ltime);

	// 将LOCALTIME(本地时间)转换为SYSTEMTIME(系统时间)
	TzSpecificLocalTimeToSystemTime

	// 将本地文件时间转换为文件时间(UTC)
	LocalFileTimeToFileTime

	// 将文件时间(UTC)转换为本地文件时间
	FileTimeToLocalFileTime

	// 获取UTC时间
	GetSystemTime(&sysTm);

	// 获取本时区时间
	GetLocalTime(&locTm);                               

	*/
	printf("UTC创建日期: %d 年 %d 月 %d 日 %02d 点 %02d 分 %02d 秒\n",ltime.wYear,ltime.wMonth,ltime.wDay,ltime.wHour,ltime.wMinute,ltime.wSecond);
}

// 读取数据
VOID TestReadFile()
{
	/*
	//读文件
	BOOL ReadFile(
		HANDLE hFile,                // 文件句柄
		LPVOID lpBuffer,             // 读到哪里?提供一个Buffer
		DWORD nNumberOfBytesToRead,  // 要读多少个字节
		LPDWORD lpNumberOfBytesRead, // OUT型参数,真正读了多少个字节,会返回到这个指针中
		LPOVERLAPPED lpOverlapped    // overlapped buffer
	);
	*/
	
	// 打开文件
	HANDLE hFile = CreateFile(
		TEXT("TestFile.txt"),
		GENERIC_READ|GENERIC_WRITE,
		0,
		NULL,
		OPEN_ALWAYS, 
		// 创建文件用: CREATE_ALWAYS
		// 打开文件用: OPEN_ALWAYS
		FILE_ATTRIBUTE_NORMAL,
		NULL
		);

	// 申请空间
	LPSTR pszBuffer = (LPSTR)malloc(0x1000);

	// 初始化
	ZeroMemory(pszBuffer,0x1000);


	// 设置从哪开始读
	SetFilePointer(hFile,0,NULL,FILE_BEGIN); //从文件开始的地方,0这个字节开始读

	// 读取数据
	DWORD dwReadLength = 0;
	ReadFile(hFile,pszBuffer,0x1000,&dwReadLength,NULL);

	// 打印数据
	printf(pszBuffer);

	// 释放内存
	free(pszBuffer);

	// 关闭文件
	CloseHandle(hFile);
}

// 写入数据
VOID TestWriteFile()
{
	/*
	//写文件
	BOOL WriteFile(
		HANDLE hFile,                    // 文件句柄
		LPCVOID lpBuffer,                // 写到哪里?提供一个Buffer
		DWORD nNumberOfBytesToWrite,     // 要写多少个字节
		LPDWORD lpNumberOfBytesWritten,  // OUT型参数,真正写了多少个字节,会返回到这个指针中
		LPOVERLAPPED lpOverlapped        // overlapped buffer
	);
	*/

	// 打开文件
	HANDLE hFile = CreateFile(
		TEXT("TestFile.txt"),
		GENERIC_READ|GENERIC_WRITE,
		0,
		NULL,
		OPEN_ALWAYS, 
		// 创建文件用: CREATE_ALWAYS
		// 打开文件用: OPEN_ALWAYS
		FILE_ATTRIBUTE_NORMAL,
		NULL
		);


	// 要写的数据
	CHAR szBuffer[] = "中国";

	// 设置从哪开始写
	SetFilePointer(hFile,0,NULL,FILE_END); //从最后开始写入

	// 写数据
	DWORD dwReadLength = 0;
	WriteFile(hFile,szBuffer,strlen(szBuffer),&dwReadLength,NULL);
	
	// 关闭文件
	CloseHandle(hFile);
}

// 复制文件
VOID TestCopyFile()
{
	/*
	//复制文件
	BOOL CopyFile(
		LPCTSTR lpExistingFileName, // 原文件名,完整路径
		LPCTSTR lpNewFileName,      // 目标文件名,完整路径
		BOOL bFailIfExists          // TRUE如果这个文件已存在,则返回FALSE,如果FALSE,则覆盖
	);
	*/

	CopyFile(TEXT("TestFile.txt"),TEXT("TestFile.txt.COPY"),FALSE);
	DWORD lastcode = GetLastError();
	printf("lastcode = %d\n",lastcode);
}

// 查找文件
VOID FindFile()
{
	/*
	//通过文件名查找文件
	HANDLE FindFirstFile(
		LPCTSTR lpFileName,               // 文件名,完整路径
		LPWIN32_FIND_DATA lpFindFileData  // 查找到的文件或目录信息会返回到这个指针所指向的结构体中
	);
	*/

	/*
	//通过句柄查找文件
	BOOL FindNextFile(
		HANDLE hFindFile,                // 文件句柄
		LPWIN32_FIND_DATA lpFindFileData // 查找到的文件或目录信息会返回到这个指针所指向的结构体中
	);
	*/
	WIN32_FIND_DATA fdata;
	FindFirstFile(TEXT("TestFile.txt"),&fdata);
	_tprintf(TEXT("%s;\n"),fdata.cFileName);
}

