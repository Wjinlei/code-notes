/* Copyright (c) 2022 Jerry. All Rights Reserved. */

#include <stdio.h>

/* Function declaration */
void newline(void);
int increment(int x);

int main(int argc, char* argv[])
{
        printf("%s\n", "First Line.");
        newline(); // Call custom function
        newline(); // Call custom function
        newline(); // Call custom function
        printf("%s\n", "Second Line.");

        int i = 1, j = 2;
        printf("i = %d\n", increment(i));
        printf("j = %d\n", increment(j));
        return 0;
}

/*
 * Custom function
 */
void newline(void)
{
        printf("\n");
}

/*
 * Custom function
 */
int increment(int x)
{
        return x + 1;
}
