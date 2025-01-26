#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 50

typedef int KeyType;

typedef int ElemType;


typedef struct {
    KeyType key;
    ElemType data;
} SqType;


void bubbleSort(SqType R[], int n) {
    SqType tmp;
    int exchange = 0;
    for (int i = 0; i < n - 1; i++) {
        exchange = 0;
        for (int j = n - 1; j > i; j--) {
            if (R[j].key < R[j-1].key) {
                tmp = R[j];
                R[j] = R[j-1];
                R[j-1] = tmp;
                exchange = 1;
            }
        }
        if (exchange == 0) {
            return;
        }
    }
}

// quickSort 快速排序算法
void quickSort(SqType R[], int s, int t) {
    int i = s;
    int j = t;
    SqType tmp;
    // 判断s、t的关系
    if (s >= t) {
        return;
    }
    tmp = R[s];
    while (i != j) {
        // 从后往前寻找比tmp小的元素
        while (j > i && R[j].key >= tmp.key) {
            j--;
        }
        // 将R[j]移动到R[i]的位置
        if (i < j) {
            R[i] = R[j];
            i++;
        }
        // 从前往后寻找比tmp大的元素
        while ( i < j && R[i].key <= tmp.key) {
            i++;
        }
        // 将R[i]移动到R[j]的位置
        if (i < j) {
            R[j] = R[i];
            j--;
        }
    }
    // 把最终的tmp值赋值到最终位置
    R[i] = tmp;
    // 递归算法分别对左右子序列
    quickSort(R, s, i-1);
    quickSort(R, i+1, t);
}

void runBubbleSort() {
    SqType R[MAX_SIZE];
    KeyType A[] = {75, 87, 68, 92, 88, 61, 77, 96, 80, 72};
    int n = 10;
    for (int i = 0; i < n; i++) {
        R[i].key = A[i];
    }
    bubbleSort(R, n);
    printf("排序结果：");
    for (int i = 0; i < n; i++) {
        printf("%3d", R[i].key);
    }
    printf("\n");
}

void testQuickSort() {
    SqType R[MAX_SIZE];
    KeyType A[] = {75, 87, 68, 92, 88, 61, 77, 96, 80, 72};
    int n = 10;
    for (int i = 0; i < n; i++) {
        R[i].key = A[i];
    }
    bubbleSort(R, n);
    printf("排序结果：");
    for (int i = 0; i < n; i++) {
        printf("%3d", R[i].key);
    }
    printf("\n");
}