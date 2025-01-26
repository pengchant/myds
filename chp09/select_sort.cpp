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