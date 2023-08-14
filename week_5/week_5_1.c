#pragma warning (disable : 4996)
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <math.h>
#include <time.h>
typedef struct Node {
    int elem;
    struct Node* next;
}Node;
Node* getNode() {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->next = NULL;
    return newNode;
}
void print(Node* L) {
    while (L != NULL) {
        printf("%d ", L->elem);
        L = L->next;
    }
    printf("\n");
}
void insert(Node*L, int elem) {
    Node* q = getNode();
    q->elem = elem;
    //printf("%d", q->elem);
    while (L->next != NULL) {
        L = L->next;
        //printf("%d\n", L->elem);
    }
    //printf("%d\n", L->elem);
    L->next = q;
    //printf("%d\n", L->elem);
}
Node *partition(Node* L1, int k) {
    for (int i = 0; i < k-1; i++) {
        L1 = L1->next;
    }
    Node* L2 = L1->next;
    L1->next = NULL;
    return L2;
}
Node* merge(Node* L1, Node* L2) {

    Node* L;
    if (L1->elem >= L2->elem) {
        L = L2;
        L2 = L2->next;
    }
    else {
        L = L1;
        L1 = L1->next;
    }
    Node* p = L;
    while (L1!=NULL && L2!=NULL) {

        if (L1->elem >= L2->elem) {
            L->next = L2;
            L2 = L2->next;
        }
        else {
            L->next = L1;
            L1 = L1->next;
        }
        L = L->next;
    }
    if (L1 != NULL) {
        L->next = L1;
    }
    else {
        L->next = L2;
    }
    //print(L);
    return p;
}
Node* mergeSort(Node* L, int k) {
    //printf("k=%d\n", k);
    if (k == 1) {
        return L;
    }
    Node* L1, * L2;
    L1 = L;
    L2 = partition(L, k / 2);
    //printf("k/2=%d\n", k / 2);

    L1 = mergeSort(L1, k / 2);
    L2 = mergeSort(L2, k - k / 2);

    merge(L1, L2);
}

int main()
{
    int n;
    Node* L=getNode();
    Node* p;
    int e;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &e);
        if (i == 0) {
            L->elem = e;
        }
        else insert(L, e);
    }

    p = mergeSort(L, n);

    print(p);

    /*free(p);
    free(L);*/
    return 0;
}
