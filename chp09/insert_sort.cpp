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

void runInsertSort() {
    SqType R[MAX_SIZE];
    KeyType A[] = {75, 87, 68, 92, 88, 61, 77, 96, 80, 72};
    int n = 10;
    for (int i = 0; i < n; i++) {
        R[i].key = A[i];
    }
    insertSort(R, n);
    printf("操作结果:");
    for (int i = 0; i < n; i++) {
        printf("%3d", R[i].key);
    }
    printf("\n");
}
