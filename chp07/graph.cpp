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


// -------------------- dijkstra 算法 ----------------------
void dispAllPath(MatGraph g, int dist[], int path[], int S[], int v) {
    int d; // 路径长度
    int k; // 前一个结点编号
    int apath[MAXVEX]; // 所有路径
    for (int i = 0; i < g.n; i++) {
        if (S[i] == 0 || i == v) {
            continue;
        }
        printf("    从%d到%d最短路径长度为:%d\t路径:", v, i, dist[i]);
        d = 0;
        apath[d] = i;
        k = path[i]; // 求当前结点 前一个 顶点 k
        if (k == -1) {
            printf("无路径\n");
            continue;
        }
        while (k != v) {
            d++; // 累加路径结点数
            apath[d] = k; // apath数组中保存路径编号
            k = path[k]; // 往前递推路径编号 
        }
        d++;
        apath[d] = v;

        // 逆向输出路径
        printf("%d", apath[d]); // 先输出起点 
        for (int j = d-1; j >= 0; j--) {
            printf("->%d", apath[j]);
        }
        printf("\n");
    }
}

void dijkstra(MatGraph g, int v) {
    int dist[MAXVEX];
    int path[MAXVEX];
    int S[MAXVEX]; // 结果集合
    // 初始化dist path 数组
    for (int i = 0; i < g.n; i++) {
        dist[i] = g.edges[v][i];
        S[i] = 0;
        if (g.edges[v][i] < INF) {
            path[i] = v;
        } else {
            path[i] = -1;
        }
    }
    // 开始算法过程
    S[v] = 1; // 源点v放入S集合中
    int mindis; // 保存最短路径局部变量
    int u; // 保存路径最短的顶点编号
    for (int i = 0; i < g.n - 1; i++) {
        // 先从U中找距离最短的一个顶点
        mindis = INF;
        for (int j = 0; j < g.n; j++) {
            if (S[j] == 0 && dist[j] < mindis) {
                u = j;
                mindis = dist[j];
            }
        }
        // 将顶点放入S集合中
        printf("将顶点%d加入S中\n", u);
        S[u] = 1;
        // 修改U集合中的距离，考虑从u->U集合中其余顶点的距离值
        for (int j = 0; j < g.n; j++) {
            if (S[j] == 0) {
                if (g.edges[u][j] < INF && dist[u] + g.edges[u][j] < dist[j]) {
                    dist[j] = dist[u] + g.edges[u][j];
                    path[j] = u;
                }
            }
        }
    }
    // 最后一步输出路径
    dispAllPath(g, dist, path, S, v);
}



void runDijkstra() {
    MatGraph g;
    int n = 7;
    int e = 12;
    int A[MAXVEX][MAXVEX] = {
        {0, 4, 6, 6, INF, INF, INF},
        {INF, 0, 1, INF, 7, INF, INF},
        {INF, INF, 0, INF, 6, 4, INF},
        {INF, INF, 2, 0, INF, 5, INF},
        {INF, INF, INF, 0, INF, 6},
        {INF, INF, INF, INF, 1, 0, 8},
        {INF, INF, INF, INF, INF ,INF, 0}
    };
    createGraph(g, A, n, e);

    printf("图G的存储结构:\n");
    dispGraph(g);

    dijkstra(g, 0);

    destroyGraph(g);
}


// ---------------- floyd 多源最短路径算法 ----------------

// dispAllPath 输出最短路径
void dispAllPath(MatGraph g, int A[][MAXVEX], int path[][MAXVEX]) {
    int apath[MAXVEX];
    for (int i = 0; i < g.n; i++) {
        for (int j = 0; j < g.n; j++) {
            if (i == j || A[i][j] == INF) {
                continue;
            }
            printf("    顶点%d到顶点%d的最短路径长度:%d\t路径:", i, j, A[i][j]);
            // 输出路径
            int k = path[i][j]; // 追溯法
            int d = 0; // 路径计数
            apath[d] = j; // 终点j
            while (k != -1 && k != i) {
                d++;
                apath[d] = k;
                k = path[i][k];
            }
            d++; // 起始结点
            apath[d] = i; // 起始结点
            printf("%d", apath[d]); // 输出起点
            // 逆序输出
            for (int s = d-1; s >= 0; s--) {
                printf("->%d", apath[s]);
            }
            printf("\n");
        }
    }
}

