#pragma warning (disable : 4996)
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
typedef struct Node {
    int elem;
    struct Node* LEFT;
    struct Node* RIGHT;
}Node;

Node* getNode() {
    Node* TREE=(Node*)malloc(sizeof(Node));
    TREE->LEFT = NULL;
    TREE->RIGHT = NULL;
    return TREE;
}
Node* find(Node* p, int x) {
    Node* tmp = p;
    if (tmp != NULL) {
        if (tmp->elem == x) {
            return tmp;
        }
        Node* q = NULL;
        q = find(tmp->LEFT, x);
        if (q != NULL) {
            return q;
        }
        q = find(tmp->RIGHT, x);
        if (q != NULL) {
            return q;
        }
    }
    return NULL;

}
void maketree(Node* root) {
    Node* p = root;
    int n, x, y, z;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d %d %d", &x, &y, &z);
        if (i == 0) {
            root->elem = x;
            if (y != 0) {
                root->LEFT = getNode();
                root->LEFT->elem = y;
            }
            if (z != 0) {
                root->RIGHT = getNode();
                root->RIGHT->elem = z;
            }
        }
        else {
            Node *q=find(p,x);
            if (y != 0) {
                q->LEFT = getNode();
                q->LEFT->elem = y;
            }
            if (z != 0) {
                q->RIGHT = getNode();
                q->RIGHT->elem = z;
            }
        }
    }

}
void search(Node *root) {
    int n;
    scanf("%d", &n);
    getchar();
    Node* p = root;

    for (int i = 0; i < n; i++) {
        char str[101];
        scanf("%s", str);
        getchar();
        int len=strlen(str);
        p = root;
        for (int j = 0; j <= len; j++) {
            printf(" %d", p->elem);
            if (str[j] == 'L') {
                p = p->LEFT;
            }
            else if (str[j] == 'R') {
                p = p->RIGHT;
            }
        }
        printf("\n");
    }
}
int main(void) {
    Node* root = getNode();
    maketree(root);
    search(root);
    return 0;
}