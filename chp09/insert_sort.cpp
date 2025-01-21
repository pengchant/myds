#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 50

typedef int KeyType;

typedef int ElemType;


typedef struct {
    KeyType key;
    ElemType data;
} SqType;


// insertSort 直接插入排序
void insertSort(SqType R[], int n) {
    SqType tmp;
    int j;
    for (int i = 1; i < n; i++) {
        if (R[i-1].key <= R[i].key) {
            continue;
        }
        tmp = R[i];
        j = i-1;
        // 有序区中必当前元素大的统一往后移
        while (j >= 0 && R[j].key > tmp.key) {
            R[j+1] = R[j];
            j--;
        }
        R[j+1] = tmp; // 插入到对应位置
    }
}


// 折半插入排序
void binInsertSort(SqType R[], int n) {
    SqType tmp;
    int low, high, mid;
    for (int i = 1; i < n; i++) {
        if (R[i-1].key > R[i].key) {
            tmp = R[i];
            low = 0;
            high = i - 1;
            // 使用二分查找法找到位置
            while (low <= high) {
                mid = (low + high) / 2;
                if (tmp.key < R[mid].key) {
                    high = mid - 1;
                } else {
                    low = mid + 1;
                }
            }
            // 元素统一后移
            for (int j = i - 1; j >= high + 1; j--) {
                R[j+1] = R[j];
            }
            R[high+1] = tmp; // 插入原来的R[j]
        }
    }
}


void shellSort(SqType R[], int n) {
    SqType tmp;
    int d = n / 2;
    while (d > 0) {
        // 第n趟排序，分组大小为d
        for (int i = d; i < n; i++) {
            tmp = R[i];
            int j = i - d; // 插入排序法第一个元素
            while (j >= 0 && tmp.key < R[j].key) { // 有序部分统一往后挪d个位置
                R[j+d] = R[j];
                j = j - d;
            }
            R[j+d] = tmp;
        }
        d = d / 2;
    }
}

void runInsertSort() {
    SqType R[MAX_SIZE];
    KeyType A[] = {75, 87, 68, 92, 88, 61, 77, 96, 80, 72};
    int n = 10;
    for (int i = 0; i < n; i++) {
        R[i].key = A[i];
    }
    // insertSort(R, n);
    // binInsertSort(R, n);
    shellSort(R, n);

    printf("操作结果:");
    for (int i = 0; i < n; i++) {
        printf("%3d", R[i].key);
    }
    printf("\n");
}

