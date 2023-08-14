#pragma warning (disable : 4996)
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <math.h>
#include <time.h>
int H[100], n=0;
void upHeap(int i) {
    if (i == 1)return;
    if (H[i] <= H[i / 2])return;
    int tmp = H[i];
    H[i] = H[i / 2];
    H[i / 2] = tmp;
    upHeap(i / 2);
}
void downHeap(int i) {
    if (i * 2 > n)return;
    int greater = i * 2;
    if (H[2 * i + 1] != NULL) {
        if (H[greater] < H[i * 2 + 1]) {
            greater = i * 2 + 1;
        }
    }
    if (H[greater] <= H[i])return;
    int temp = H[greater];
    H[greater] = H[i];
    H[i] = temp;
    downHeap(greater);

}
void insertItem(int num) {
    n++;
    H[n] = num;
    upHeap(n);
}
int removeMax() {
    int key = H[1];
    H[1] = H[n];
    n--;
    downHeap(1);
    return key;
}
void printHeap() {
    for (int i = 1; i <= n; i++) {
        printf(" %d", H[i]);
    }
    printf("\n");
}
void rBuildHeap(int i) {
    if (i > n)return;
    rBuildHeap(2 * i);
    rBuildHeap(2 * i + 1);
    downHeap(i);
}
void buildHeap() {
    for (int i = n / 2; i > 0; i--) {
        downHeap(i);
    }
}
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &H[i]);
    }
    buildHeap();
    printHeap();
    return 0;
}
