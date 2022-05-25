# 这是最简单的汇编程序,它只做了一件事就是退出,退出状态是4
# 生成目标文件: as hello.s -o hello.o 
# 链接执行文件: ld hello.o -o hello

# 汇编程序中以.开头的名称并不是指令的助记符，不会被翻译成机器指令，而是给汇编器一些特殊指示，
# 称为汇编指示（Assembler Directive）或伪操作（Pseudo-operation），由于它不是真正的指令所以加个“伪”字。
# .section指示把代码划分成若干个段（Section），程序被操作系统加载执行时，每个段被加载到不同的地址，操作系统对不同的页面设置不同的读、写、执行权限。

  .section .data # .data段保存程序的数据，是可读可写的，相当于C程序的全局变量。本程序中没有定义数据，所以.data段是空的。

  .section .text # .text段保存代码，是只读和可执行的，后面那些指令都属于.text段。

# .globl指示告诉汇编器，_start这个符号要被链接器用到，所以要在目标文件的符号表中标记它是一个全局符号。
# _start就像C程序的main函数一样特殊，是整个程序的入口，链接器在链接时会查找目标文件中的_start符号代表的地址，
# 把它设置为整个程序的入口地址，所以每个汇编程序都要提供一个_start符号并且用.globl声明。
  .globl _start
_start:
  # 这是一条数据传送指令，这条指令要求CPU内部产生一个数字1并保存到eax寄存器中。
  # mov的后缀l表示long，说明是32位的传送指令。这条指令不要求CPU读内存，1这个数是在CPU内部产生的，称为立即数（Immediate）。
  # 在汇编程序中，立即数前面要加$，寄存器名前面要加%，以便跟符号名区分开。
  movl $1, %eax
  movl $4, %ebx
  # int指令称为软中断指令，可以用这条指令故意产生一个异常
  # int指令中的立即数0x80是一个参数，在异常处理程序中要根据这个参数决定如何处理，
  # 在Linux内核中int $0x80这种异常称为系统调用（System Call）。
  # 内核提供了很多系统服务供用户程序使用，但这些系统服务不能像库函数（比如printf）那样调用，
  # 因为在执行用户程序时CPU处于用户模式，不能直接调用内核函数，所以需要通过系统调用切换CPU模式，经由异常处理程序进入内核，
  # 用户程序只能通过寄存器传几个参数，之后就要按内核设计好的代码路线走，而不能由用户程序随心所欲，想调哪个内核函数就调哪个内核函数，
  # 这样可以保证系统服务被安全地调用。在调用结束之后，CPU再切换回用户模式，继续执行int $0x80的下一条指令，在用户程序看来就像函数调用和返回一样。
  # eax和ebx的值是传递给系统调用的两个参数。eax的值是系统调用号，Linux的各种系统调用都是由int $0x80指令引发的，
  # 内核需要通过eax判断用户要调哪个系统调用，_exit的系统调用号是1。ebx的值是传给_exit的参数，表示退出状态。
  # 大多数系统调用完成之后会返回用户空间继续执行后面的指令，而_exit系统调用比较特殊，它会终止掉当前进程，而不是返回用户空间继续执行。
  int $0x80
