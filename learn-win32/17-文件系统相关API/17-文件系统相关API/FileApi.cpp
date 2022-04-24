#include "stdafx.h"

// �����ļ�
VOID TestCreateFileApi()
{
	/* �����ļ�
	HANDLE CreateFile(
		LPCTSTR lpFileName,                         // �ļ���,������·��
		DWORD dwDesiredAccess,                      // ����ģʽ,����ο�API
		DWORD dwShareMode,                          
		// ����ģʽ,
			FILE_SHARE_DELETE����û�в�����֮ǰ���˿���ɾ,
			FILE_SHARE_READͬ����Զ�,
			FILE_SHARE_WRITEͬ�����д,
			�����0,��ʾ����û�в�����֮ǰ,������ʲô����Ҳ������,�൱�ڻ���
		LPSECURITY_ATTRIBUTES lpSecurityAttributes, // ��ȫ������
		DWORD dwCreationDisposition,                // ʲôʱ�򴴽�,����ο�API
		DWORD dwFlagsAndAttributes,                 // �ļ�����,����ο�API
		HANDLE hTemplateFile                        // handle to template file �����дNULL����,һ���ò���
	);
	*/
	HANDLE hFile = CreateFile(
		TEXT("TestFile.txt"),
		GENERIC_READ|GENERIC_WRITE,
		0,
		NULL,
		CREATE_ALWAYS, 
		// �����ļ���: CREATE_ALWAYS
		// ���ļ���: OPEN_ALWAYS
		FILE_ATTRIBUTE_NORMAL,
		NULL
		);

	// �ر��ļ�
	CloseHandle(hFile);
}

// ��ȡ�ļ���С
VOID TestGetFileSize()
{
	HANDLE hFile = CreateFile(
		TEXT("TestFile.txt"),
		GENERIC_READ|GENERIC_WRITE,
		0,
		NULL,
		OPEN_ALWAYS, 
		// �����ļ���: CREATE_ALWAYS
		// ���ļ���: OPEN_ALWAYS
		FILE_ATTRIBUTE_NORMAL,
		NULL
		);

	/*
	// ��ȡ�ļ���С
	DWORD GetFileSize(
		HANDLE hFile,           // �ļ����
		LPDWORD lpFileSizeHigh  // ���ֵ��NULL����
	*/
	DWORD dwSize = GetFileSize(hFile,NULL);
	DWORD r = GetLastError();
	printf("GetLastError: %d\n",r);
	printf("�ļ���С: %d\n",dwSize);

	// �ر��ļ�
	CloseHandle(hFile);
}

// ��ȡ�ļ�������
VOID TestGetFileAttributesEx()
{
/*
//��ȡ�ļ������Ժ���Ϣ
BOOL GetFileAttributesEx(
	LPCTSTR lpFileName,                   // �ļ���Ŀ¼��,������·��
	GET_FILEEX_INFO_LEVELS fInfoLevelId,  // ����ֻ��д���,û�п�ѡ��GetFileExInfoStandard
	LPVOID lpFileInformation              // ��ȡ���Ľ����洢������ṹ����
);
*/

/*
typedef struct _WIN32_FILE_ATTRIBUTE_DATA {
DWORD    dwFileAttributes; // ����ֵ
FILETIME ftCreationTime; // ��󴴽�ʱ��
FILETIME ftLastAccessTime; // ������ʱ��
FILETIME ftLastWriteTime; // ����޸�ʱ��
DWORD    nFileSizeHigh; // �ļ���С, ��32λ
DWORD    nFileSizeLow; // �ļ���С, ��32λ
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

	// ����ʱ����ϵͳʱ��Ķ�����SYSTEMTIME�ṹ���洢��
	SYSTEMTIME utctime;
	SYSTEMTIME ltime;
	// ��FILETIMEת��ΪSYSTEMTIME(ϵͳʱ��)
	FileTimeToSystemTime(&data.ftCreationTime,&utctime);
	// ��SYSTEMTIMEת��ΪLOCALTIME(����ʱ��)
	SystemTimeToTzSpecificLocalTime(NULL,&utctime,&ltime);

	/* ʱ��ת�����API
	// ��FILETIME(�ļ�ʱ��)ת��ΪSYSTEMTIME(ϵͳʱ��)
	FileTimeToSystemTime(&data.ftCreationTime,&utctime);

	// ��SYSTEMTIME(ϵͳʱ��)ת��ΪFILETIME(�ļ�ʱ��)
	SystemTimeToFileTime

	// ��SYSTEMTIME(ϵͳʱ��)ת��ΪLOCALTIME(����ʱ��)
	SystemTimeToTzSpecificLocalTime(NULL,&utctime,&ltime);

	// ��LOCALTIME(����ʱ��)ת��ΪSYSTEMTIME(ϵͳʱ��)
	TzSpecificLocalTimeToSystemTime

	// �������ļ�ʱ��ת��Ϊ�ļ�ʱ��(UTC)
	LocalFileTimeToFileTime

	// ���ļ�ʱ��(UTC)ת��Ϊ�����ļ�ʱ��
	FileTimeToLocalFileTime

	// ��ȡUTCʱ��
	GetSystemTime(&sysTm);

	// ��ȡ��ʱ��ʱ��
	GetLocalTime(&locTm);                               

	*/
	printf("UTC��������: %d �� %d �� %d �� %02d �� %02d �� %02d ��\n",ltime.wYear,ltime.wMonth,ltime.wDay,ltime.wHour,ltime.wMinute,ltime.wSecond);
}

