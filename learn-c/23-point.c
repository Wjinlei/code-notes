#include <stddef.h>
#include <stdio.h>

/* 指针的定义 */

int main(int argc, char* argv[])
{
        int i;
        /*
         * int *pi = &i; 表示定义一个指向int型的指针变量pi，并用i的地址来初始化pi。
         * 但我不建议用"指向int型的指针"的说法来描述指针，指针实际上是没有类型的
         * 不要把指针和类型挂钩，这里的类型只是指针的"宽度"，指针运算时会根据宽度决定一次跳多远的距离
         */
        int* pi = &i; /* 这里的&是取地址运算符（Address Operator），&i表示取变量i的地址 */

        /* 无论用什么类型定义指针,它们的内存单元都占4个字节，因为要保存32位的虚拟地址，同理，在64位平台上指针变量都占8个字节。*/
        char c;
        char* pc = &c;

        /* 为避免出现野指针很，在定义指针变量时就应该给它明确的初值，或者把它初始化为NULL：*/
        int* p = NULL;

        *pi = *pi + 10; /* 这里的*号是指针间接寻址运算符（Indirection Operator），*pi表示取指针pi所指向的变量的值，
                           也称为Dereference操作，指针有时称为变量的引用（Reference），所以根据指针找到变量称为Dereference。*/

        printf("%d\n", *pi);
        return 0;
}
