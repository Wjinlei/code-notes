#include <stdio.h>

/* 指针类型的参数和返回值 */

/* 交换两个指针px 和 py的值, 返回交换后的px的指针  */
int* swap(int* px, int* py)
{
        int temp;
        temp = *px;
        *px = *py;
        *py = temp;
        return px;
}

int main(int argc, char* argv[])
{
        int i = 10, j = 20;

        /*
         * px和py分别指向main函数的局部变量i和j，在swap函数中读写*px和*py其实是读写main函数的i和j。
         * 尽管在swap函数的作用域中访问不到i和j这两个变量名，却可以通过地址访问它们，最终swap函数将i和j的值做了交换。
         * 返回值px就是把变量i的地址返回了，通过指针p接收了，所以此时p指向变量i
         */
        int* p = swap(&i, &j);
        printf("now i=%d j=%d *p=%d\n", i, j, *p);
        return 0;
}
