/* Copyright (c) 2022 Jerry. All Rights Reserved. */

#include <stdio.h>

/* 枚举类型
 * 枚举类型的成员是常量,它们的值由编译器自动分配
 * 枚举成语的值由0开始
 * 枚举常量也是一种整型，其值在编译时确定，因此也可以出现在常量表达式中，
 * 可以用于初始化全局变量或者作为case分支的判断条件。
 */
enum ENUM1 {
        AAA,
        BBB
};

/*
 * 如果不希望从0开始分配，可以这样定义：
 */
enum ENUM2 {
        /*
         * 有一点需要注意，虽然结构体的成员名和变量名不在同一命名空间中，
         * 但枚举的成员名却和变量名在同一命名空间中，
         * 所以会出现命名冲突。例如下面再定义AAA和BBB是不合法的：
         */
        // AAA = 1,
        // BBB,
        CCC = 1,
        DDD
};

int main(int argc, char* argv[])
{
        enum ENUM1 e1;
        e1 = BBB; // 枚举变量可以代表其任意一个成员

        printf("e1 = %d\n", e1);
        printf("%d\n", AAA);
        printf("%d\n", BBB);
        printf("%d\n", CCC);
        printf("%d\n", DDD);
        return 0;
}
