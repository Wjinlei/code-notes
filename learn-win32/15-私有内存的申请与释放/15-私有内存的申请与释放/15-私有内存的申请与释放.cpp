// 15-私有内存的申请与释放.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

/*
在说私有内存前先来看几个概念

什么是物理页?
答:
操作系统为了便于物理内存的管理,所以在inter x86架构里面,它把物理内存按照4kb的方式分成一页一页的。
这就是为什么我们管物理内存叫做页式管理的原因
每个进程所使用的物理页是不一样的。所以说物理页就是4kb的内存

每个进程的4GB内存是真实存在的吗?
答:
我们知道每一个进程都有一个私有的4GB的内存空间,那么这4GB空间是真实存在的么?
当然不是,它是用多少就申请多少物理页。没有用到的地方就不会挂物理页。所以说它是假的4GB
这个我们称为每个进程的虚拟内存,为了和下面的虚拟内存的概念区分,这里我们就叫它假内存

什么是物理内存?
答:
就是物理页(内存条),物理页的多少,和内存条大小有关,内存条越大,可用的物理页越多

什么是虚拟内存?
答:
当物理页不够用时,操作系统会把硬盘划出一块空间来当作内存来使用,我们把这块空间叫做虚拟内存

已分配的假内存会一直有物理页吗?
答:
不见得,如果当前进程访问已分配的假内存不是很频繁,那么操作系统就会把其物理页中的内容存储到硬盘(虚拟内存)中
当下一次再访问该内存的时候,会触发一个缺页异常,这时操作系统会重新分配一个物理页给你。
因此,总结: 已分配的假内存不一定有物理页,没有分配的假内存是一定不会挂物理页的

什么是私有内存?
一个物理页只能被一个进程使用(独占物理页),这种内存我们称之为私有内存(private)

什么是共享内存?
一个物理页可以被多个进程使用(共享物理页),这种内存我们称之为共享内存(Mapping)
*/

int _tmain(int argc, _TCHAR* argv[])
{
	/* VirtualAlloc 只能在当前进程申请内存,换句话说就是只能给自己申请

	LPVOID VirtualAlloc // 该函数的返回值是: 申请到的内存的开始地址的指针
	(
		LPVOID lpAddress,
		// 要分配的内存区域的地址,我们可以手动指定一个地址,但通常不需要指定,因为如果指定到已分配的空间那内存申请一定是失败的
		
		DWORD dwSize, 
		// 分配的大小,页的整数倍(一个页:十进制4096,十六进制0x1000)

		DWORD flAllocationType, 
		// 分配的类型,开发中常用MEM_COMMIT、MEM_RESERVE
			MEM_COMMIT: 把这块内存给我保留,并且告诉操作系统,现在就需要物理内存(会立即给你分配物理页)
			MEM_RESERVE: 把这块内存给我保留,但是我现在不需要用(就不会给你分实际的物理页,只是把这块内存给你保留起来)

		DWORD flProtect 		
		// 该内存的初始保护属性
			PAGE_READONLY(只读)、
			PAGE_READWRITE(读写)、
			PAGE_EXECUTE(能够执行代码)、
			PAGE_EXECUTE_READ(既能读,又能执行代码)、
			PAGE_EXECUTE_READWRITE(既能读写,又能执行代码)
	);

	// VirtualAllocEx 这个函数可以在别的进程里面申请内存,换句话说就是可以给别的进程申请内存

	LPVOID WINAPI VirtualAllocEx(
	__in      HANDLE hProcess, //进程句柄
	__in_opt  LPVOID lpAddress,
	__in      SIZE_T dwSize,
	__in      DWORD flAllocationType,
	__in      DWORD flProtect
	);

	*/
	LPVOID p = VirtualAlloc(NULL,0x1000*2,MEM_COMMIT,PAGE_READWRITE);


	/*
	BOOL VirtualFree(
		LPVOID lpAddress,   // 申请的内存从哪里开始的?
		SIZE_T dwSize,      // 要释放的内存有多大?
		DWORD dwFreeType    
		// 要释放的类型是什么?
			MEM_DECOMMIT 虚拟地址仍然保留,但是不给你留物理页了,
			MEM_RELEASE 不但物理页不给你留,虚拟地址也不给你留了,但是使用MEM_RELEASE的时候,dwSize必须填0
	);
	*/
	VirtualFree(p,0,MEM_RELEASE); //也就意味着这是完全释放掉

	return 0;
}

