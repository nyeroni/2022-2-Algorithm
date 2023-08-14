#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0
#define INF 1000000000

struct Edge;

typedef struct Vertex
{
    int num, isVist;
    struct Edge* eg;
    struct Vertex* next;
}Vertex;

typedef struct Edge
{
    Vertex* vt;
    int weight;
    struct Edge* next;
}Edge;

typedef struct Graph
{
    Vertex* vertex;
    int vCnt;
}Graph;

void initGraph(Graph* x)
{
    x->vertex = NULL;
    x->vCnt = 0;
}

Vertex* findVertex(Graph* x, int v)
{
    Vertex* p = x->vertex;
    while (p->num != v)
        p = p->next;
    return p;
}

void insertVertex(Graph* g, int vName)
{
    Vertex* new = malloc(sizeof(Vertex));
    new->num = vName;
    new->isVist = FALSE;
    new->next = NULL;
    new->eg = NULL;

    if (g->vertex == NULL)
        g->vertex = new;
    else
    {
        Vertex* p = g->vertex;
        while (p->next)
            p = p->next;
        p->next = new;
    }
    g->vCnt++;
}

void addEdge(Vertex* v1, Vertex* v2, int w)
{
    Edge* new = malloc(sizeof(Edge));
    new->vt = v2;
    new->weight = w;
    new->next = NULL;

    Edge* q = v1->eg;
    if (q == NULL)
        v1->eg = new;
    else
    {
        if (v1->eg->weight > new->weight)
        {
            v1->eg = new;
            new->next = q;
        }
        else
        {
            while (q->next && q->next->weight < new->weight)
                q = q->next;
            new->next = q->next;
            q->next = new;
        }
    }
}

void makeEdge(Graph* x, int v1, int v2, int w)
{
    Vertex* V1 = findVertex(x, v1);
    Vertex* V2 = findVertex(x, v2);

    addEdge(V1, V2, w);
    if (v1 != v2)
        addEdge(V2, V1, w);
}

void printGraph(Graph* x)
{
    for (Vertex* p = x->vertex; p; p = p->next)
    {
        printf("{%d} :", p->num);
        for (Edge* q = p->eg; q; q = q->next)
            printf(" (av : %d, w : %d)", q->vt->num, q->weight);
        printf("\n");
    }
}

Vertex* getMinVertex(Graph* x, int d[])
{
    Vertex* p = x->vertex;
    Vertex* min;
    for (; p; p = p->next)
        if (p->isVist == FALSE)
        {
            min = p;
            break;
        }
    for (p = x->vertex; p; p = p->next)
        if (p->isVist == FALSE && d[p->num] < d[min->num])
            min = p;
    return min;
}

void dijkstra(Graph* x, int v, int dis[])
{
    dis[v] = 0;
    for (int i = 0; i < x->vCnt; i++)
    {
        Vertex* p = getMinVertex(x, dis);
        p->isVist = TRUE;
        for (Edge* q = p->eg; q; q = q->next)
            if (q->vt->isVist == FALSE && dis[q->vt->num] > dis[p->num] + q->weight)
                dis[q->vt->num] = dis[p->num] + q->weight;
        p = p->next;
    }
}

int main()
{
    Graph g; initGraph(&g);
    int n, m, s; scanf("%d %d %d", &n, &m, &s);
    for (int i = 1; i <= n; i++)
        insertVertex(&g, i);
    for (int i = 0; i < m; i++)
    {
        int v1, v2, w;
        scanf("%d %d %d", &v1, &v2, &w);
        makeEdge(&g, v1, v2, w);
    }

    int* dis = calloc(n + 1, sizeof(int));
    for (int i = 0; i < n + 1; i++)
        dis[i] = INF;
    dijkstra(&g, s, dis);
    for (int i = 1; i < n + 1; i++)
        if (i != s && dis[i] != INF)
            printf("%d %d\n", i, dis[i]);
    return 0;
}