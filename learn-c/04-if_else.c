#include <stdio.h>

int main(int argc, char* argv[])
{
        int x = 2;
        if (x > 0) {
                printf("x is positive.\n");
        } else if (x < 0) {
                printf("x is negative.\n");
        } else {
                printf("x is zero.\n");
        }
        return 0;
}
