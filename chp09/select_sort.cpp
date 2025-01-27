#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 50

typedef int KeyType;

typedef int ElemType;

typedef struct {
    KeyType key;
    ElemType data;
} SqType;


void selectSort(SqType R[], int n) {
    SqType tmp;
    int min;
    for (int i = 0; i < n - 1; i++) {
        min = i;
        for (int j = i+1; j < n; j++) {
            if (R[min].key > R[j].key) {
                min = j;
            }
        }
        if (min != i) {
            tmp = R[i];
            R[i] = R[min];
            R[min] = tmp;
        }
    }
}

void testSelectSort() {
    SqType R[MAX_SIZE];
    KeyType A[] = {75, 87, 68, 92, 88, 61, 77, 96, 80, 72};
    int n = 10;
    for (int i = 0; i < n; i++) {
        R[i].key = A[i];
    }
    // do select sort
    selectSort(R, n);
    printf("选择排序结果：");
    for (int i = 0; i < n; i++) {
        printf("%3d", R[i].key);
    }
    printf("\n");
}


// sift 以R[low]为根结点的左右子树均为堆的调整算法
void sift(SqType R[], int low, int high) {
    int i = low;
    int j = 2 * i; // j 为i的左孩子
    SqType tmp = R[i];
    while (j <= high) {
        // 右孩子大，j重新指向
        if (j < high && R[j].key < R[j+1].key) {
            j++;
        }
        // 判断根结点的大小,如果比最大值都大则直接添加
        if (tmp.key >= R[j].key) {
            break;
        }
        R[i] = R[j]; // R[j]调整到双亲结点上
        i = j; // i 重新指向当前节点
        j = 2 * i; // j指向左孩子
    }
    R[i] = tmp; // 被筛选出来的结点放入最终的位置
}

// heapSort 堆排序
void heapSort(SqType R[], int n) {
    // 建立初始大根堆，从最后一个分支结点开始
    for (int i = n/2; i >= 1; i--) {
        sift(R, i, n);
    }
    // 进行n-1次循环，每次循环结束后把最大的元素R[1]和R[i]替换
    SqType tmp;
    for (int i = n; i >= 2; i--) {
        tmp = R[1]; // R[1]为最大元素,R[1]和R[i]交换,第i位置上即位最终值
        R[1] = R[i];
        R[i] = tmp;
        sift(R, 1, i - 1); // R[1..i-1]重新建立大根堆
    }
}

void testHeapSort() {
    SqType R[MAX_SIZE];
    KeyType A[] = {75, 87, 68, 92, 88, 61, 77, 96, 80, 72};
    int n = 10;
    for (int i = 0; i < n; i++) { // 这里R从下标1开始
        R[i+1].key = A[i];
    }
    printf("排序前: ");
    for (int i = 1; i <= n; i++) {
        printf("%3d", R[i].key);
    }
    printf("\n");
    heapSort(R, n);
    printf("排序后: ");
    for (int i = 1; i <= n; i++) {
        printf("%3d", R[i].key);
    }
    printf("\n");
}