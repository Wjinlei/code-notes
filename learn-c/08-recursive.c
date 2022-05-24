#include <stdio.h>

/*
 * 什么是递归?
 * 如果定义一个概念需要用到这个概念本身，我们称它的定义是递归的（Recursive）。
 * 例如：数学上确实有很多概念是用它自己来定义的，比如n的阶乘（Factorial）是这样定义的：
 * n的阶乘等于n乘以n-1的阶乘。如果这样就算定义完了，恐怕跟上面那个词条有异曲同工之妙了：
 * n-1的阶乘是什么？是n-1乘以n-2的阶乘。那n-2的阶乘又是什么？这样下去永远也没完。
 * 因此需要定义一个最关键的基础条件（Base Case）：0的阶乘等于1。
 */
int factorial(int n)
{
        /* 递归最关键的就是基础条件(Base Case), 它控制了递归什么时候结束 */
        if (n == 0) {
                return 1;
        } else {
                int recurse = factorial(n - 1);
                int result = n * recurse;
                return result;
        }
}

int main(int argc, char* argv[])
{
        printf("%d\n", factorial(3));
        return 0;
}
