// 16-共享内存的申请与释放.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

// 先看相关的函数
/*
HANDLE CreateFileMapping(
	HANDLE hFile,                       // 如果指定了文件,那么会将申请的物理页与这个文件相关联
	LPSECURITY_ATTRIBUTES lpAttributes, // 安全描述符
	DWORD flProtect,                    
	// 准备的物理内存什么属性
		PAGE_READONLY(只读,)、
		PAGE_READWRITE(可读写)、
		PAGE_WRITECOPY(写拷贝)
	DWORD dwMaximumSizeHigh,            // 高32位的值,32位计算机中这个值没有用,填0即可,因为32位计算机不可能超过32位
	DWORD dwMaximumSizeLow,             // 低32位的值,该参数指定你要多大的内存
	LPCTSTR lpName                      // 这个内核对象的名字,如果你要在多个进程里共用这个内核对象的时候,就可以给一个名字,如果只是在自己的进程里使用,那这里NULL就行

  如果成功返回FileMapping对象句柄,如果该对象已经存在,仍然返回存在的对象句柄,只不过这时候用GetLastEerror会返回一个ERROR_ALREADY_EXISTS
);
*/

/*
LPVOID MapViewOfFile(
	HANDLE hFileMappingObject,   // 你要映射的FileMapping对象的句柄
	DWORD dwDesiredAccess,       
	// 访问权限,这里指定的是虚拟内存的属性
		FILE_MAP_WRITE(读写,前提是用PAGE_READWRITE创建的物理页对象)、
		FILE_MAP_READ(只读,前提是PAGE_READONLY或PAGE_READWRITE)
	DWORD dwFileOffsetHigh,      // 高32位的值,32位计算机中这个值没有用,填0即可,因为32位计算机不可能超过32位
	DWORD dwFileOffsetLow,       // 低32位的值,该参数指定你要从哪里开始映射,如果你要从开始出开始映射就填0,这是一个偏移
	SIZE_T dwNumberOfBytesToMap  // 这里指定你要映射多少,那么你上面dwMaximumSizeLow是多少,这里就映射多少

// 这个函数的返回值是一个 映射好的虚拟地址
);
*/

HANDLE g_hMapFile;
LPTSTR g_lpBuff;

int _tmain(int argc, _TCHAR* argv[])
{
	// 如果你仅仅是想要一块物理内存,那么第一个参数可以写INVALID_HANDLE_VALUE,它其实是一个宏,它表示无效的文件句柄
	g_hMapFile = CreateFileMapping(INVALID_HANDLE_VALUE,NULL,PAGE_READWRITE,0,0x1000,TEXT("共享内存"));

	// 映射虚拟地址,因为光申请了物理页,没有建立联系就没办法用,相当于虚拟内存和物理页之间的映射
	g_lpBuff = (LPTSTR)MapViewOfFile(g_hMapFile,FILE_MAP_WRITE,0,0,0x1000);

	// 向g_lpBuff这个内存地址赋值,给他赋值为0x12345678(这就是告诉你如何使用)
	*(PDWORD)g_lpBuff = 0x12345678; 

	// 打印这个内存地址,注意不是打印值
	printf("%p",g_lpBuff); 

	getchar();

	// 关闭映射
	UnmapViewOfFile(g_lpBuff); // 将当前的物理页和这个虚拟内存地址之间的映射关系去掉

	// 关闭句柄
	CloseHandle(g_hMapFile); // 关闭句柄不一定表示该内核对象一定被销毁

	getchar();
	return 0;
}

