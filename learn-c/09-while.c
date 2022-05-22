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

int main(int argc, char* argv[])
{
        printf("%d\n", factorial(3));
        return 0;
}
