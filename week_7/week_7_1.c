#pragma warning (disable : 4996)
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <math.h>
#include <time.h>
typedef struct Node {
    int key,height;
    struct Node* parent;
    struct Node* left;
    struct Node* right;
}Node;
Node* getNode() {
    Node* n = (Node*)malloc(sizeof(Node));
    n->parent = NULL;
    n->left = NULL;
    n->right = NULL;
    return n;
}

void invalidNodeException() {
    printf("invalid\n");
}
int isRoot(Node* p) {
    if (p->parent == NULL) {
        return 1;
    }
    else {
        return 0;
    }
}

int isExternal(Node* w) {
    if (w->left == NULL && w->right == NULL) {
        return 1;
    }
    else {
        return 0;
    }
}
int isInternal(Node* w) {
    if (w->left != NULL || w->right != NULL) {
        return 1;
    }
    else {
        return 0;
    }
}
Node* treeSearch(Node* v, int key) {
    if (isExternal(v)) {
        return v;
    }
    if (v->key == key) {
        return v;
    }
    if (v->key > key) {
        return treeSearch(v->left, key);
    }
    else {
        return treeSearch(v->right, key);
    }
}
int findElement(Node* root, int k) {
    Node* w = treeSearch(root, k);
    if (isExternal(w)) {
        return -1;
    }
    else {
        return w->key;
    }
}

void expandExternal(Node* w) {
    Node*l= getNode();
    Node*r = getNode();
    l->left = NULL;
    l->right = NULL;
    l->parent = w;
    l->height = 0;

    r->left = NULL;
    r->right = NULL;
    r->parent = w;
    r->height = 0;

    w->left = l;
    w->right = r;
    w->height = 1;
}
int updateHeight(Node* w) {
    if (isExternal(w))return 0;
    updateHeight(w->left);
    updateHeight(w->right);
    if (w->left->height > w->right->height) {
        w->height = w->left->height + 1;
    }
    else {
        w->height = w->right->height + 1;
    }
}
int isBalance(Node* w) {
    int gap = w->left->height - w->right->height;
    if (gap >= -1 && gap <= 1) {
        return 1;
    }
    else {
        return 0;
    }
}
void restructure(Node* x, Node* y, Node* z, Node** root) {
    Node* a, * b, * c, * T0, * T1, * T2, * T3;
    if (x->key < y->key && y->key < z->key) {
        a = x, b = y, c = z;
        T0 = x->left;
        T1 = x->right;
        T2 = y->right;
        T3 = z->right;
    }
    else if (z->key < y->key && y->key < x->key) {
        a = z, b = y, c = x;
        T0 = z->left;
        T1 = y->left;
        T2 = x->left;
        T3 = x->right;
    }
    else if (y->key < x->key && x->key < z->key) {
        a = y, b = x, c = z;
        T0 = y->left;
        T1 = x->left;
        T2 = x->right;
        T3 = z->right;
    }
    else{
        a = z, b = x, c = y;
        T0 = z->left;
        T1 = x->left;
        T2 = x->right;
        T3 = y->right;
    }

    if (z == *root) {
        *root = b;
        b->parent = NULL;
    }
    else if (z->parent->left == z) {
        z->parent->left = b;
        b->parent = z->parent;
    }
    else {
        z->parent->right = b;
        b->parent = z->parent;
    }

    a->left = T0;
    a->right = T1;
    T0->parent = a;
    T1->parent = a;
    updateHeight(a);

    c->left = T2;
    c->right = T3;
    T2->parent = c;
    T3->parent = c;
    updateHeight(c);

    b->left = a;
    b->right = c;
    a->parent = b;
    c->parent = b;
    updateHeight(b);
}
void searchAndFixAfterInsertion(Node** root, Node* w) {
    Node* z = w;
    if (isRoot(z))return;

    z = z->parent;
    while (updateHeight(z) && isBalance(z)) {
        if (isRoot(z))return;
        z = z->parent;
    }
    if (isBalance(z))return;


    Node* y;
    if (z->left->height > z->right->height) {
        y = z->left;
    }
    else {
        y = z->right;
    }

    Node* x;
    if (y->left->height > y->right->height) {
        x = y->left;
    }
    else {
        x = y->right;
    }

    restructure(x, y, z, root);
}
void insertItem(Node** root, int k) {
    Node* w = treeSearch(*root, k);
    if (isInternal(w)) {
        invalidNodeException();
    }
    w->key = k;
    expandExternal(w);
    searchAndFixAfterInsertion(root,w);

}

/*
Node* sibling(Node* w) {
	if (isRoot(w)) {
		invalidNodeException();
		return;
	}
	if (w->parent->left == w) {
		return w->parent->right;
	}
	else {
		return w->parent->left;
	}
}
Node* inOrderSucc(Node* w) {
	w = w->right;
	if (isExternal(w)) {
		invalidNodeException();
	}
	else {
		while (isInternal(w->left)) {
			w = w->left;
		}
	}
	return w;
}
Node* reduceExternal(Node* z, Node** root) {
	Node* w = z->parent;
	Node* zs = sibling(z);
	if (isRoot(w)) {
		*root = zs;
		zs->parent = NULL;
	}
	else {
		Node* g = w->parent;
		zs->parent = g;
		if (g->left == w) {
			g->left = zs;
		}
		else {
			g->right = zs;
		}
	}
	free(z);
	free(w);
	return zs;
}

int removeElement(Node** root, int key) {
	Node* w = treeSearch(*root, key);
	if (isExternal(w)) {
		return -1;
	}
	int k = w->key;
	//Case 1 : 둘 중에 하나가 외부노드라면
	Node* z = w->left;
	if (isInternal(z)) {
		z = w->right;
	}
	if (isExternal(z)) {
		reduceExternal(z, root);
	}
	else {
		Node* y = inOrderSucc(w);
		w->key = y->key;
		Node* z = y->left;
		reduceExternal(z, root);
	}
	return k;
}*/
void printTree(Node* root) {
    if (isExternal(root)) {
        return;
    }
    printf(" %d", root->key);
    printTree(root->left);
    printTree(root->right);
}
int main()
{
    char ch;
    int key;
    Node* root = getNode();
    while (1) {
        scanf("%c", &ch);
        if (ch == 'i') {
            scanf("%d", &key);
            insertItem(&root, key);
        }
            /*else if (ch == 'd') {
                scanf("%d", &key);
                int tmp = removeElement(&root, key);
                if (tmp == -1) {
                    printf("X\n");
                }
                else {
                    printf("%d\n", tmp);
                }
            }*/
        else if (ch == 's') {
            scanf("%d", &key);
            int tmp = findElement(root, key);
            if (tmp == -1) {
                printf("X\n");
            }
            else {
                printf("%d\n", tmp);
            }
        }
        else if (ch == 'p') {
            printTree(root);
            printf("\n");
        }
        else if (ch == 'q') {
            break;
        }
        getchar();
    }

    return 0;
}
