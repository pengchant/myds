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

// -------------- 图的深度遍历算法 ------------
int visited[MAXVEX] = {0};

void dfs1(MatGraph g, int v) {
    printf("%d ", v);
    visited[v] = 1;
    int val;
    for (int w = 0; w < g.n; w++) {
        val = g.edges[v][w];
        if (val != 0 && val != INF && visited[w] == 0) {
            dfs1(g, w);
        }
    }
}



void bfs1(MatGraph g, int v) {
    // 定义visited已访问列表数组
    int visited[MAXVEX];
    for (int i = 0; i < g.n; i++) {
        visited[i] = 0;
    }

    // 定义一个循环队列
    int Qu[MAXVEX];
    int front = 0, rear = 0;

    // 访问当前结点
    printf("%d ", v);
    visited[v] = 1;
    rear = (rear + 1) % MAXVEX;
    Qu[rear] = v;

    // 队列不为空时循环
    int w = 0;
    int val = 0;
    while (front != rear) {
        // 队列中弹出首元素
        front = (front + 1) % MAXVEX;
        w = Qu[front];
        for (int i = 0; i < g.n; i++) {
            val = g.edges[w][i];
            if (val != 0 && val != INF && visited[i] == 0) {
                // 访问元素并标记
                printf("%d ", i);
                visited[i] = 1;

                // 把当前结点加入队列
                rear = (rear + 1) % MAXVEX;
                Qu[rear] = i;
            }
        }
    }
}


// prim 最小生成树算法
void prim(MatGraph g, int v) {
    int lowcost[MAXVEX]; // 建立数组lowcost
    int closest[MAXVEX]; // 建立数组closest
    for (int i = 0; i < g.n; i++) {
        closest[i] = v; // v -> i
        lowcost[i] = g.edges[v][i]; // v -> i 权值
    }
    int min;
    int k;
    // 构造n-1条边
    for (int i = 1; i < g.n; i++) {
        min = INF;
        // 从V-U 中选择距离U最近的点k
        for (int j = 0; j < g.n; j++) {
            if (lowcost[j] != 0 && lowcost[j] < min) {
                k = j; // 记录下最短边的顶点(i -> j)
                min = lowcost[j]; // min是权值
            }
        }
        // 把最小边打印处理
        printf("    边(%d,%d),权值为%d\n", closest[k], k, min);
        lowcost[k] = 0; // 把顶点k加入到U集合
        // 修正数组lowcost 和 closest, k -> j (j要在候选集合中) 的最短路径
        for (int j = 0; j < g.n; j++) {
            if (lowcost[j] != 0 && g.edges[k][j] < lowcost[j]) {
                closest[j] = k; // K -> j
                lowcost[j] = g.edges[k][j]; // k 到 j的最短路径
            }
        }
    }
}

// -------------------- kruskal算法 ----------------------

// Edge 定义边的类型
typedef struct {
    int u; // 边的起始顶点
    int v; // 边的终止顶点
    int w; // 边的权值
} Edge;


// sortEdge 采用直接插入排序方法进行排序
void sortEdge(Edge E[], int e) {
    Edge temp;
    int j;
    for (int i = 1; i < e; i++) {
        temp = E[i];
        j = i - 1;
        while (j >= 0 && temp.w < E[j].w) {
            E[j] = E[j-1];
            j--;
        }
        E[j+1] = temp;
    }
}

// kruskal 输出求得最小生成树的所有边
void kruskal(MatGraph g) {
    int k = 0; // 累加所有的边数
    int vset[MAXVEX]; // 建立数组vset
    Edge E[MAXVEX]; // 建立存放所有边的数组E
    for (int i = 0; i < g.n; i++) {
        for (int j = 0; j <= i; j++) { // 无向图只提取主对角+下三角部分元素
            if (g.edges[i][j] != 0 && g.edges[i][j] != INF) {
                E[k].u = i; // 起始结点
                E[k].v = j; // 终止结点
                E[k].w = g.edges[i][j]; // 边的权重
                k++; // 累加边数
            }
        }
    }

    // 边权重排序
    sortEdge(E, k);

    // 初始化辅助数组vset
    for (int i = 0; i < g.n; i++) {
        vset[i] = i;
    }

    // k表示构造当前生成树的第几条边
    k = 1;
    int j = 0; // j为数组E的下标
    int u1, v1; // 遍历过程中u1,v1,起始,结束结点编号
    int sn1, sn2; // u1和v1的所在连通图编号标记

    // 生成n-1条边
    while (k < g.n) {
        u1 = E[j].u; // 起始位置
        v1 = E[j].v; // 终止结点
        sn1 = vset[u1]; // 联通图标记1
        sn2 = vset[v1]; // 连通图标记2
        if (sn1 != sn2) {
            printf("    边(%d,%d),权值为%d\n", u1, v1, E[j].w);
            k++; // 生成边数累加
            for (int i = 0; i < g.n; i++) {
                if (vset[i] == sn2) {
                    vset[i] = sn1;
                }
            }
        }
        j++; // 扫描下一条边
    }
}


void testKruskal() {
    MatGraph g;
    int n = 5;
    int e = 8;
    int A[MAXVEX][MAXVEX] = {
        {0, 1, 3, 4, 7},
        {1, 0, 2, INF, INF},
        {3, 2, 0, 5, 8},
        {4, INF, 5, 0, 6},
        {7,INF, 8, 6, 0},
    };
    createGraph(g, A, n, e);

    printf("图G的存储结构:\n");
    dispGraph(g);

    printf("Prim: 从顶点0出发构造最小生成树:\n");
    prim(g, 0);

    printf("Kruskal: 构造的最小生成树:\n");
    kruskal(g);

    destroyGraph(g);
}

