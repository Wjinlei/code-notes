// 11-���ڵı���.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"


int _tmain(int argc, _TCHAR* argv[])
{
	/*
	ʲô��HWND? ��:HWND��HANDLEû��ʲô�����ϵ�����,HANDLE��ʾ�ں˶���ľ��,HWND��ʾ���ڵľ��
	*/
	HWND hwnd;

	/*
	ʲô��HDC? �豸��������ʵ����HWND��ָ��Ĵ��ڵ��ڴ�,HDC����һ���ڴ�,������Ҫ���κζ��������Ȼ����ڴ���,Ȼ������ʾ����
	����������Ҫ���κεط�������,�ͱ����ȵõ��Ǹ��豸���ڴ����.
	*/
	
	// 1.�豸����,�������д�κ��豸�ľ��,���дNULL���ʾ����
	hwnd = (HWND)NULL;

	// 2.��ȡ�豸����������,��ʵ���ǻ�ȡ��Ҫ���Ķ�����ڴ�
	HDC hdc; //�豸������
	hdc = GetDC(hwnd);

	// 3.��������,������������
	HPEN hpen;
	hpen = CreatePen(PS_SOLID,5,RGB(0xFF,00,00));

	// 4.�����ʺ�HDC����
	SelectObject(hdc,hpen);

	//5.��ʼ��
	/*
	BOOL MoveToEx(
		HDC hdc,          // �豸�����ľ��
		int X,            // ��ʼX����
		int Y,            // ��ʼY����
		LPPOINT lpPoint   // ԭ��������,��ָ��һ���ṹ��,������ԭ��������,�����ҪҪ�Ļ�,��д��ָ��������,��Ҫ�Ļ���дNULL
	);
	*/
	MoveToEx(hdc,0,400,NULL); //���ÿ�ʼX����

	/*
	BOOL LineTo(
		HDC hdc,    // �豸�����ľ��
		int nXEnd,  // ������x����
		int nYEnd   // ������y����
	);
	*/

	LineTo(hdc,400,400);

	//�ͷ���Դ
	DeleteObject(hpen);
	ReleaseDC(hwnd,hdc);

	return 0;
}

/*
�ܽ�:һ�仰,������ʲô?������ʵ���ǻ�������
*/