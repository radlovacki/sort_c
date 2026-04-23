#include <string.h>
#include "utils.h"

#define TEST_SORT_EL 100
#define TEST_SORT_ITERS 20
#define TEST_TIME_MIN_EL 10
#define TEST_TIME_MAX_EL 100000
#define TEST_TIME_ITERS 10

void selectionSort(int *arr, int n);
void mergeSort(int *arr, int n);
void hybridSort(int *arr, int n);

int main()
{
    srand(time(0));
    void (*all_sorts[])(int *, int) = {selectionSort, mergeSort, hybridSort};
    const char *names[] = {"Selection Sort", "Merge Sort", "Hybrid Sort"};
    const char *valid_names[3];
    int num_sorts = sizeof(all_sorts) / sizeof(all_sorts[0]);
    void (*valid_sorts[3])(int *, int);
    int valid_count = 0;
    for (int i = 0; i < num_sorts; i++)
    {
        printf("Testing %s:\n", names[i]);
        int res = test_sort(all_sorts[i], TEST_SORT_EL, TEST_SORT_ITERS);
        if (res == 1)
        {
            fprintf(stderr, "Fatal error: Memory allocation failed during %s.\n", names[i]);
            return 1;
        }
        else if (res == 0)
        {
            valid_sorts[valid_count] = all_sorts[i];
            valid_names[valid_count++] = names[i];
        }
        else if (res == 2)
        {
            printf("%s failed the test and will be excluded from further testing.\n", names[i]);
        }
    }
    if (valid_count > 0)
    {
        printf("\nRunning multiple tests on working algorithms (%d total):\n", valid_count);
        test_multiple_sorts(valid_sorts, valid_names, valid_count, TEST_TIME_MIN_EL, TEST_TIME_MAX_EL, TEST_TIME_ITERS);
    }
    else
    {
        printf("\nNo algorithms passed the initial tests. Skipping multiple sort testing.\n");
    }
    return 0;
}

void selectionSort(int *arr, int n)
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

void mergeSort(int *arr, int n)
{
    if (n <= 1)
    {
        return;
    } 
    int mid = n / 2;
    int leftLen = mid;
    int rightLen = n - mid;
 
    mergeSort(arr, leftLen);
    mergeSort(arr + mid, rightLen);
 
    int *left  = (int *)malloc(leftLen  * sizeof(int));
    int *right = (int *)malloc(rightLen * sizeof(int));
 
    if (left == NULL || right == NULL)
    {
        perror("malloc (mergeSort)");
        free(left);
        free(right);
        return;
    }
 
    for (int i = 0; i < leftLen;  i++)
    {
        left[i]  = arr[i];
    }
    for (int i = 0; i < rightLen; i++)
    {
        right[i] = arr[mid + i];
    }
 
    int i = 0, j = 0, k = 0;
    while (i < leftLen && j < rightLen)
    {
        if (left[i] <= right[j])
            arr[k++] = left[i++];
        else
            arr[k++] = right[j++];
    }
    while (i < leftLen)  arr[k++] = left[i++];
    while (j < rightLen) arr[k++] = right[j++];
 
    free(left);
    free(right);
}

void hybridSort(int *arr, int n)
{
    if (n <= 15)
    {
        selectionSort(arr, n);
        return;
    }
 
    int mid = n / 2;
    int leftLen = mid;
    int rightLen = n - mid;
 
    hybridSort(arr, leftLen);
    hybridSort(arr + mid, rightLen);
 
    int *left = (int *)malloc(leftLen * sizeof(int));
    int *right = (int *)malloc(rightLen * sizeof(int));
 
    if (left == NULL || right == NULL)
    {
        perror("malloc (hybridSort)");
        free(left);
        free(right);
        return;
    }
 
    for (int i = 0; i < leftLen;  i++) left[i]  = arr[i];
    for (int i = 0; i < rightLen; i++) right[i] = arr[mid + i];
 
    int i = 0, j = 0, k = 0;
    while (i < leftLen && j < rightLen)
    {
        if (left[i] <= right[j])
            arr[k++] = left[i++];
        else
            arr[k++] = right[j++];
    }
    while (i < leftLen)  arr[k++] = left[i++];
    while (j < rightLen) arr[k++] = right[j++];
 
    free(left);
    free(right);
}
