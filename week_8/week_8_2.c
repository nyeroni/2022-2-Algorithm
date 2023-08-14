#pragma warning (disable : 4996)
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int hash(int k, int M) {
    return k % M;
}
int getNextBucket(int v, int i, int M) {
    return (v + i) % M;
}
void insertItem(int* arr, int k, int M) {
    int i;
    for (int j = 0; j < M; j++) {
        i = getNextBucket(hash(k, M), j, M);
        if (arr[i] == 0) {
            arr[i] = k;
            printf("%d\n", i);
            return;
        }
        else {
            printf("C");
        }
    }
}
int searchItem(int* arr, int k, int M) {
    int i;
    for (int j = 0; j < M; j++) {
        i = getNextBucket(hash(k, M), j, M);
        if (arr[i] == k) {
            return i;
        }
    }
    return -1;
}
int main() {
    int M, n, k, cnt = 0;
    scanf("%d %d", &M, &n);
    getchar();
    int* arr = (int*)malloc(sizeof(int) * M);
    for(int i=0; i<M; i++){
        arr[i] = 0;
    }
    char ch;
    while (1) {
        scanf("%c", &ch);
        if (ch == 'i'&&cnt<n) {
            scanf("%d", &k);
            insertItem(arr, k, M);
            cnt++;
        }
        else if (ch == 's') {
            scanf("%d", &k);
            int j = searchItem(arr, k, M);
            if (j == -1)printf("%d\n", j);
            else printf("%d %d\n", j, k);
        }
        else if (ch == 'e') {
            free(arr);
            break;
        }
    }
    return 0;
}