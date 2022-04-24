// 01-C语言中的宽字符.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"


int _tmain(int argc, _TCHAR* argv[])
{
	// ascii编码的字符串,观察反汇编,它在内存中的存储方式是以00结尾
	char szStr[] = "中国"; 
	
	// unicode编码的字符串,准确的说是UTF-16,它是由2个00 00结尾
	// 定义宽字节字符需要声明类型 wchar_t,而且字符串前面要加L
	wchar_t swzStr[] = L"中国";

	
	// 通过观察反汇编发现,其实ascii编码的中国占5个字节,其中包括一个 00,
	// unicode编码的中国占6个字节,其中包括两个 00 00

	/*
	编码的不同,那么在内存中的结构也完全发生了变化,意味着在使用这种字符串的时候,相应的处理函数也不同
	常用函数:
		//多字节字符类型   宽字符类型
		char				wchar_t		
		-----------------------------------------------------							
		printf				wprintf		//打印到控制台函数
								
		strlen				wcslen		//获取长度			
  
		strcpy				wcscpy		//字符串复制			
			
		strcat				wcscat		//字符串拼接			
			  
		strcmp				wcscmp		//字符串比较			
				
		strstr				wcsstr		//字符串查找
	*/

	// 使用控制台默认的编码
	setlocale(LC_ALL,"");
	printf("%s\n",szStr);
	wprintf(L"%s\n",swzStr);

	// 取得多字节字符串中字符长度，不包含 00

	size_t r1 = strlen(szStr);

	// 取得宽字节字符串中字符长度，不包含 00 00
	size_t r2 = wcslen(swzStr);

	printf("%d\n",r1);
	printf("%d\n",r2);

	getchar();
	return 0;
}

