#pragma warning (disable : 4996)
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <math.h>
#include <time.h>
typedef struct Vertex {
    int inDegree;
    char name;
    struct IncidentList* icd;
}Vertex;
typedef struct Edge {
    struct Vertex* start;
    struct Vertex* end;
}Edge;
typedef struct IncidentList {
    struct Edge* eg;
    struct IncidentList* next;
}IncidentList;
typedef struct Graph {
    struct Vertex *vertex;
    struct Edge *edge;
}Graph;
int index(Graph* g, int n, char name) {
    for (int i = 0; i < n; i++) {
        if (g->vertex[i].name == name) {
            return i;
        }
    }
}
void insertVEA(Graph* g, int n, char name1, char name2) {
    Vertex* s = &(g->vertex[index(g, n, name1)]);
    Vertex* e = &(g->vertex[index(g, n, name2)]);

    Edge* eg = (Edge*)malloc(sizeof(Edge));
    eg->start = s;
    eg->end = e;
    eg->end->inDegree++;

    IncidentList* incidentList = (IncidentList*)malloc(sizeof(IncidentList));
    incidentList->eg = eg;
    incidentList->next = s->icd->next;
    s->icd->next = incidentList;
}
void insertVertex(Graph* g, int n) {
    g->vertex = (Vertex*)malloc(sizeof(Vertex) * n);
    for (int i = 0; i < n; i++) {
        getchar();
        scanf("%c", &g->vertex[i].name);
        g->vertex[i].icd = (IncidentList*)malloc(sizeof(IncidentList));
        g->vertex[i].icd->next = NULL;
    }
}
void insertDirectedEdge(Graph* g, int n, int m) {
    g->edge = (Edge*)malloc(sizeof(Edge) * m);
    char name1, name2;
    for (int i = 0; i < m; i++) {
        scanf("%c %c", &name1, &name2);
        getchar();
        insertVEA(g, n, name1, name2);
    }
}
int topologicalSort(Graph* g, int n, int* topSort) {
    int* queue = (int*)malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++) {
        queue[i] = -1;
    }
    int l = 0, top=0;
    for (int i = 0; i < n; i++) {
        if (g->vertex[i].inDegree == 0) {
            queue[l] = i;
            l++;
        }
    }
    while (queue[0] != -1) {
        topSort[top] = queue[0];
        top++;
        for (int i = 0; i < l; i++) {
            queue[i] = queue[i + 1];
        }
        l--;
        IncidentList* tmp = g->vertex[topSort[top - 1]].icd->next;
        while (tmp != NULL) {
            tmp->eg->end->inDegree--;
            if (tmp->eg->end->inDegree == 0) {
                queue[l] = index(g, n, tmp->eg->end->name);
                l++;
            }
            tmp = tmp->next;
        }
    }
    if (top < n) {
        return 0;
    }
    else {
        return 1;
    }
}
int main()
{
    int n, m;
    scanf("%d", &n);
    Graph g;
    insertVertex(&g, n);
    getchar();
    scanf("%d", &m);
    getchar();
    insertDirectedEdge(&g, n, m);


    int* topSort = (int*)malloc(sizeof(int) * n);
    int tmp = topologicalSort(&g, n, topSort);
    if (tmp == 0) {
        printf("0\n");

    }
    else {
        for (int i = 0; i < n; i++) {
            printf("%c", g.vertex[topSort[i]].name);
        }
    }
    return 0;
}
