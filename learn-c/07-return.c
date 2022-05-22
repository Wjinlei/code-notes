/* Copyright (c) 2022 Jerry. All Rights Reserved. */

#include <math.h>
#include <stdio.h>

void print_logarithm(double x)
{
        if (x < 0.0) {
                printf("Positive numbers only, please.\n");
                return; // 在有返回值的函数中，return语句的作用是结束当前函数并返回到调用它的地方。
        }

        printf("The log of x %f", log(x));
}

int is_even(int x)
{
        return !(x % 2);
}

int main(int argc, char* argv[])
{
        print_logarithm(-1);

        int i = 19;
        if (is_even(i)) {
                printf("%d is even", i);
        } else {
                printf("%d is odd", i);
        }
        return 0;
}
