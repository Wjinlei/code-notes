#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* 简单演示strcpy malloc free 函数的用法 */

typedef struct {
        int number;
        char* msg;
} unit_t;

int main(void)
{
        unit_t* p = malloc(sizeof(unit_t));
        /* malloc 后判断一下是否申请成功是个好习惯 */
        if (p == NULL) {
                printf("out of memory\n");
                exit(1);
        }

        p->number = 3;
        p->msg = malloc(20);
        if (p->msg == NULL) {
                printf("out of memory\n");
                exit(1);
        }

        strcpy(p->msg, "Hello world!");
        printf("number: %d\nmsg: %s\n", p->number, p->msg);
        free(p->msg);
        free(p);
        p = NULL;

        return 0;
}
