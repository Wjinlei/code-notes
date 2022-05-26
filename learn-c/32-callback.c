#include <stdio.h>

/*
 * 回调函数
 * 如果参数是一个函数指针，调用者可以传递一个函数的地址给实现者，让实现者去调用它，这称为回调函数
 */

typedef void (*callback_t)(void*); /* 函数指针 */
void repeat_three_times(callback_t, void*);

/* 实现者 */
void repeat_three_times(callback_t f, void* para)
{
        f(para);
        f(para);
        f(para);
}

void say_hello(void* str)
{
        printf("Hello %s\n", (const char*)str);
}

int main(void)
{
        /* 调用者 */
        repeat_three_times(say_hello, "Guys");
        return 0;
}
