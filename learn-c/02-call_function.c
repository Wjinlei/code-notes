/*
 * 使用math.h中声明的库函数还有一点特殊之处，gcc命令行必须加-lm选项，
 * 因为数学函数位于libm.so库文件中（这些库文件通常位于/lib目录下），
 * -lm选项告诉编译器，我们程序中用到的数学函数要到这个库文件里找。
 */
#include <math.h>
#include <stdio.h>

int main(int argc, char* argv[])
{
        double pi = 3.14;
        printf("sin(pi/2)=%f\n", sin(pi / 2));
        return 0;
}
