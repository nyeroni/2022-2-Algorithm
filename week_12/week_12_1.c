#pragma warning (disable : 4996)
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <math.h>
#include <time.h>
#define INFINITE 99999;
typedef struct Edge {
    int vertex1, vertex2;
    int weight;
}Edge;
typedef struct Incident {
    int edge;
    struct Incident* next;
}Incident;
typedef struct Vertex {
    int num;
    int distance;
    struct Incident* head;
}Vertex;
typedef struct Graph {
    Vertex* vertex;
    Edge* edge;
    int n, m;
}Graph;
typedef struct Heap {
    int key;
    int distance;
}Heap;
Graph g;
void insertVertex(int i) {
    g.vertex[i].num = i;
    g.vertex[i].head = (Incident*)malloc(sizeof(Incident));

    g.vertex[i].head->next = NULL;
}
void initGraph(int n, int m) {
    g.n = n;
    g.m = m;
    g.vertex = (Vertex*)malloc(sizeof(Vertex) * (n + 1));//1부터 시작
    g.edge = (Edge*)malloc(sizeof(Edge)* m);

    for (int i = 1; i <= n; i++) {
        insertVertex(i);
    }
}
void addFirst(Incident* head, int i) {
    Incident* node = (Incident*)malloc(sizeof(Incident));
    node->edge = i;
    node->next = head->next;
    head->next = node;
}
void insertIncidentEdge(int v1, int v2, int w, int i) {
    g.edge[i].vertex1 = v1;
    g.edge[i].vertex2 = v2;
    g.edge[i].weight = w;

    addFirst(g.vertex[v1].head, i);
    addFirst(g.vertex[v2].head, i);
}
void buildGraph() {
    int n, m;
    int v1, v2, w;
    scanf("%d %d", &n, &m);
    initGraph(n, m);
    for (int i = 0; i < g.m; i++) {
        scanf("%d %d %d", &v1, &v2, &w);
        insertIncidentEdge(v1, v2, w, i);
    }
}
void swapElem(Heap* x, Heap* y) {
    Heap tmp;
    tmp = *x;
    *x = *y;
    *y = tmp;
}
void downHeap(Heap* heap, int i, int size) {
    int l = 2 * i;
    int r = 2 * i + 1;
    int smaller;

    if (l > size) {
        return;
    }
    smaller = l;
    if (r <= size) {
        if (heap[r].distance < heap[l].distance) {
            smaller = r;
        }
    }

    if (heap[i].distance <= heap[smaller].distance) {
        return;
    }

    swapElem(heap + i, heap + smaller);
    downHeap(heap, smaller, size);
}
Heap* buildHeap() {
    Heap* heap = (Heap*)malloc(sizeof(Heap) * (g.n + 1));
    for (int i = 1; i <= g.n; i++) {
        heap[i].distance = g.vertex[i].distance;
        heap[i].key = g.vertex[i].num;
    }

    for (int i = g.n / 2; i >= 1; i--) {
        downHeap(heap, i, g.n);
    }
    return heap;
}
int removeMin(Heap* heap, int i) {
    Heap res;
    if (i == 0) {
        return -1;
    }
    res = heap[1];
    swapElem(heap + 1, heap + i);
    downHeap(heap, 1, --i);

    return res.key;
}
int opposite(int u, int e) {
    if (g.edge[e].vertex1 == u) {
        return g.edge[e].vertex2;
    }
    else {
        return g.edge[e].vertex1;
    }
}
int isInclude(Heap* heap, int i, int z) {
    for (int j = 1; j < i; j++) {
        if (heap[j].key == z) {
            return 1;
        }
    }
    return 0;
}
void upHeap(Heap* heap, int i) {
    if (i == 1) {
        return;
    }
    if (heap[i].distance >= heap[i / 2].distance) {
        return;
    }
    swapElem(heap + i, heap + i / 2);
    upHeap(heap, i / 2);
}
void replaceKey(Heap* heap, int i, int z, int w) {
    int j;
    for (j = 1; j < i; j++) {
        if (heap[j].key == z) {
            heap[j].distance = w;
            break;
        }
    }
    upHeap(heap, j);
}
void primJarnikMST() {
    Heap* heap;
    Incident* icd;
    int sum, u, z, i;

    for (int j = 1; j <= g.n; j++) {
        g.vertex[j].distance = INFINITE;
    }
    g.vertex[1].distance = 0;
    heap = buildHeap();

    sum = 0;
    i = g.n;
    while (i > 0) {
        u = removeMin(heap, i);
        printf(" %d", g.vertex[u].num);

        sum += g.vertex[u].distance;

        icd = g.vertex[u].head->next;
        while (icd != NULL) {
            z = opposite(u, icd->edge);
            if (isInclude(heap, i, z) && g.edge[icd->edge].weight < g.vertex[z].distance) {
                g.vertex[z].distance = g.edge[icd->edge].weight;
                replaceKey(heap, i, z, g.vertex[z].distance);
            }
            icd = icd->next;
        }
        i--;
    }
    printf("\n%d", sum);
    free(heap);

}
void freeGraph() {
    Incident* node, * next;
    for (int i = 1; i <= g.n; i++) {
        node = g.vertex[i].head;
        while (node != NULL) {
            next = node->next;
            free(node);
            node = next;
        }
    }
    free(g.vertex);
    free(g.edge);
}
int main()
{
    Incident* head;
    buildGraph();
    primJarnikMST();
    freeGraph();
    return 0;
}
