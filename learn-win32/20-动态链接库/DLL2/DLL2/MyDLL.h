#pragma once

/*
第二种方法: 添加.def源文件,后缀名必须是.def
格式:

EXPORTS
函数名    @编号
函数名    @编号    NONAME   // 如果指定NONAME,则导出的函数没有名字, 只有编号

*/

// 定义还是要想原来那样照写
int add(int x, int y);

int sub(int x, int y);