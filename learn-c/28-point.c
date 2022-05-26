#include <stdio.h>

/* 函数指针 */

void say_hello(const char* str)
{
        printf("Hello %s\n", str);
}

int main(void)
{
        /*
         * 分析一下变量f的类型声明void (*f)(const char *)，f首先跟*号结合在一起，因此是一个指针。
         * (*f)外面是一个函数原型的格式，参数是const char *，返回值是void，所以f是指向这种函数的指针。
         */

        void (*f)(const char*) = say_hello; /*
                                             say_hello是一种函数类型，而函数类型和数组类型类似，做右值使用时自动转换成函数指针类型，所以可以直接赋给f，
                                             当然也可以写成void (*f)(const char *) = &say_hello;，把函数say_hello先取地址再赋给f，就不需要自动类型转换了。
                                             */
        f("Guys");
        return 0;
}
