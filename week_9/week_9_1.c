#pragma warning (disable : 4996)
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <math.h>
#include <time.h>
typedef struct Vertex {
    int num;
}Vertex;
typedef struct Edge {
    int weight;
    struct Vertex* start;
    struct Vertex* end;
}Edge;
typedef struct Graph {
    Vertex vertex[6];
    Edge edge[8];
}Graph;
void insertVE(Graph* g, Edge **E, int num1, int num2, int w) {
    Vertex* v1 = &(g->vertex[num1 - 1]);
    Vertex* v2 = &(g->vertex[num2 - 1]);

    Edge eg;
    eg.start = v1;
    eg.end = v2;
    eg.weight = w;

    E[num1 - 1][num2 - 1] = eg;
    if (num1 != num2)E[num2 - 1][num1 - 1]=eg;
}
int isEmpty(Edge e) {
    if (e.start == NULL || e.end == NULL)return 1;
    else return 0;
}
void modifyGraph(Graph* g,Edge **E, int num1, int num2, int w) {
    if (num1 < 1 || num1>6 || num2 < 1 || num2>6) {
        printf("-1\n");
        return;
    }
    if (w == 0) {
        if (isEmpty(E[num1 - 1][num2 - 1]))return;
        else {
            E[num1 - 1][num2 - 1].start = NULL;
            E[num1 - 1][num2 - 1].end = NULL;
            E[num1 - 1][num2 - 1].weight = 0;
            if (num1 != num2) {
                E[num2 - 1][num1 - 1].start = NULL;
                E[num2 - 1][num1 - 1].end = NULL;
                E[num2 - 1][num1 - 1].weight = 0;
            }
        }
    }
    else {
        if (isEmpty(E[num1 - 1][num2 - 1])) {
            insertVE(g, E, num1, num2, w);
        }
        else {
            E[num1 - 1][num2 - 1].weight = w;
            if (num1 != num2) {
                E[num2 - 1][num1 - 1].weight = w;
            }
        }
    }
}
void searchIcdVertex(Graph* g, Edge **E, int num) {
    if (num < 1 || num>6) {
        printf("-1\n");
        return;
    }
    for (int i = 0; i < 6; i++) {
        if (!isEmpty(E[num - 1][i])) {
            if (E[num - 1][i].start == &(g->vertex[num - 1])) {
                printf(" %d %d", E[num - 1][i].end->num, E[num - 1][i].weight);
            }
            else {
                printf(" %d %d", E[num - 1][i].start->num, E[num - 1][i].weight);
            }
        }
        printf("\n");
    }
}
int main()
{
    Graph g;
    Edge** E = (Edge**)malloc(sizeof(Edge*) * 6);
    for (int i = 0; i < 6; i++) {
        E[i] = (Edge*)malloc(sizeof(Edge) * 6);
        for (int j = 0; j < 6; j++) {
            E[i][j].start = NULL;
            E[i][j].end = NULL;

        }
        g.vertex[i].num = i + 1;
    }
    insertVE(&g, E, 1, 2, 1);
    insertVE(&g, E, 1, 3, 1);
    insertVE(&g, E, 1, 4, 1);
    insertVE(&g, E, 1, 6, 2);
    insertVE(&g, E, 2, 3, 1);
    insertVE(&g, E, 3, 5, 4);
    insertVE(&g, E,5, 5, 4);
    insertVE(&g, E,5, 6, 3);

    char ch;
    int num,num1, num2, w;
    while (1) {
        scanf("%c", &ch);
        if (ch == 'a') {
            scanf("%d", &num);
            searchIcdVertex(&g, E,num);
        }
        else if (ch == 'm') {
            scanf("%d %d %d", &num1, &num2, &w);
            modifyGraph(&g, E, num1, num2, w);
        }
        else if (ch == 'q') {
            break;
        }
        getchar();
    }
    return 0;
}
