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