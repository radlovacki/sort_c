#include <stdio.h>
#include "utils.h"

#define EL_CNT 10

void bubble_sort(int *arr, int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main(void)
{
    int *arr = generateDynArray(EL_CNT);
    printArray(arr, EL_CNT);

    bubble_sort(arr, EL_CNT);
    printArray(arr, EL_CNT);

    free(arr);
    return 0;
}
