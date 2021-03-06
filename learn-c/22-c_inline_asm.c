#include <stdio.h>

/*
 * 内联汇编格式：

__asm__(assembler template
        : output operands
        : input operands
        : list of clobbered registers
        );

 这种格式由四部分组成:
      第一部分是汇编指令，
      第二部分和第三部分是约束条件，第二部分指示汇编指令的运算结果要输出到哪些C操作数中，C操作数应该是左值表达式，
      第三部分指示汇编指令需要从哪些C操作数获得输入，
      第四部分是在汇编指令中被修改过的寄存器列表，指示编译器哪些寄存器的值在执行这条__asm__语句时会改变。
 后三个部分都是可选的，如果有就填写，没有就空着只写个:号。

*/

/* 这个程序将变量a的值赋给b。*/
int main()
{
        int a = 10, b;

        __asm__("movl %1, %%eax\n\t"
                "movl %%eax, %0\n\t"
                : "=r"(b) /* "=r"(b)就表示把%0所代表的寄存器的值输出给变量b。 */
                : "r"(a) /* "r"(a)指示编译器分配一个寄存器保存变量a的值，作为汇编指令的输入，也就是指令中的%1 */
                : "%eax" /* 告诉编译器在执行这条__asm__语句时eax要被改写，所以在此期间不要用eax保存其它值。 */
        );
        printf("Result: %d, %d\n", a, b);
        return 0;
}
