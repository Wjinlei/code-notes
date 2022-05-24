#include <stdio.h>

int main(int argc, char* argv[])
{
        int x = 2;
        if (x > 0 && x < 3) {
                printf("x > 0 and x < 3.\n");
        }
        if (x == 2 || x < 0) {
                printf("x == 2 or x < 0.\n");
        }
        return 0;
}
