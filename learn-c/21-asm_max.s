# 这个程序在一组数中找到一个最大的数，并把它作为程序的退出状态。这组数在.data段给出

 .section .data
data_items:             # data_items类似于C语言中的数组名。
 .long 3,67,34,222,45,75,54,34,44,33,22,11,66,0 # .long指示声明一组数，每个数占32位，相当于C语言中的数组。

 .section .text
 .globl _start
_start:
 # edi寄存器保存数组中的当前位置，每次比较完一个数就把edi的值加1，指向数组中的下一个数。
 # ebx寄存器保存到目前为止找到的最大值，如果发现有更大的数就更新ebx的值。
 # eax寄存器保存当前要比较的数，每次更新edi之后，就把下一个数读到eax中。

 movl $0, %edi          # 初始化edi，指向数组的第0个元素。
 # data_items是数组的首地址，edi的值是数组的下标，4表示数组的每个元素占4字节，
 # 那么数组中第edi个元素的地址应该是data_items + edi * 4，写在指令中就是data_items(,%edi,4)
 movl data_items(,%edi,4), %eax # 这条指令把数组的第0个元素传送到eax寄存器中。
 movl %eax, %ebx        # ebx的初始值也是数组的第0个元素。

# 循环开始
start_loop:
 # cmpl指令将两个操作数相减，但计算结果并不保存，只是根据计算结果改变eflags寄存器中的标志位。
 # 如果两个操作数相等，则计算结果为0，eflags中的ZF位置1。
 cmpl $0, %eax          # 比较eax的值是不是0，如果是0就说明到达数组末尾了，就要跳出循环

 je loop_exit           # 跳转到循环结束 je是一个条件跳转指令，它检查eflags中的ZF位，ZF位为1则发生跳转，ZF位为0则不跳转，继续执行下一条指令。

 incl %edi              # 将edi的值加1，把数组中的下一个数传送到eax寄存器中。
 movl data_items(,%edi,4), %eax

 cmpl %ebx, %eax        # 把当前数组元素eax和目前为止找到的最大值ebx做比较，
 jle start_loop         # 如果前者小于等于后者，则最大值没有变，跳转到循环开头比较下一个数，否则继续执行下一条指令。

 movl %eax, %ebx        # 更新最大值ebx然后跳转到循环开头比较下一个数。
 jmp start_loop         # jmp是一个无条件跳转指令，什么条件也不判断，直接跳转。

loop_exit:
 # %ebx is the status code for the _exit system call
 # and it already has the maximum number
 movl $1, %eax          #1 is the _exit() syscall
 int $0x80
