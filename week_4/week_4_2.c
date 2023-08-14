#pragma warning (disable : 4996)
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
int H[100], n=0,N=0;
void downHeap(int i) {
    if (i * 2 > n)return;
    int greater = i * 2;
    if (i*2+1<=n) {
        if (H[i * 2] <= H[i * 2 + 1]) {
            greater = i * 2 + 1;
        }
    }
    if (H[i] >= H[greater])return;
    int tmp = H[i];
    H[i] = H[greater];
    H[greater] = tmp;
    downHeap(greater);
}
void upHeap(int i) {
    if (i == 1)return;
    if (H[i] <= H[i / 2])return;
    int tmp = H[i];
    H[i] = H[i / 2];
    H[i / 2] = tmp;
    upHeap(i / 2);
}
void insertItem(int key) {
    n++;
    H[n] = key;
    upHeap(n);
}

void rBuildHeap(int i) {
    if (i > n)return;
    rBuildHeap(i * 2);
    rBuildHeap(i * 2 + 1);
    downHeap(i);
}
void buildHeap() {
    for (int i = n / 2; i >= 1; i--) {
        downHeap(i);
    }
}
void inPlaceHeapSort() {
    for (int i = N; i > 1; i--) {
        int tmp = H[1];
        H[1] = H[i];
        H[i] = tmp;
        n = i - 1;
        downHeap(1);
    }
}
void printArray() {
    for (int i= 1; i <= N; i++) {
        printf(" %d", H[i]);
    }
    printf("\n");
}
int main(void) {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &H[i]);
    }
    buildHeap();
    N = n;
    inPlaceHeapSort();
    printArray();
    return 0;
}