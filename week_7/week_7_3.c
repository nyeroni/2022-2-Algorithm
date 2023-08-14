#pragma warning (disable:4996)
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
typedef struct Node {
    int key;
    struct Node* next;
}Node;
Node* getNode(int k) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->key = k;
    node->next = NULL;
    return node;
}
int hash(int k, int M) {
    return k % M;
}
void insertItem(Node* arr, int k, int M) {
    Node* node = getNode(k);
    Node* tmp = &arr[hash(k, M)];
    node->next = tmp->next;
    tmp->next = node;
    return;
}
int searchItem(Node* arr, int k, int M) {
    Node* tmp = arr[hash(k, M)].next;
    int j = 0;
    while (tmp != NULL) {
        j++;
        if (tmp->key == k) {
            return j;
        }
        tmp = tmp->next;
    }
    return 0;
}
int deleteItem(Node* arr, int k, int M) {
    int j = searchItem(arr, k, M);
    if (j == 0)return j;
    Node* tmp = &arr[hash(k, M)];

    while (tmp->next->key != k) {
        tmp = tmp->next;
    }
    Node* del = tmp->next;
    tmp->next = tmp->next->next;
    free(del);
    return j;
}
void printItem(Node* arr, int M) {
    Node* tmp;
    for (int i = 0; i < M; i++) {
        tmp = arr[i].next;
        while (tmp != NULL) {
            printf(" %d", tmp->key);
            tmp = tmp->next;
        }
    }
    printf("\n");
    return;
}
int main() {
    int M, k;
    scanf("%d", &M);
    getchar();
    Node* arr = (Node*)malloc(sizeof(Node) * M);
    for (int i = 0; i < M; i++) {
        arr[i].next = NULL;
    }
    char ch;
    while (1) {
        scanf("%c", &ch);
        if (ch == 'i') {
            scanf("%d", &k);
            insertItem(arr, k, M);
        }
        else if (ch == 's') {
            scanf("%d", &k);
            printf("%d\n", searchItem(arr, k, M));
        }
        else if (ch == 'd') {
            scanf("%d", &k);
            printf("%d\n", deleteItem(arr, k, M));
        }
        else if (ch == 'p') {
            printItem(arr, M);
        }
        else if (ch == 'e') {
            free(arr);
            break;
        }
        getchar();
    }

    return 0;
}