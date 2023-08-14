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
int main()
{
    char ch;
    int num;
    while (1) {
        scanf("%c", &ch);
        if (ch == 'i') {
            scanf("%d", &num);
            insertItem(num);
            printf("0\n");
        }
        else if (ch == 'd') {
            printf("%d\n", removeMax());

        }
        else if (ch == 'p') {
            printHeap();
        }
        else if (ch == 'q') {
            break;
        }
    }
    return 0;
}
