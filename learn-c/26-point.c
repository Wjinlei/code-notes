#include <stdio.h>

/* 指针与结构体 */

struct unit {
        char c;
        int num;
};

int main(int argc, char* argv[])
{
        struct unit u;
        struct unit* pu = &u;
        /* 要通过指针p访问结构体成员可以写成(*p).c和(*p).num，为了书写方便，C语言提供了->运算符，也可以写成p->c和p->num。*/
        pu->num = 10;
        printf("%d\n", pu->num);
        return 0;
}
