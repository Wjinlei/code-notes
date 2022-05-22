/* Copyright (c) 2022 Jerry. All Rights Reserved. */

#include <stdio.h>

/*
 * 在C语言中，任何迭代(循环)程序都可以用递归来完成
 * 但C语言给我们提供了更方便的循环语句使迭代程序写起来更方便
 * while语句就是其中之一
 * 例如factorial函数用while语句可以写成
 */
int factorial(int n)
{
        int result = 1;
        /* 如果n>0满足条件,则进入循环,每循环一次后继续判断条件,当条件不满足则跳出循环 */
        while (n > 0) {
                result = result * n;
                n = n - 1;
        }
        return result;
}

/**
 * while语句先测试控制表达式的值再执行循环体，
 * 而do/while语句先执行循环体再测试控制表达式的值。
 * 如果控制表达式的值一开始就是假，while语句的循环体一次都不执行，
 * 而do/while语句的循环体仍然要执行一次再跳出循环。
 * 说白了，do/while和while的区别就是do/while至少要执行一次
 */
int factorial_do_while(int n)
{
        int result = 1;
        int i = 1;
        do {
                result = result * i;
                i = i + 1;
        } while (i <= n);

        return result;
}

int main(int argc, char* argv[])
{
        printf("%d\n", factorial(3));
        printf("%d\n", factorial_do_while(3));
        return 0;
}
