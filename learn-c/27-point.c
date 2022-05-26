#include <stdio.h>

/*
 * 数组指针
 * 练习
 * 要想通过pa或ppa访问数组a中的'r'元素，分别应该怎么写
 */

int main(int argc, char* argv[])
{
        char a[4][3][2] = {
                { { 'a', 'b' }, { 'c', 'd' }, { 'e', 'f' } },
                { { 'g', 'h' }, { 'i', 'j' }, { 'k', 'l' } },
                { { 'm', 'n' }, { 'o', 'p' }, { 'q', 'r' } },
                { { 's', 't' }, { 'u', 'v' }, { 'w', 'x' } },
        };

        char(*pa)[2] = &a[1][0];
        char(*ppa)[3][2] = &a[1];

        printf("%c\n", *(*(pa + 5) + 1));
        printf("%c\n", pa[5][1]);

        printf("%c\n", *(*(*(ppa + 1) + 2) + 1));
        printf("%c\n", ppa[1][2][1]);
        return 0;
}
