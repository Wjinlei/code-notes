// 01-C�����еĿ��ַ�.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"


int _tmain(int argc, _TCHAR* argv[])
{
	// ascii������ַ���,�۲췴���,�����ڴ��еĴ洢��ʽ����00��β
	char szStr[] = "�й�"; 
	
	// unicode������ַ���,׼ȷ��˵��UTF-16,������2��00 00��β
	// ������ֽ��ַ���Ҫ�������� wchar_t,�����ַ���ǰ��Ҫ��L
	wchar_t swzStr[] = L"�й�";

	
	// ͨ���۲췴��෢��,��ʵascii������й�ռ5���ֽ�,���а���һ�� 00,
	// unicode������й�ռ6���ֽ�,���а������� 00 00

	/*
	����Ĳ�ͬ,��ô���ڴ��еĽṹҲ��ȫ�����˱仯,��ζ����ʹ�������ַ�����ʱ��,��Ӧ�Ĵ�����Ҳ��ͬ
	���ú���:
		//���ֽ��ַ�����   ���ַ�����
		char				wchar_t		
		-----------------------------------------------------							
		printf				wprintf		//��ӡ������̨����
								
		strlen				wcslen		//��ȡ����			
  
		strcpy				wcscpy		//�ַ�������			
			
		strcat				wcscat		//�ַ���ƴ��			
			  
		strcmp				wcscmp		//�ַ����Ƚ�			
				
		strstr				wcsstr		//�ַ�������
	*/

	// ʹ�ÿ���̨Ĭ�ϵı���
	setlocale(LC_ALL,"");
	printf("%s\n",szStr);
	wprintf(L"%s\n",swzStr);

	// ȡ�ö��ֽ��ַ������ַ����ȣ������� 00

	size_t r1 = strlen(szStr);

	// ȡ�ÿ��ֽ��ַ������ַ����ȣ������� 00 00
	size_t r2 = wcslen(swzStr);

	printf("%d\n",r1);
	printf("%d\n",r2);

	getchar();
	return 0;
}

