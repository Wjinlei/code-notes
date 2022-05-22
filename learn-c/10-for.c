/* Copyright (c) 2022 Jerry. All Rights Reserved. */

#include <stdio.h>

/*
 * 前两节我们在while和do/while循环中使用循环变量，
 * 其实使用循环变量最见的是for循环这种形式。for语句的语法是：
 * for (控制表达式1; 控制表达式2; 控制表达式3) 语句
 * for循环中控制表达式1在整个循环中只执行一次
 * for循环中控制表达式2用于判断是否执行下一次循环,当条件满足则执行，否则跳出
 * for循环中控制表达式3每次循环后都要执行
 * 控制表达式1和3都可以为空，但控制表达式2是必不可少的
 * 例如for (;1;) {...}等价于while (1) {...}死循环。
 */

/*
 * 上一节do/while循环的例子可以改写成for循环：
 */
int factorial_c89(int n)
{
        int result = 1;
        int i; // C89
        for (i = 1; i <= n; ++i)
                result = result * i;
        return result;
}

/*  这个程序用gcc编译要加上选项-std=c99。
 *  这种语法也是从C++借鉴的，考虑到兼容性不建议使用这种写法。
 */
int factorial_c99(int n)
{
        int result = 1;
        /* C99规定了一种新的for循环语法，在控制表达式1的位置可以有变量定义。*/
        for (int i = 1; i <= n; i++)
                result = result * i;
        return result;
}

int main(int argc, char* argv[])
{
        printf("%d\n", factorial_c89(3));
        printf("%d\n", factorial_c99(3));
        return 0;
}