void floyd(MatGraph g) {
    int A[MAXVEX][MAXVEX];
    int path[MAXVEX][MAXVEX]; 
    // 初始化path数组
    for (int i = 0; i < g.n; i++) {
        for (int j = 0; j < g.n; j++) {
            A[i][j] = g.edges[i][j];
            if (i != j && g.edges[i][j] < INF) {
                path[i][j] = i; // i -> j 前一个顶点i
            } else {
                path[i][j] = -1; // 无边
            }
        }
    }
    // 求Ak
    for (int k = 0; k < g.n; k++) {
        for (int i = 0; i < g.n; i++) {
            for (int j = 0; j < g.n; j++) {
                // 找到更短的路径
                if (A[i][j] > A[i][k] + A[k][j]) {
                    A[i][j] = A[i][k] + A[k][j];
                    path[i][j] = path[k][j]; // 最短路径改为经过点k
                }
            }
        }
    }
    // 输出路径
    dispAllPath(g, A, path);
}

void runFloyd() {
    MatGraph g;
    int n = 6;
    int e = 11;
    int v = 2;
    int A[][MAXVEX] = {
        {0, 50, 10, INF, INF, INF},
        {INF, 0, 15, 50, 10, INF},
        {20, INF, 0, 15, INF, INF},
        {INF, 20, INF, 0, 35, INF},
        {INF, INF, INF, 30, 0, INF},
        {INF, INF, INF, 3, INF, 0},
    };
    createGraph(g, A, n, e); // 创建图
    printf("Dijkstra求解结果如下:\n");
    dijkstra(g, v);
    printf("\nFloyd求解结果如下:\n");
    floyd(g);
    destroyGraph(g);
}

// --------------------- floyd 算法应用 ---------------------

void floyd1(MatGraph g, int A[][MAXVEX]) {
    // 初始化A数组
    for (int i = 0; i < g.n; i++) {
        for (int j = 0; j < g.n; j++) {
            A[i][j] = g.edges[i][j];
        }
    }
    // 动态规划
    for (int k = 0; k < g.n; k++) {
        for (int i = 0; i < g.n; i++) {
            for (int j = 0; j < g.n; j++) {
                if (A[i][j] > A[i][k] + A[k][j]) {
                    A[i][j] = A[i][k] + A[k][j]; // 修改路径长度
                }
            }
        }
    }
}

// findVex 查找最佳村庄的编号
int findVex(int A[][MAXVEX], int n) {
    int B[MAXVEX];
    for (int i = 0; i < n; i++) {
        B[i] = 0;
        for (int j = 0; j < n; j++) {
            B[i] += A[i][j];
        }
    }
    int minv = 0;
    for (int i = 1; i < n; i++) {
        if (B[i] < B[minv]) {
            minv = i;
        }
    }
    return minv;
}

void runFindVex() {
    MatGraph g;
    int A[MAXVEX][MAXVEX];
    int n = 5;
    int e = 6;
    int B[MAXVEX][MAXVEX] = {
        {0, 12, 9, INF, 3},
        {12, 0, 6, INF, INF},
        {9, 6, 0, 4, INF},
        {INF, INF, 4, 0, 6},
        {3, INF, INF, 6, 0}
    };
    createGraph(g, B, n, e); // 创建图
    printf("图G的存储结构:\n");
    dispGraph(g);
    floyd1(g, A);
    printf("最佳村庄编号:%d\n", findVex(A, n));
}