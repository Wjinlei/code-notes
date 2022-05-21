/* Copyright (c) 2022 Jerry. All Rights Reserved. */

#include <stdio.h>

int main(int argc, char* argv[])
{
        int x = 2;
        switch (x) {
        case 2:
                printf("yes x = %d\n", 2);
                break;
        default:
                printf("no x = %d\n", x);
                break;
        }
        return 0;
}
