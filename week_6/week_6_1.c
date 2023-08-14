#pragma warning (disable : 4996)
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <math.h>
#include <time.h>
int findKey(int* x, int l, int r, int k) {
    int mid = (l + r) / 2;
    if (l > r)return r;
    if (k == x[mid])return mid;
    else if (k > x[mid]) {
        return findKey(x, mid + 1, r, k);
    }
    else {
        return findKey(x, l, mid - 1, k);
    }
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
    if (x[0]!=k && temp==-1) {
        printf("-1");
    }
    else {
        printf(" %d", temp);
    }
    return 0;
}
