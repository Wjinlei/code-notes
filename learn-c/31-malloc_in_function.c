#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* 通过二级指针在函数中分配内存 */

typedef struct {
        int number;
        char* msg;
} unit_t;

/* 为什么这里要用二级指针？ 一级指针为什么不行 */
/* 答: 一级指针调用者在传递时不用&，这样的话传进来的实际上是它的拷贝而不是真正传进来的那个参数 */
void alloc_unit(unit_t** pp)
{
        unit_t* p = malloc(sizeof(unit_t));
        if (p == NULL) {
                printf("out of memory\n");
                exit(1);
        }
        p->number = 3;
        p->msg = malloc(20);
        strcpy(p->msg, "Hello World!");
        *pp = p;
}

void free_unit(unit_t* p)
{
        free(p->msg);
        free(p);
}

int main(void)
{
        unit_t* p = NULL;
        alloc_unit(&p);
        printf("number: %d\nmsg: %s\n", p->number, p->msg);
        free_unit(p);
        p = NULL;
        return 0;
}
