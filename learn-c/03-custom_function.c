/* Copyright (c) 2022 Jerry. All Rights Reserved. */

#include <stdio.h>

/*
 * custom function
 */
void newline(void)
{
        printf("\n");
}

int main(int argc, char* argv[])
{
        printf("%s\n", "First Line.");
        newline(); // call custom function
        printf("%s\n", "Second Line.");
        return 0;
}
