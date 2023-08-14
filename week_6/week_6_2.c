#pragma warning (disable : 4996)
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <math.h>
#include <time.h>
int findKey(int* x, int l, int r, int k) {
    int mid,f=0,min;
    while (l <= r) {
        mid = (l + r) / 2;
        if (k <= x[mid]) {
            if (f == 0) {
                f = 1;
                min = mid;
            }
            else if (x[min] > x[mid]) {
                min = mid;
            }
            r = mid - 1;
        }
        else {
            l = mid + 1;
        }
    }
    if (f == 0) {
        return -1;
    }
    else return min;
}
int main()
{
    int n, k;
    int* x;
    scanf("%d %d", &n, &k);
    x = (int*)malloc(sizeof(int) * n);
    if (x == NULL) {
        printf("No enough memory!\n");
        return -1;
    }

    for (int i = 0; i < n; i++) {
        scanf("%d", &x[i]);
    }
    int temp = findKey(x, 0, n - 1, k);
    if (temp==-1) {
        printf("%d",n);
    }
    else {
        printf(" %d", temp);
    }
    return 0;
}
