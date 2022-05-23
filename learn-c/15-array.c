/* Copyright (c) 2022 Jerry. All Rights Reserved. */

#include <stdio.h>

/* 数组（Array）也是一种复合数据类型，它由一系列相同类型的元素（Element）组成。*/

int main(int argc, char* argv[])
{
        /* 定义长度为4的int型数组,并为其赋初值,未赋初值的元素也是用0来初始化 */
        int count1[4] = {
                3,
                2,
        };
        int i;
        for (i = 0; i < 4; i++) {
                printf("count1[%d]=%d\n", i, count1[i]);
        }

        /*
         * 如果定义数组的同时初始化它，也可以不指定数组的长度,
         * 编译器会根据Initializer有三个元素确定数组的长度为3。
         */
        int count2[] = {
                3,
                2,
                1,
        };

        /* 数组不能相互赋值或初始化。例如这样是错的： */
        // int a[5] = { 4, 3, 2, 1 };
        // int b[5] = a;
        // a = b; // 相互赋值也是错误的

        /* 既然不能相互赋值，也就不能用数组类型作为函数的参数或返回值。*/
        return 0;
}
