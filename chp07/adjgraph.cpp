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

int visited[MAXVEX];


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

// bfs 广度优先遍历算法
void bfs(AdjGraph *G, int v) {
    // 定义顶点访问标记
    int visited[MAXVEX];
    for (int i = 0; i < G->n; i++) {
        visited[i] = 0;
    }
    printf("%d ", v);
    visited[v] = 1;

    // 定义一个队列
    int Qu[MAXVEX];
    int front = 0, rear = 0;
    rear = (rear + 1) % MAXVEX;
    Qu[rear] = v;

    ArcNode *p;
    int w;

    // 只要队列中不为空
    while (rear != front) {
        // 取出队列头部结点
        front = (front + 1) % MAXVEX;
        w = Qu[front];
        p = G->adjlist[w].firstarc;

        // 开始遍历和当前p结点相邻的元素
        while (p != NULL) {
            if (visited[p->adjvex] == 0) {
                // 访问该节点，并标记为已访问
                printf("%d ", p->adjvex);
                visited[p->adjvex] = 1;

                // 加入到队列que中
                rear = (rear + 1) % MAXVEX;
                Qu[rear] = p->adjvex;
            }
            // 一直往后遍历其余相邻结点
            p = p->nextarc;
        }
    }
}


void runFS() {
    int n = 5;
    int e = 6;
    int A[MAXVEX][MAXVEX] = {
        {0, 1, 0, 1, 0},
        {1, 0, 1, 0, 0},
        {0, 1, 0, 1, 1},
        {1, 0, 1, 0, 1},
        {0, 0, 1, 1, 0}
    };
    AdjGraph *G;
    createGraph(G, A, n, e);
    printf("邻接表 G:\n");
    dispGraph(G);

    // 初始化全局变量visited
    for (int i = 0; i < G->n; i++) {
        visited[i] = 0;
    }

    printf("各种遍历序列:\n");
    printf("    DFS:");
    dfs(G, 0);
    printf("\n");

    printf("    BFS:");
    bfs(G, 0);
    printf("\n");

    destroyGraph(G);

}


// 7.8 判断G是否为连通图
int connect(AdjGraph *G) {
    // 初始化visited
    for (int i = 0; i < G->n; i++) {
        visited[i] = 0;
    }
    dfs(G, 0);
    for (int i = 0; i < G->n; i++) {
        if (visited[i] == 0) {
            return 0;
        }
    }
    return 1;
}

// testConnect 测试连通图
void testConnect() {
    int n = 5;
    int e = 6;
    int A[MAXVEX][MAXVEX] = {
        {0, 1, 0, 1, 0},
        {1, 0, 1, 0, 0},
        {0, 1, 0, 1, 1},
        {1, 0, 1, 0, 1},
        {0, 0, 1, 1, 0}
    };
    AdjGraph *G;
    createGraph(G, A, n, e);

    if (connect(G)) {
        printf("\n图G是连通图\n");
    } else {
        printf("\n图G不是连通图\n");
    }
    
    destroyGraph(G);

}

// hasAPath 按照深度优先遍历算法的思路，寻找u->v是否存在一条路径
int hasAPath(AdjGraph *G, int u, int v) {
    visited[u] = 1; // 从u开始
    ArcNode *p = G->adjlist[u].firstarc;
    int w;
    while (p != NULL) {
        // 记录相邻结点的编号
        w = p->adjvex;
        if (w == v) {
            return 1;
        }
        if (visited[w] == 0) {
            if (hasAPath(G, w, v)) { // 使用递归的方式深度遍历
                return 1;
            }
        }
        p = p->nextarc;
    }
    return 0;
}

int hashAPath1(AdjGraph *G, int u, int v) {
    if (u == v) {
        return 1;
    }
    visited[u] = 1; // 标记当前已被访问过
    ArcNode *p = G->adjlist[u].firstarc;
    int w;
    while (p != NULL) {
        w = p->adjvex;
        if (visited[w] == 0) {
            if (hashAPath1(G, w, v)) {
                return 1;
            }
        }
        p = p->nextarc;
    }
    return 0;
}


