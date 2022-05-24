/* Copyright (c) 2022 Jerry. All Rights Reserved. */

#include <stdio.h>

/*
 * 这个程序的作用是：
 * 首先从键盘读入一串数字存到字符数组input中，
 * 然后转换成整型存到sum中，然后打印出来，一直这样循环下去。
 * 结果不对，请用GDB找出问题的原因
 */
int main(void)
{
        int sum = 0, i = 0;
        char input[5];

        while (1) {
                scanf("%s", input);
                for (i = 0; input[i] != '\0'; i++) {
                        sum = sum * 10 + input[i] - '0';
                }
                printf("input=%d\n", sum);
        }
        return 0;
}

/*
 * 第一步: 我们可以用display命令使得每次停下来的时候都显示当前sum的值，然后继续往下走：
 *      display sum
 * 第二步: 如果不想一步一步走这个循环，可以用break命令（简写为b）在第9行设一个断点
 *      b 9
 * 第三步: 现在用continue命令（简写为c）连续运行而非单步运行，程序到达断点会自动停下来，这样就可以停在下一次循环的开头：
 *      c
 * 第四步: info命令可以查看已经设置的断点：
 *      i breakpoints
 * 第五步: 每个断点都有一个编号，可以用编号指定删除某个断点：
 *      delete breakpoints 2
 * 第六步: 有时候一个断点暂时不用可以禁用掉而不必删除，这样以后想用的时候可以直接启用，而不必重新从代码里找应该在哪一行设断点：
 *      disable breakpoints 3
 *      enable 3
 * 第七步: gdb的断点功能非常灵活，还可以设置断点在满足某个条件时才激活，
 * 例如我们仍然在循环开头设置断点，但是仅当sum不等于0时才中断，然后用run命令（简写为r）重新从程序开头连续运行：
 *      break 9 if sum != 0
 *      r
 *
 * 命令参考:
 * break（或b） 行号	在某一行设置断点
 * break 函数名	在某个函数开头设置断点
 * break ... if ...	设置条件断点
 * delete breakpoints 断点号	删除断点
 * disable breakpoints 断点号	禁用断点
 * enable 断点号	启用断点
 * info（或i） breakpoints	查看当前设置了哪些断点
 * continue（或c）	从当前位置开始连续运行程序
 * run（或r）	从头开始连续运行程序
 * display 变量名	跟踪查看某个变量，每次停下来都显示它的值
 * undisplay 跟踪显示号	取消跟踪显示
 * x/7b 变量名          x命令打印指定存储单元的内容。7b是打印格式，b表示每个字节一组，7表示打印7组[22]，从input数组的第一个字节开始连续打印7个字节。
 * watch 变量名         设置观察点，观察点是当程序访问某个存储单元时中断，如果我们不知道某个存储单元是在哪里被改动的，这时候观察点尤其有用。
 * i watchpoints        查看观察点
 *
 */
