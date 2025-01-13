#include <stdio.h>
#include <stdlib.h>

typedef int KeyType;

typedef int ElemType;

typedef struct {
    KeyType key; // 块关键字
    int low; // 块最低索引
    int high; // 块最高索引
} IdxType;

typedef struct {
    KeyType key; // 存放关键字 
    ElemType data; // 存放具体的数据
} SqType;

// blkSearch 分块查找
int blkSearch(SqType R[], int n, IdxType I[], int b, KeyType k) {
    int low = 0;
    int high = b - 1;
    int mid;
    int s = (n + b - 1) / b;
    printf("s=%d\n", s);
    while (low <= high) {
        mid = (low + high) / 2;
        if (I[mid].key >= k) {
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }
    int i = I[high+1].low;
    while (i <= I[high+1].high && R[i].key != k) {
        i++;
    }
    if (i <= I[high+1].high) {
        return i + 1;
    } else {
        return 0;
    }
}