#pragma warning (disable : 4996)
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
typedef struct Vertex {
    int num;
    int v_visit;
}Vertex;
typedef struct Edge {
    struct Vertex* start;
    struct Vertex* end;
    int e_visit;
}Edge;
typedef struct Graph {
    struct Vertex* vertex;
    struct Edge* edge;
}Graph;
void initGraph(Graph* g, int n, int m) {
    g->vertex = (Vertex*)malloc(sizeof(Vertex) * n);
    g->edge = (Edge*)malloc(sizeof(Edge) * m);

    for (int i = 0; i < n; i++) {
        g->vertex[i].num = i + 1;
    }
}
void insertVEA(Graph* g, Edge*** E, int num1, int num2) {
    Vertex* v1 = &(g->vertex[num1 - 1]);
    Vertex* v2 = &(g->vertex[num2 - 1]);

    Edge* eg = (Edge*)malloc(sizeof(Edge));
    eg->start = v1;
    eg->end = v2;

    E[num1 - 1][num2 - 1] = eg;
    if (num1 != num2) {
        E[num2 - 1][num1 - 1] = eg;
    }
}
void BFS(Graph* g, Edge*** E, int num, int n) {
    int* queue = (int*)malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++) {
        queue[i] = 0;
    }
    queue[0] = num;
    int l = 1, i;
    while (queue[0] != 0) {
        num = queue[0];
        i = num - 1;
        printf("%d\n", num);
        for (int j = 0; j < l; j++) {
            queue[j] = queue[j + 1];
        }
        l--;
        for (int j = 0; j < n; j++) {
            if (E[i][j] == NULL) {
                continue;
            }
            if (E[i][j]->e_visit == 0) {
                if (E[i][j]->start->num == num) {
                    if (E[i][j]->end->v_visit == 0) {
                        queue[l] = j + 1;
                        l++;
                        E[i][j]->e_visit = 1;
                        E[i][j]->end->v_visit = 1;
                    }
                    else {
                        E[i][j]->e_visit = 2;
                    }
                }
                else {
                    if (E[i][j]->start->v_visit == 0) {
                        queue[l] = j + 1;
                        l++;
                        E[i][j]->start->v_visit = 1;
                        E[i][j]->e_visit = 1;
                    }
                    else {
                        E[i][j]->e_visit = 2;
                    }
                }
            }
        }
    }
}
int main() {
    int n, m, s, num1, num2;
    scanf("%d %d %d", &n, &m, &s);
    Graph g;
    initGraph(&g, n, m);
    Edge*** E = (Edge***)malloc(sizeof(Edge**) * n);
    for (int i = 0; i < n; i++) {
        E[i] = (Edge*)malloc(sizeof(Edge) * n);
        for (int j = 0; j < n; j++) {
            E[i][j] = NULL;
        }
    }
    for (int i = 0; i < m; i++) {
        scanf("%d %d", &num1, &num2);
        insertVEA(&g, E,num1, num2);
    }
    BFS(&g, E, s, n);
    return 0;
}