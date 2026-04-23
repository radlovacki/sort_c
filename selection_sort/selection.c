#include <stdio.h>
#include "utils.h"

#define EL_CNT 10

void selection_sort(int *arr, int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        int idx_min = i;
        for (int j = i + 1; j < n; j++)
        {
            if (arr[j] < arr[idx_min])
            {
                idx_min = j;
            }
        }
        if (idx_min != i)
        {
            int temp = arr[i];
            arr[i] = arr[idx_min];
            arr[idx_min] = temp;
        }
    }
}

int main(void)
{
    int *arr = generateDynArray(EL_CNT);
    printArray(arr, EL_CNT);

    selection_sort(arr, EL_CNT);
    printArray(arr, EL_CNT);

    free(arr);
    return 0;
}
