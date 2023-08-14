#pragma warning (disable : 4996)
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <math.h>
#include <time.h>

int hash1(int x, int M) {
    return x % M;
}
int hash2(int x, int q) {
    return q - (x % q);
}
int getNextBucket(int x, int i ,int M, int q) {
    return (hash1(x, M) + hash2(x, q) * i) % M;
}

void insertItem(int* H, int k, int M,int q) {
    int i;
    for (int j = 0; j < M; j++) {
        i = getNextBucket(k,j, M,q);
        if (H[i] == 0) {
            H[i] = k;
            printf("%d\n", i);
            return;
        }
        else {
            printf("C");
        }
    }
}
int searchItem(int* H, int k, int M, int q) {
    int i;
    for (int j = 0; j < M; j++) {
        i = getNextBucket(k, j, M,q);
        if (H[i] == k) {
            return i;
        }
    }
    return -1;
}
void printItem(int* H, int M) {
    for (int i = 0; i < M; i++) {
        printf(" %d", H[i]);
    }
    printf("\n");
}
int main()
{
    int M, n, k, q, cnt = 0;
    char ch;
    scanf("%d %d %d", &M, &n, &q);
    getchar();
    int* H = (int*)malloc(sizeof(int) * M);

    for (int i = 0; i < M; i++) {
        H[i] = 0;
    }
    while (1) {
        scanf("%c", &ch);
        if (ch == 'i' && cnt < n) {
            scanf("%d", &k);
            insertItem(H, k, M, q);
            cnt++;
        }
        else if (ch == 's') {
            scanf("%d", &k);
            int tmp = searchItem(H, k, M, q);
            if (tmp == -1) {
                printf("%d\n", tmp);
            }
            else {
                printf("%d %d\n", tmp, k);
            }
        }
        else if (ch == 'p') {
            printItem(H, M);
        }
        else if (ch == 'e') {
            printItem(H, M);

            free(H);
            break;
        }
        getchar();

    }
    return 0;
}

