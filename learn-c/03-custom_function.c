/* Copyright (c) 2022 Jerry. All Rights Reserved. */

#include <stdio.h>

/* Function declaration */
void newline(void);

int main(int argc, char* argv[])
{
        printf("%s\n", "First Line.");
        newline(); // Call custom function
        newline(); // Call custom function
        newline(); // Call custom function
        printf("%s\n", "Second Line.");
        return 0;
}

/*
 * Custom function
 */
void newline(void)
{
        printf("\n");
}
