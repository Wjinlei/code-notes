/* Copyright (c) 2022 Jerry. All Rights Reserved. */

#include <stdio.h>

/* 定义一个结构体类型 */
struct complex_struct1 {
        double x, y;
};

/* 定义结构体类型时直接定义变量名z1, z2 */
struct complex_struct2 {
        double x, y;
} z1, z2;

/* 如果在定义结构体类型的同时定义了变量，也可以不必写Tag,但是不推荐这么写
 * 因为这样就没办法再次引用这个结构体类型了，因为它没有名字。
 */
struct {
        double x, y;
} z3, z4;

int main(int argc, char* argv[])
{

        /* 定义结构体complex_struct2后也可以直接用struct complex_struct2来代替类型名了。
         * 这样就可以在定义结构体后再定义变量
         */
        struct complex_struct2 z5, z6;

        /*
         * 可以用.运算符（.号，Period）来访问结构体中的成员。
         */
        double x = 3.0;
        z5.x = x;
        z5.y = 4.0;
        if (z5.y < 0) {
                printf("z=%f%fi\n", z5.x, z5.y);
        } else {
                printf("z=%f+%fi\n", z5.x, z5.y);
        }

        /* 结构体变量也可以在定义时初始化，例如：*/
        struct complex_struct2 z8 = { 3.0, 4.0 };

        /* Initializer中的数据依次赋给结构体的各成员。
         * 如果Initializer中的数据比结构体的成员多，编译器会报错，但如果只是末尾多个逗号则不算错。
         * 如果Initializer中的数据比结构体的成员少，未指定的成员将用0来初始化，就像未初始化的全局变量一样。
         */
        struct complex_struct2 z9 = {
                x,
                4.0,
        }; /* z1.x=3.0, z1.y=4.0 */
        struct complex_struct2 z10 = {
                3.0,
        }; /* z2.x=3.0, z2.y=0.0 */
        struct complex_struct2 z11 = { 0 }; /* z3.x=0.0, z3.y=0.0 */

        /* C99引入的新特性，用于初始化稀疏（Sparse）结构体和稀疏数组很方便。
         * 有些时候结构体或数组中只有某一个或某几个成员需要初始化，其它成员都用0初始化即
         * 这样就不必按顺序进行初始化
         */
        // struct complex_struct z12 = { .y = 4.0 }; /* z1.x=0.0, z1.y=4.0 */

        printf("z9 = %f+%f\n", z9.x, z9.y);
        printf("z10 = %f+%f\n", z10.x, z10.y);
        printf("z11 = %f+%f\n", z11.x, z11.y);
        return 0;
}
