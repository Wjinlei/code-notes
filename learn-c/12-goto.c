#include <stdio.h>

/*
 * goto语句，实现无条件跳转
 */

int main(int argc, char* argv[])
{
        /*
         * 我们知道break只能跳出最内层的循环，
         * 如果在一个嵌套循环中遇到某个错误条件需要立即跳出最外层循环做出错处理，就可以用goto语句
         */
        int i, j;
        for (i = 0; i < 10; i++) {
                for (j = 0; j < 10; j++) {
                        if (i == 5 && j == 9) {
                                goto error;
                        }
                }
        }
error:
        printf("i(%d) == 5 and j(%d) == 9\n", i, j);
        return 0;
}
