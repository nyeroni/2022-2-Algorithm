#pragma warning (disable : 4996)
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <math.h>
#include <time.h>
void inPlaceInsertSort(int* arr, int n) {
    for (int i = 1; i < n; i++) {
        int j = i - 1, tmp=arr[i];
        while (arr[j] > arr[j+1]&&j>=0) {
            int temp = arr[j];
            arr[j] = arr[j + 1];
            arr[j + 1] = temp;
            j--;
        }
        arr[j + 1] = tmp;
    }

    //3 73 48 31 8 11 20

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
    inPlaceInsertSort(arr, n);
    for (int i = 0; i < n; i++) {
        printf(" %d", arr[i]);
    }
    printf("\n");
    return 0;
}
