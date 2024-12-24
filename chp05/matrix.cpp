#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 10
#define M 6
#define N 7

typedef int ElemType;

typedef struct {
    int r;  // 行号
    int c;  // 列号
    ElemType d; // 元素值为ElemType的类型
} TupNode;

typedef struct {
    int rows;   // 行数
    int cols;   // 列数
    int nums;   // 非零元素个数
    TupNode data[MAX_SIZE];
} TSMatrix;


// createMat 从一个二维稀疏矩阵创建三元组表示
void createMat(TSMatrix &t, ElemType A[M][N]) {
    int i, j;
    t.rows = M;
    t.cols = N;
    t.nums = 0;
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            if (A[i][j] != 0) {
                t.data[t.nums].r = i;
                t.data[t.nums].c = j;
                t.data[t.nums].d = A[i][j];
                t.nums++; // 计数累加
            }
        }
    }
}

// value 设置矩阵i,j位置值为x
int value(TSMatrix &t, ElemType x, int i, int j) {
    int k = 0;
    if (i >= t.rows || j >= t.cols) {
        return 0;
    }
    while (k < t.nums && t.data[k].r) {
        k++;
    }
    while (k < t.nums && i == t.data[k].r && j > t.data[k].c) {
        k++;
    }
    if (k < t.nums && t.data[k].r == i && t.data[k].c == j) {
        t.data[k].d = x;
        return 1;
    } 
    for (int k1 = t.nums - 1; k1 >= k; k1--) {
        t.data[k1+1].r = t.data[k1].r;
        t.data[k1+1].c = t.data[k1].c;
        t.data[k1+1].d = t.data[k1].d;
    }
    t.data[k].r = i;
    t.data[k].c = j;
    t.data[k].d = x;
    t.nums++;
    return 1;

}


// assign 将指定位置元素值赋值给变量
int assign(TSMatrix t, ElemType &x, int i, int j) {
    if (i >= t.rows || j >= t.cols) {
        return 0;
    }
    int k = 0;
    while (k < t.nums && i > t.data[k].r) {
        k++;
    }
    while (k < t.nums && t.data[k].r == i && t.data[k].c < j) {
        k++;
    }
    if (k < t.nums && t.data[k].r == i && t.data[k].c == j) {
        x = t.data[k].d;
    } else {
        x = 0;
    }
    return 1;
}

// dispMat 打印数组
void dispMat(TSMatrix t) {
    if (t.nums < 0) {
        return;
    }
    printf("\t%d\t%d\t%d\n", t.rows, t.cols, t.nums);
    printf("\t---------------------\n");
    for (int i = 0; i < t.nums; i++) {
        printf("\t%d\t%d\t%d\n", t.data[i].r, t.data[i].c, t.data[i].d);
    }
}

void runMatrix() {
    TSMatrix t;
    ElemType x;
    ElemType a[M][N] = {
        {0,0,1,0,0,0,0},
        {0,2,0,0,0,0,0},
        {3,0,0,0,0,0,0},
        {0,0,0,5,0,0,0},
        {0,0,0,0,6,0,0},
        {0,0,0,0,0,7,4},
    };
    createMat(t, a);
    printf("三元组t表示:\n");
    dispMat(t);

    printf("执行A[4][1]=8\n");
    value(t, 8, 4, 1);

    printf("三元组t表示:\n");
    dispMat(t);

    printf("求x=A[4][1]\n");
    assign(t, x, 4, 1);
    printf("x=%d\n", x);

}