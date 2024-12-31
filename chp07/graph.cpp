#include <stdlib.h>
#include <stdio.h>

#define MAXVEX 20
#define INF 999

typedef char VertexType[10]; 

typedef struct vertex {
    int adjvex;
    VertexType data;
} VType;

typedef struct graph {
    int n, e; // n 为实际顶点数，e为实际边数
    VType vex[MAXVEX];  // 顶点集合
    int edges[MAXVEX][MAXVEX]; // 邻接矩阵
} MatGraph;

void createGraph(MatGraph &g, int A[][MAXVEX], int n, int e) {
    g.n = n;
    g.e = e;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            g.edges[i][j] = A[i][j];
        }
    }
}

void destroyGraph(MatGraph &g) {
}

void dispGraph(MatGraph g) {
    for (int i = 0; i < g.n; i++) {
        for (int j = 0; j < g.n; j++) {
            if (g.edges[i][j] < INF) {
                printf("%4d", g.edges[i][j]);
            } else {
                printf("%4s", "**");
            }
        }
        printf("\n");
    }
}

int degree1(MatGraph g, int v) {
    int d = 0;
    if (v < 0 || v >= g.n) {
        return -1;
    }
    for (int i = 0; i < g.n; i++) {
        if (g.edges[v][i] > 0 && g.edges[v][i] < INF) {
            d++;
        }
    }
    return d;
}

int degree2(MatGraph g, int v) {
    int d = 0;
    if (v < 0 || v >= g.n) {
        return -1;
    }
    for (int i = 0; i < g.n; i++) {
        if (g.edges[v][i] > 0 && g.edges[v][i] < INF) {
            d++;
        }
    }
    for (int i = 0; i < g.n; i++) {
        if (g.edges[i][v] > 0 && g.edges[i][v] < INF) {
            d++;
        }
    }
    return d;
}

void runMatGraph() {
    MatGraph g;
    int n = 5;
    int e = 7;
    int A[MAXVEX][MAXVEX] = {
        {0, 1, 2, 6, INF},
        {INF, 0, INF, 4, 5},
        {INF, INF, 0, INF, 3},
        {INF, INF, INF, 0, INF},
        {INF, INF, INF, 7, 0},
    };
    createGraph(g, A, n, e);
    printf("图G的存储结构:\n");
    dispGraph(g);
    printf("图G的所有顶点的度:\n");
    printf("    顶点\t度\n");
    for (int i = 0; i < g.n; i++) {
        printf("    %d\t\t%d\n", i, degree2(g, i));
    }
    destroyGraph(g);
}