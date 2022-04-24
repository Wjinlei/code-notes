// 11-窗口的本质.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"


int _tmain(int argc, _TCHAR* argv[])
{
	/*
	什么是HWND? 答:HWND和HANDLE没有什么本质上的区别,HANDLE表示内核对象的句柄,HWND表示窗口的句柄
	*/
	HWND hwnd;

	/*
	什么是HDC? 设备上下文其实就是HWND它指向的窗口的内存,HDC就是一块内存,我们想要画任何东西都是先画到内存中,然后再显示出来
	所以我们想要向任何地方画东西,就必须先得到那个设备的内存才行.
	*/
	
	// 1.设备对象,这里可以写任何设备的句柄,如果写NULL则表示桌面
	hwnd = (HWND)NULL;

	// 2.获取设备对象上下文,其实就是获取你要画的对象的内存
	HDC hdc; //设备上下文
	hdc = GetDC(hwnd);

	// 3.创建画笔,设置线条属性
	HPEN hpen;
	hpen = CreatePen(PS_SOLID,5,RGB(0xFF,00,00));

	// 4.将画笔和HDC关联
	SelectObject(hdc,hpen);

	//5.开始画
	/*
	BOOL MoveToEx(
		HDC hdc,          // 设备上下文句柄
		int X,            // 起始X坐标
		int Y,            // 起始Y坐标
		LPPOINT lpPoint   // 原来的坐标,它指向一个结构体,保存了原来的坐标,如果你要要的话,就写个指针来接收,不要的话就写NULL
	);
	*/
	MoveToEx(hdc,0,400,NULL); //设置开始X坐标

	/*
	BOOL LineTo(
		HDC hdc,    // 设备上下文句柄
		int nXEnd,  // 结束的x坐标
		int nYEnd   // 结束的y坐标
	);
	*/

	LineTo(hdc,400,400);

	//释放资源
	DeleteObject(hpen);
	ReleaseDC(hwnd,hdc);

	return 0;
}

/*
总结:一句话,窗口是什么?窗口其实就是画出来的
*/