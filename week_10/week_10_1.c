#pragma warning (disable : 4996)
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
typedef struct Vertex {
    int v_visit;
    int num;
    struct IncidentList* icd;
}Vertex;
typedef struct Edge {
    int e_visit;
    struct Vertex* start;
    struct Vertex* end;
}Edge;
typedef struct IncidentList {
    struct Edge* eg;
    struct IncidentList* next;
}IncidentList;
typedef struct Graph {
    struct Vertex* vertex;
    struct Edge* edge;
}Graph;
void initGraph(Graph* g, int n, int m) {
    g->vertex = (Vertex*)malloc(sizeof(Vertex)*n);
    g->edge = (Edge*)malloc(sizeof(Edge) * m);
    for (int i = 0; i < n; i++) {
        g->vertex[i].num = i + 1;
        g->vertex[i].icd = (IncidentList*)malloc(sizeof(IncidentList));
        g->vertex[i].icd->next = NULL;
    }
}
void insertIncidentList(Vertex* v, Edge* e) {
    IncidentList* icdL = (IncidentList*)malloc(sizeof(IncidentList));
    icdL->eg = e;

    Vertex* tmpv;
    if (e->start == v) {
        tmpv = e->end;
    }
    else tmpv = e->start;

    IncidentList* tmpI = v->icd;
    while (tmpI->next != NULL) {
        if (tmpI->next->eg->start == v) {
            if (tmpI->next->eg->end->num < tmpv->num) {
                tmpI = tmpI->next;
            }
            else break;
        }
        else {
            if (tmpI->next->eg->start->num < tmpv->num) {
                tmpI = tmpI->next;
            }
            else break;
        }
    }

    icdL->next = tmpI->next;
    tmpI->next = icdL;
}
void insertVEA(Graph* g, int num1, int num2) {
    Vertex* v1 = &(g->vertex[num1 - 1]);
    Vertex* v2 = &(g->vertex[num2 - 1]);

    Edge* eg = (Edge*)malloc(sizeof(Edge));
    eg->start = v1;
    eg->end = v2;

    insertIncidentList(v1, eg);
    if (num1 != num2) {
        insertIncidentList(v2, eg);
    }
}
void DFS(Graph* g, int num) {
    printf("%d\n", num);
    int i = num - 1;
    g->vertex[i].v_visit = 1;

    IncidentList* tmp = g->vertex[i].icd->next;
    while (tmp != NULL) {
        if (tmp->eg->e_visit == 0) {
            if (tmp->eg->start->num == g->vertex[i].num) {
                if (tmp->eg->end->v_visit == 1) {
                    tmp->eg->e_visit = 2;
                }
                else {
                    tmp->eg->e_visit = 1;
                    DFS(g, tmp->eg->end->num);
                }
            }
            else {
                if (tmp->eg->start->v_visit == 1) {
                    tmp->eg->e_visit = 2;
                }
                else {
                    tmp->eg->e_visit = 1;
                    DFS(g, tmp->eg->start->num);
                }
            }
        }
        else {
            tmp = tmp->next;
        }
    }
    return;
}
int main() {
    Graph g;
    int num1, num2, n, m, s;
    scanf("%d %d %d", &n, &m, &s);
    initGraph(&g,n,m);
    for (int i = 0; i < m; i++) {
        scanf("%d %d", &num1, &num2);
        insertVEA(&g, num1, num2);
    }
    DFS(&g, s);
    return 0;
}