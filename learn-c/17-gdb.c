/* Copyright (c) 2022 Jerry. All Rights Reserved. */

#include <stdio.h>

/*
 * 利用gdb调试器找出问题原因
 */

int add_range(int low, int high)
{
        int i, sum;
        for (i = low; i <= high; i++) {
                sum = sum + i;
        }
        return sum;
}

int main(void)
{
        int result[100];
        result[0] = add_range(1, 10); // 正确结果应该是55
        result[1] = add_range(1, 100); // 正确结果应该是5050
        printf("result[0]=%d\nresult[1]=%d\n", result[0], result[1]);
        return 0;
}

/*
 * 学习使用GDB调试
 *
 * 第一步: 在编译时要加上-g选项
 *      生成的可执行文件才能用gdb进行源码级调试：gcc -g main.c -o main
 *
 *      -g选项的作用是在可执行文件中加入源代码的信息，
 *      比如可执行文件中第几条机器指令对应源代码的第几行，
 *      但并不是把整个源文件嵌入到可执行文件中，所以在调试时必须保证gdb能找到源文件。
 *
 * 第二步: 现在试试用list 1命令从第一行开始列出源代码一次只列10行，
 *      如果要从第11行开始继续列源代码可以继续输入 list，也可以什么都不输直接敲回车，
 *      gdb提供了一个很方便的功能，在提示符下直接敲回车表示重复上一条命令。
 *
 *
 * 第三步: 开始运行程序 start
 *      gdb会停在main函数中变量定义之后的第一条语句处等待我们发命令
 *      我们可以用next命令（简写为n）控制这些语句一条一条地执行：
 *      n
 *
 * 第四步: 用step命令（简写为s）钻进函数中去跟踪执行：
 *      s
 *
 * 第五步: 在函数中有几种查看状态的办法，
 *      backtrace命令（简写为bt）可以查看函数调用的栈帧:
 *      bt
 *      可以用info命令（简写为i）查看函数局部变量的值：
 *      i locals
 *      如果想查看main函数当前局部变量的值也可以做到，
 *      先用frame命令（简写为f）选择1号栈帧然后再查看局部变量：
 *      f 1
 *      i locals
 *
 * 第六步：打印变量的值
 *      用print命令（简写为p）打印出变量sum的值：p sum
 *
 * 第七步: finish命令让程序一直运行到从当前函数返回为止
 *      finish
 *
 * 第八步: 设置变量的值
 *      set var sum=0
 *
 * GDB基本命令参考
 * backtrace（或bt）	查看各级函数调用及参数
 * finish	        连续运行到当前函数返回为止，然后停下来等待命令
 * frame（或f） 帧编号	选择栈帧
 * info（或i） locals	查看当前栈帧局部变量的值
 * list（或l）	        列出源代码，接着上次的位置往下列，每次列10行
 * list 行号	        列出从第几行开始的源代码
 * list 函数名	        列出某个函数的源代码
 * next（或n）	        执行下一行语句
 * print（或p）	        打印表达式的值，通过表达式可以修改变量的值或者调用函数
 * quit（或q）	        退出gdb调试环境
 * set var	        修改变量的值
 * start	        开始执行程序，停在main函数第一行语句前面等待命令
 * step（或s）	        执行下一行语句，如果有函数调用则进入到函数中
 */
