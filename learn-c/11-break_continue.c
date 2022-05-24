#include <stdio.h>

/*
 * 我们见到了break语句的一种用法，用来跳出switch语句块，这个语句也可以用来跳出循环体。
 * continue语句也会终止当前循环，和break语句不同的是，
 * continue语句终止当前循环后又回到循环体的开头准备执行下一次循环。
 * 对于while循环和do/while循环，执行continue语句之后测试控制表达式，
 * 如果值为真则继续执行下一次循环；
 * 对于for循环，执行continue语句之后首先计算控制表达式3，
 * 然后测试控制表达式2，如果值为真则继续执行下一次循环。
 */

/*
 * 判断是否是素数
 * 质数（Prime number，又称素数），
 * 指在大于1的自然数中，除了1和该数自身外，无法被其他自然数整除的数
 * （也可定义为只有1与该数本身两个正因数的数）。
 */
int is_prime(int n)
{
        int i;
        for (i = 2; i < n; i++) {
                /*
                 * 一旦这个数能被整除就跳出循环
                 */
                if (n % i == 0) {
                        break; // break 可以跳出switch语句块,也可以跳出当前循环体
                }
        }
        /*
         * 又因为素数只能被1和自身整除,所以这里判断i是否等于n
         * 如果不等于，则证明这个数被其他自然数整除了，则证明不是素数
         */
        if (i == n) {
                return 1;
        } else {
                return 0;
        }
}

int main(void)
{
        int i;
        for (i = 1; i <= 10; i++) {
                if (!is_prime(i)) {
                        /*
                         * continue用于结束当前循环,立即执行下一次循环
                         * 对于for循环，执行continue语句之后首先计算控制表达式3，
                         * 然后测试控制表达式2，如果值为真则继续执行下一次循环。
                         */
                        continue;
                }
                printf("%d\n", i);
        }
        return 0;
}
