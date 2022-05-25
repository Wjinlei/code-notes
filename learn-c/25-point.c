#include <stdio.h>

/* 指针与数组 */

int main(int argc, char* argv[])
{
        int a[] = { 1, 2, 3, 4, 5 };
        /* int* pa = &a[0]; */
        /* 由于a做右值使用时和&a[0]是一个意思，所以int *pa = &a[0];通常不这么写，而是写成更简洁的形式int *pa = a;。*/
        int* pa = a;
        long* pb = (long*)a;

        printf("%d\n", *(pa + 1)); // ?
        printf("%d\n", *(pa + 2)); // ?

        /* 指针的++ -- */
        printf("%d\n", *pa++); // 1
        printf("%d\n", *pa++); // 2

        printf("%d\n", *pa--); // ?
        printf("%d\n", *pa--); // ?

        printf("%d\n", *pb++); // 1
        printf("%d\n", *pb++); // 3

        printf("%d\n", *pb--); // ?
        printf("%d\n", *pb--); // ?
        return 0;
}
