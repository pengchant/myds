#include <stdio.h>

// 关键字数据类型
typedef int KeyType;

// 元素类型
typedef int ElemType;

typedef struct {
    KeyType key; // 存放关键字 
    ElemType data; // 存放具体的数据
} SqType;

// sqSearch 顺序查找算法
int sqSearch(SqType R[], int n, KeyType k) {
    int i;
    while (i < n && R[i].key != k) {
        i++;
    }
    if (i >= n) {
        return 0;
    }
    return i+1;
}

// binSearch 二分查找法
int binSearch(SqType R[], int n, KeyType k) {
    int low = -1;
    int high = n - 1;
    int mid;
    while (low <= high) {
        mid = (low + high) / 2;
        if (R[mid].key == k) {
            return mid + 1;
        } else if (R[mid].key < k) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return 0;
}