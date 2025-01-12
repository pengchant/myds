#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 40

// KeyType 关键字的数据类型
typedef int KeyType;

// SqType 学生成绩表数据类型
typedef struct {
    int no;
    char name[10];
    int score;
} SqType;

// IdxType 索引元素
typedef struct {
    KeyType key; // 存放关键字
    int pos; // 存放当前关键字在主元素表中的物理序号
} IdxType;


// binSearch 二分查找法
int binSearch(IdxType I[], int n, KeyType k) {
    int low = 0;
    int high = n - 1;
    int mid;
    while (low <= high) {
        mid = (low + high) / 2;
        if (I[mid].key == k) {
            return mid + 1;
        } else if (I[mid].key > k) {
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }
    return 0;
}

int idxSearch(SqType R[], IdxType I[], int n, KeyType k) {
    int i = binSearch(I, n, k);
    if (i > 0) {
        return I[i-1].pos + 1;
    }
    return 0;
}


void runIdxSearch() {
    int n = 5;
    KeyType k = 201204;
    // 建立主数据库表
    SqType R[MAX_SIZE] = {
        {201201, "王实", 85}, // 0
        {201205, "李斌", 82}, // 1
        {202606, "刘英", 92}, // 2
        {201202, "张三", 78}, // 3
        {201304, "陈功", 90}  // 4
    };
    // 建立索引表
    IdxType I[MAX_SIZE] = {
        {201201, 0},
        {201202, 3},
        {201204, 4},
        {201205, 1},
        {202206, 2}
    };
    int i = idxSearch(R, I, n, k);
    if (i > 0) {
        printf("关键字为%d的元素的逻辑序号为:%d\n", k, i);
    } else {
        printf("没有找到关键字为%d的元素\n", k);
    }
}

