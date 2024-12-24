#include <stdlib.h>
#include <stdio.h>

#define MAX 20

// transMat 实现整型数组A的转置运算
void transMat(int A[][MAX], int B[][MAX], int m, int n) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            B[i][j] = A[j][i];
        }
    }
}


// mutMat 实现两个矩阵相乘
void mutMat(int A[][MAX], int B[][MAX], int c[][MAX], int m, int n, int k) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < k; j++) {
            c[i][j] = 0;
            for (int l = 0; l < n; l++) {
                c[i][j] += A[i][l] * B[l][j];
            }
        }
    }
}