void testHasAPath() {
    int n = 5;
    int e = 5;
    for (int i = 0;i < n; i++) {
        visited[i] = 0;
    }

    int A[MAXVEX][MAXVEX] = {
        {0, 1, 0, 1, 0},
        {1, 0, 1, 0, 0},
        {0, 1, 0, 1, 1},
        {1, 0, 1, 0, 1},
        {0, 0, 1, 1, 0}
    };
    AdjGraph *G;
    createGraph(G, A, n, e);

    int u = 0;
    int v = 4;
    if (hashAPath1(G, u, v)) {
        printf("顶点%d到顶点%d有简单路径\n", u, v);
    } else {
        printf("顶点%d到顶点%d没有简单路径\n", u, v);
    }

    destroyGraph(G);
}

// findAPath 求u到v的一条简单的路径
void findAPath(AdjGraph *G, int u, int v, int path[], int d) {
    visited[u] = 1;
    d++;
    path[d] = u;
    if (u == v) {
        for (int i = 0; i <=d; i++) {
            printf("%d ", path[i]);
        }
        return;
    }
    ArcNode *p = G->adjlist[u].firstarc;
    int w;
    while (p != NULL) {
        w = p->adjvex;
        if (visited[w] == 0) {
            findAPath(G, w, v, path, d);
        }
        p = p->nextarc;
    }
}

// findAllPath 求从u->v的所有的简单路径
void findAllPath(AdjGraph *G, int u, int v, int path[], int d) {
    visited[u] = 1;
    d++;
    path[d] = u;

    // 如果找到顶点v
    if (u == v) {
        for (int i = 0;i <= d; i++) {
            printf(" %d", path[i]);
        }
        printf("\n");
        visited[v] = 0; // 从终点回溯
    } else {
        ArcNode *p = G->adjlist[u].firstarc;
        int w;
        while (p != NULL) {
            w = p->adjvex;
            if (visited[w] == 0) {
                findAllPath(G, w, v, path, d);
            }
            p = p->nextarc;
        }
        visited[u] = 0; // 从顶点u开始回溯
    }
}

void testFindAllPath() {
    int n = 5;
    int e = 5;
    for (int i = 0;i < n; i++) {
        visited[i] = 0;
    }

    int A[MAXVEX][MAXVEX] = {
        {0, 1, 0, 1, 0},
        {1, 0, 1, 0, 0},
        {0, 1, 0, 1, 1},
        {1, 0, 1, 0, 1},
        {0, 0, 1, 1, 0}
    };
    AdjGraph *G;
    createGraph(G, A, n, e);

    int u = 0;
    int v = 4;
    printf("从顶点%d到顶点%d的所有路径:\n", u, v);
    int path[MAXVEX];
    int d = -1;
    findAllPath(G, u, v, path, d);
    destroyGraph(G);
}

// shortPath 找u->v的最短路径
void shortPath(AdjGraph *G, int u, int v) {
    struct Queue {
        int data;   // 顶点编号
        int parent; // 前一个顶点编号
    } qu[MAXVEX];
    int front = -1;
    int rear = -1;

    // 访问标记设置为0
    for (int i = 0; i < G->n; i++) {
        visited[i] = 0;
    }

    rear++;
    qu[rear].data = u;
    qu[rear].parent = -1;
    visited[u] = 1;

    // 按照广度优先遍历算法
    int w;
    int i;
    ArcNode *p;
    while (front != rear) {
        // 出队列
        front++;
        w = qu[front].data;
        if (w == v) {
            // 找到则逆序输出路径
            i = front;
            while (qu[i].parent != -1) {
                printf("%d ", qu[i].data);
                i = qu[i].parent;
            }
            printf("%d\n", qu[i].data);
            break;
        }
        // 如果没有找到继续
        p = G->adjlist[w].firstarc;
        while (p != NULL) {
            if (visited[p->adjvex] == 0) {
                // 加入到队列，并标记为已访问
                visited[p->adjvex] = 1;
                rear++;
                qu[rear].data = p->adjvex;
                qu[rear].parent = front;
            }
            p = p->nextarc; // 找w的下一个相邻点
        }
    }
}

void testShortPath() {
    int n = 5, e = 6;
    int u = 0, v = 4;
    int A[MAXVEX][MAXVEX] = {
        {0, 1, 0, 1, 0},
        {1, 0, 1, 0, 0},
        {0, 1, 0, 1, 1},
        {1, 0, 1, 0, 1},
        {0, 0, 1, 1, 0}
    };
    AdjGraph *G;
    createGraph(G, A, n, e);

    printf("从顶点%d到%d的最短逆路径:", u, v);
    shortPath(G, u, v);
    destroyGraph(G);
}