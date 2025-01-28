#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 50

typedef int KeyType;

typedef int ElemType;


typedef struct {
    KeyType key;
    ElemType data;
} SqType;

// merge 有序列表合并
void merge(SqType R[], int low, int mid, int high) {
    int i = low;
    int j = mid + 1;
    int k = 0; // k 为R1的下标
    SqType *R1 = (SqType *) malloc((high - low + 1) * sizeof(SqType));
    while (i <= mid && j <= high) {
        if (R[i].key <= R[j].key) {
            R1[k] = R[i];
            i++;
            k++;
        } else {
            R1[k] = R[j];
            j++;
            k++;
        }
    }
    while (i <= mid) {
        R1[k] = R[i];
        i++;
        k++;
    }
    while (j <= high) {
        R1[k] = R[j];
        j++;
        k++;
    }
    for (k = 0, i = low; i <= high; k++, i++) {
        R[i] = R1[k];
    }
    free(R1);
}

void mergePass(SqType R[], int length, int n) {
    int i;
    for (i = 0; i + 2 * length - 1 < n; i = i + 2 * length) {
        merge(R, i, i + length - 1, i + 2 * length - 1);
    }
    if (i + length - 1 < n) {
        merge(R, i, i + length - 1, n - 1);
    }
}

void mergeSort(SqType R[], int n) {
    for (int length = 1; length < n; length = 2 * length) {
        mergePass(R, length, n);
    }
}

void testMergeSort() {
    SqType R[MAX_SIZE];
    KeyType A[] = {75, 87, 68, 92, 88, 61, 77, 96, 80, 72};
    int n = 10;
    for (int i = 0; i < n; i++) {
        R[i].key = A[i];
    }
    mergeSort(R, n);
    printf("操作结果:");
    for (int i = 0; i < n; i++) {
        printf("%3d", R[i].key);
    }
    printf("\n");
}