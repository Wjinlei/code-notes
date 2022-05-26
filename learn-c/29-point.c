#include <stdio.h>

/* 函数指针练习 */

enum Option {
        MIN = 0,
        MAX,
        /* 如果后期又添加了两个选项该怎么办？ 修改函数func的实现，增加else if 判断? */
        ADD,
        SUB
};

int func(enum Option opt, int x, int y)
{
        /*
         * 这种方法不太好，每增加一个选项就要修改原来的函数实现
         * 我们应该尽量让代码互相独立，而不必把所有的代码都耦合到一个函数中。
         * “低耦合，高内聚”（Low Coupling, High Cohesion）是程序设计的一条基本原则，这样可以更好地复用现有代码，使代码更容易维护。
         */
        if (opt == MAX) {
                return x > y ? x : y;
        } else if (opt == ADD) {
                return x + y;
        } else if (opt == SUB) {
                return x - y;
        } else {
                return x < y ? x : y;
        }
}

/* 来看看用函数指针如何更好的解决这个问题 */
int min(int x, int y)
{
        return x < y ? x : y;
}

int max(int x, int y)
{
        return x > y ? x : y;
}

int add(int x, int y)
{
        return x + y;
}

int sub(int x, int y)
{
        return x - y;
}

int (*p_func[])(int x, int y) = { min, max, add, sub };

#define p_func_t(opt, x, y) p_func[opt](x, y)

int main(int argc, char* argv[])
{
        printf("%d\n", func(MAX, 1, 3));
        printf("%d\n", func(ADD, 1, 3));

        printf("%d\n", p_func_t(MAX, 1, 3));
        printf("%d\n", p_func_t(ADD, 1, 3));
        return 0;
}
