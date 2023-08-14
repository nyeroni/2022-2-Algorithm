#pragma warning (disable : 4996)
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <math.h>
#include <time.h>
void inPlaceSelectSort(int* arr, int n) {
    for (int i = n - 1; i > 0;  i--) {
        int max = arr[0],h=0;
        for (int j = 0; j <= i; j++) {
            if (max < arr[j]) {
                max = arr[j];
                h = j;
            }
        }
        int temp = arr[h];
        arr[h] = arr[i];
        arr[i] = temp;

    }
}
int main()
{
    int n;
    scanf("%d", &n);
    int* arr;
    arr = (int*)malloc(sizeof(int) * n);
    if (arr == NULL) {
        printf("No enough memory!\n");
        return -1;
    }
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    inPlaceSelectSort(arr, n);
    for (int i = 0; i < n; i++) {
        printf(" %d", arr[i]);
    }
    printf("\n");
    return 0;
}
