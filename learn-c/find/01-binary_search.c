#include <stdio.h>

/*
 * 折半查找
 */

#define LEN 8
int a[LEN] = { 1, 2, 2, 2, 5, 6, 8, 9 };

int binarysearch(int number)
{
        int mid, start = 0, end = LEN - 1;

        while (start <= end) {
                mid = (start + end) / 2;
                if (a[mid] < number) {
                        start = mid + 1;
                } else if (a[mid] > number) {
                        end = mid - 1;
                } else {
                        return mid;
                }
        }
        return -1;
}

int main(void)
{
        printf("%d\n", binarysearch(5));
        return 0;
}
