#include <stdlib.h>
#include <stdio.h>

#define MAXVEX 20
#define INF 999

typedef char VertexType[10]; // 定义vertex type为字符串类型

typedef struct edgenode {
    int adjvex; // 相邻点编号
    int weight; // 边权值
    struct edgenode *nextarc; // 下一条边的顶点
} ArcNode;

typedef struct vexnode {
    VertexType data; // 存放一个顶点的信息
    ArcNode *firstarc; // 指向第一个边结点
} VHeadNode;

typedef struct {
    int n, e; // n为实际顶点数，e为实际边数
    VHeadNode adjlist[MAXVEX]; // 单链表头结点数组
} AdjGraph;


// ------------------- graph.cpp 数据结构 -----------------
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
// ------------------- graph.cpp 数据结构 -----------------


// createGraph 建立图的邻接表运算算法
void createGraph(AdjGraph *&G, int A[][MAXVEX], int n, int e) {
    G = (AdjGraph *) malloc(sizeof(AdjGraph));
    G->n = n;
    G->e = e;
    for (int i = 0; i < G->n; i++) {
        G->adjlist[i].firstarc = NULL; // 邻接表中所有头结点指针置空
    }
    ArcNode *p;
    for (int i = 0; i < G->n; i++) {
        for (int j = G->n - 1; j >= 0; j--) {
            if (A[i][j] > 0 && A[i][j] < INF) {
                p = (ArcNode *) malloc(sizeof(ArcNode));
                p->adjvex = j;
                p->weight = A[i][j];
                p->nextarc = G->adjlist[i].firstarc; // 采用头插法插入p
                G->adjlist[i].firstarc = p;
            }
        }
    }
}

// destroyGraph 销毁图算法
void destroyGraph(AdjGraph *&G) {
    ArcNode *pre, *p;
    for (int i = 0; i < G->n; i++) {
        pre = G->adjlist[i].firstarc;
        if (pre != NULL) {
            p = pre->nextarc;
            while (p != NULL) {
                free(pre);
                pre = p;
                p = p->nextarc;
            }
            free(pre);
        }
    }
    free(G);
}

// dispGraph 输出图运算算法
void dispGraph(AdjGraph *G) {
    ArcNode *p;
    for (int i = 0; i < G->n; i++) {
        printf(" [%d]", i);
        p = G->adjlist[i].firstarc;
        if (p != NULL) {
            printf("->");
        }
        while (p != NULL) {
            printf(" %d(%d)", p->adjvex, p->weight);
            p = p->nextarc;
        }
        printf("\n");
    }
}

// degree1 求顶点度运算算法
int degree1(AdjGraph *G, int v) {
    int d = 0;
    if (v < 0 || v >= G->n) {
        return -1;
    }
    ArcNode *p = G->adjlist[v].firstarc;
    while (p != NULL) {
        d++;
        p = p->nextarc;
    }
    return d;
}


// degree2 求有向图中顶点v的度
int degree2(AdjGraph *G, int v) {
    int d = 0;
    if (v < 0 || v >= G->n) {
        return -1;
    }
    ArcNode *p = G->adjlist[v].firstarc;
    while (p != NULL) {
        d++;
        p = p->nextarc;
    }
    for (int i = 0; i < G->n; i++) {
        p = G->adjlist[i].firstarc;
        while (p != NULL) {
            if (p->adjvex == v) {
                d++;
            }
            p = p->nextarc;
        }
    }
    return d;
}


void runAdjGraph() {
    int n = 5;
    int e = 7;
    int A[MAXVEX][MAXVEX] = {
      {0, 1, 2, 6, INF},
      {INF, 0, INF, 4, 5},
      {INF, INF, 0, INF, 3},
      {INF, INF, INF, 0, INF},
      {INF, INF, INF, 7, 0},
    };
    AdjGraph *G;
    createGraph(G, A, n, e);

    printf("图G存储结构:\n");
    dispGraph(G);
    printf("图G中所有顶点的度:\n");
    printf("    顶点\t度\n");

    for (int i = 0; i < G->n; i++) {
        printf("    %d\t\t%d\n", i, degree2(G, i));
    }

    destroyGraph(G);
}

// matToAdj 将邻接矩阵g转换为邻接表G
void matToAdj(MatGraph g, AdjGraph *&G) {
    G = (AdjGraph *) malloc(sizeof(AdjGraph));
    for (int i = 0; i < g.n; i++) {
        G->adjlist[i].firstarc = NULL;
    }
    int w = 0;
    ArcNode *p;
    for (int i = 0; i < g.n; i++) {
        for (int j = g.n - 1; j >=0; j--) {
            w = g.edges[i][j];
            if (w != 0 && w != INF) {
                p = (ArcNode *) malloc(sizeof(ArcNode));
                p->adjvex = j;
                p->weight = w;
                // 采用头插法
                p->nextarc = G->adjlist[i].firstarc;
                G->adjlist[i].firstarc = p;
            }
        }
    }
    G->n = g.n;
    G->e = g.e;
}

// adjToMat 邻接表G转换为邻接矩阵
void adjToMat(AdjGraph *G, MatGraph &g) {
    // 矩阵初始化
    for (int i = 0; i < G->n; i++) {
        for (int j = 0; j < G->n; j++) {
            if (i == j) {
                g.edges[i][j] = 0;
                continue;
            }
            g.edges[i][j] = INF;
        }
    }
    // 赋值
    ArcNode *p;
    for (int i = 0; i < G->n; i++) {
        p = G->adjlist[i].firstarc;
        while (p != NULL) {
            g.edges[i][p->adjvex] = p->weight;
            p = p->nextarc;
        }
    }
    // n,e 赋值
    g.n = G->n;
    g.e = G->e;
}


// ------------- 图的遍历 --------------

int visited[MAXVEX] = {0};


void dfs(AdjGraph *G, int v) {
    printf("%d ", v);
    visited[v] = 1;
    ArcNode *p = G->adjlist[v].firstarc;
    int w;
    while (p != NULL) {
        w = p->adjvex;
        if (visited[w] == 0) {
            dfs(G, w);
        }
        p = p->nextarc;
    }
}


