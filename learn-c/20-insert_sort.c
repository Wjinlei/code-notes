#include <stdio.h>

/*
 * 插入排序
 * 每一轮取出一个元素(a)和其前面的元素(b)比较，如果前面的元素(b)比它大，则
 * 将前面的元素(b)移动到它(a)的位置，直到前面的元素(b)比它小，则
 * 将其插入在其的后面的位置(b + 1)
 */

#define LEN 5
int a[LEN] = { 10, 5, 2, 4, 7 };

void insertion_sort(void)
{
        printf("%d, %d, %d, %d, %d\n", a[0], a[1], a[2], a[3], a[4]);

        int i, j, key;
        for (i = 1; i < LEN; i++) {
                /* printf("%d, %d, %d, %d, %d\n", a[0], a[1], a[2], a[3], a[4]); */
                key = a[i];
                j = i - 1;
                while (j >= 0 && a[j] > key) {
                        a[j + 1] = a[j];
                        j--;
                }
                a[j + 1] = key;
        }

        printf("%d, %d, %d, %d, %d\n", a[0], a[1], a[2], a[3], a[4]);
}

int main(void)
{
        insertion_sort();
        return 0;
}
