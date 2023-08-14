#pragma warning (disable : 4996)
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <math.h>
#include <time.h>
void print(int* arr, int n) {
    for (int i = 0; i < n; i++) {
        printf(" %d", arr[i]);
    }
}
int findPivot(int* L, int l, int r) {
    srand(time(NULL));
    int p1 = rand() % (r - l + 1) + l;

    return p1;
}
int inPlacePartition(int *arr, int l, int r, int k) {
    int pivot = arr[k];
    int a = l;
    int b = r-1;
    int temp;
    temp = arr[r];
    arr[r] = arr[k];
    arr[k] = temp;

    while (a <= b) {
        while (arr[a] <= pivot && a <= b) {
            a++;
        }
        while (arr[b] >= pivot && a <= b) {
            b--;
        }
        if (a < b) {
            temp = arr[a];
            arr[a] = arr[b];
            arr[b] = temp;
        }
    }
    temp = arr[r];
    arr[r] = arr[a];
    arr[a] = temp;
    return a;
}
void inPlaceQuickSort(int* arr, int l, int r) {
    if (l >= r)return;
    int k = findPivot(arr,l, r);
    int m = inPlacePartition(arr, l, r, k);
    inPlaceQuickSort(arr, l, m-1);
    inPlaceQuickSort(arr, m+1, r);
}

int main()
{
    int n;
    int* arr;
    scanf("%d", &n);
    arr = (int*)malloc(sizeof(int) * n);
    if (arr == NULL) {
        printf("No enough memory\n");
        return -1;
    }
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    inPlaceQuickSort(arr, 0, n - 1);
    print(arr, n);
    return 0;
}