// ��ȡ����
VOID TestReadFile()
{
	/*
	//���ļ�
	BOOL ReadFile(
		HANDLE hFile,                // �ļ����
		LPVOID lpBuffer,             // ��������?�ṩһ��Buffer
		DWORD nNumberOfBytesToRead,  // Ҫ�����ٸ��ֽ�
		LPDWORD lpNumberOfBytesRead, // OUT�Ͳ���,�������˶��ٸ��ֽ�,�᷵�ص����ָ����
		LPOVERLAPPED lpOverlapped    // overlapped buffer
	);
	*/
	
	// ���ļ�
	HANDLE hFile = CreateFile(
		TEXT("TestFile.txt"),
		GENERIC_READ|GENERIC_WRITE,
		0,
		NULL,
		OPEN_ALWAYS, 
		// �����ļ���: CREATE_ALWAYS
		// ���ļ���: OPEN_ALWAYS
		FILE_ATTRIBUTE_NORMAL,
		NULL
		);

	// ����ռ�
	LPSTR pszBuffer = (LPSTR)malloc(0x1000);

	// ��ʼ��
	ZeroMemory(pszBuffer,0x1000);


	// ���ô��Ŀ�ʼ��
	SetFilePointer(hFile,0,NULL,FILE_BEGIN); //���ļ���ʼ�ĵط�,0����ֽڿ�ʼ��

	// ��ȡ����
	DWORD dwReadLength = 0;
	ReadFile(hFile,pszBuffer,0x1000,&dwReadLength,NULL);

	// ��ӡ����
	printf(pszBuffer);

	// �ͷ��ڴ�
	free(pszBuffer);

	// �ر��ļ�
	CloseHandle(hFile);
}

// д������
VOID TestWriteFile()
{
	/*
	//д�ļ�
	BOOL WriteFile(
		HANDLE hFile,                    // �ļ����
		LPCVOID lpBuffer,                // д������?�ṩһ��Buffer
		DWORD nNumberOfBytesToWrite,     // Ҫд���ٸ��ֽ�
		LPDWORD lpNumberOfBytesWritten,  // OUT�Ͳ���,����д�˶��ٸ��ֽ�,�᷵�ص����ָ����
		LPOVERLAPPED lpOverlapped        // overlapped buffer
	);
	*/

	// ���ļ�
	HANDLE hFile = CreateFile(
		TEXT("TestFile.txt"),
		GENERIC_READ|GENERIC_WRITE,
		0,
		NULL,
		OPEN_ALWAYS, 
		// �����ļ���: CREATE_ALWAYS
		// ���ļ���: OPEN_ALWAYS
		FILE_ATTRIBUTE_NORMAL,
		NULL
		);


	// Ҫд������
	CHAR szBuffer[] = "�й�";

	// ���ô��Ŀ�ʼд
	SetFilePointer(hFile,0,NULL,FILE_END); //�����ʼд��

	// д����
	DWORD dwReadLength = 0;
	WriteFile(hFile,szBuffer,strlen(szBuffer),&dwReadLength,NULL);
	
	// �ر��ļ�
	CloseHandle(hFile);
}

// �����ļ�
VOID TestCopyFile()
{
	/*
	//�����ļ�
	BOOL CopyFile(
		LPCTSTR lpExistingFileName, // ԭ�ļ���,����·��
		LPCTSTR lpNewFileName,      // Ŀ���ļ���,����·��
		BOOL bFailIfExists          // TRUE�������ļ��Ѵ���,�򷵻�FALSE,���FALSE,�򸲸�
	);
	*/

	CopyFile(TEXT("TestFile.txt"),TEXT("TestFile.txt.COPY"),FALSE);
	DWORD lastcode = GetLastError();
	printf("lastcode = %d\n",lastcode);
}

// �����ļ�
VOID FindFile()
{
	/*
	//ͨ���ļ��������ļ�
	HANDLE FindFirstFile(
		LPCTSTR lpFileName,               // �ļ���,����·��
		LPWIN32_FIND_DATA lpFindFileData  // ���ҵ����ļ���Ŀ¼��Ϣ�᷵�ص����ָ����ָ��Ľṹ����
	);
	*/

	/*
	//ͨ����������ļ�
	BOOL FindNextFile(
		HANDLE hFindFile,                // �ļ����
		LPWIN32_FIND_DATA lpFindFileData // ���ҵ����ļ���Ŀ¼��Ϣ�᷵�ص����ָ����ָ��Ľṹ����
	);
	*/
	WIN32_FIND_DATA fdata;
	FindFirstFile(TEXT("TestFile.txt"),&fdata);
	_tprintf(TEXT("%s;\n"),fdata.cFileName);
}

