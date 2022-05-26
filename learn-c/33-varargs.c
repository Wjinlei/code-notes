#include <stdarg.h>
#include <stdio.h>

/* 可变参数的用法 */

void myprintf(const char* format, ...)
{
        va_list ap;
        char c;

        va_start(ap, format); /* va_start(ap, format)使ap指向format参数的下一个参数 */
        while ((c = *format++)) {
                switch (c) {
                case 'c': {
                        char ch = va_arg(ap, int); /* 然后va_arg(ap, int)把第二个参数的值按int型取出来，同时使ap指向第三个参数 */
                        putchar(ch);
                        break;
                }
                case 's': {
                        char* p = va_arg(ap, char*);
                        fputs(p, stdout);
                        break;
                }
                default:
                        putchar(c);
                }
        }
        va_end(ap); /* C标准要求在函数返回前调用va_end。*/
}

int main(void)
{
        myprintf("c\ts\n", '1', "hello");
        return 0;
}
