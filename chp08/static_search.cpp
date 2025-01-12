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
