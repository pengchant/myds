#include <stdio.h>

// 顺序表的定义
#define MAX_SIZE 100

typedef int ElemType;
typedef struct {
    ElemType data[MAX_SIZE];
    int length;
} SqList;


// 线性表基本运算在顺序表上的实现
void initList(SqList &L) {
    L.length = 0;
}

void destroyList(SqList L) {}

int getLength(SqList L) {
    return L.length;
}

int getElem(SqList L, int i, ElemType &e) {
    if (i < 1 || i > L.length) {
        return 0;
    } else {
        e = L.data[i-1];
        return 1;
    }
}

int locate(SqList L, ElemType x) {
    int i = 0;
    while (i < L.length && L.data[i] != x) {
        i++;
    }
    if (i >= L.length) {
        return 0;
    }
    return i+1;
}

int insElem(SqList &L, ElemType x, int i) {
    if (i < 1 || i > L.length + 1 || L.length == MAX_SIZE) {
        return 0;
    }
    for (int j = L.length; j >= i; j--) {
        L.data[j] = L.data[j-1];
    }
    L.data[i-1] = x;
    L.length++;
    return 1; // 插入成功
}


int delElem(SqList &L, int i) {
    if (i < 1 || i > L.length) {
        return 0;
    }
    for (int j = i; j < L.length; j++) {
        L.data[j-1] = L.data[j];
    }
    L.length--;
    return 1;
}

void dispList(SqList L) {
    for (int i = 0; i < L.length; i++) {
        printf("%d ", L.data[i]);
    }
    printf("\n");
}


void createList(SqList &L, ElemType a[], int n) {
    int k = 0;
    for (int i = 0; i < n; i++) {
        L.data[k] = a[i];
        k++;
    }
    L.length = k;
}

void swap(ElemType &x, ElemType &y) {
    ElemType tmp = x;
    x = y;
    y = tmp;
}

void swapMaxMin(SqList &L) {
    int i, maxi, mini;
    maxi = mini = 0;
    for (i = 0; i < L.length; i++) {
        if (L.data[i] > L.data[maxi]) {
            maxi = i;
        } else if (L.data[i] < L.data[mini]) {
            mini = i;
        }
    }
    swap(L.data[mini], L.data[mini]);
}

int deleteK(SqList &L, int i, int k) {
    // 0, ..., (i-1, ..., i+k-2), i+k-1, ... , n-1
    if (i < 1 || k < 1 || i+k-1 > L.length) {
        return 0; // 检测参数是否合法
    }
    for (int j = i + k -1; j < L.length; j++) {
        L.data[j-k] = L.data[j];
    }
    L.length -= k;
    return 1;
}

void move(SqList &L) {
    int i = 0, j = L.length - 1;
    while (i < j) {
        while (L.data[i] % 2 == 1) {
            i++;
        }
        while (L.data[j] % 2 == 0) {
            j--;
        }
        if (i < j) {
            swap(L.data[i], L.data[j]);
        }
    }
}

void deleteX(SqList &L, ElemType x) {
    int k = 0;
    for(int i = 0; i < L.length; i++) {
        if (L.data[i] != x) {
            L.data[k] = L.data[i];
            k++;
        }
    }
    L.length = k;
}

void deleteMinus(SqList &L) {
    int k = 0;
    for (int i = 0; i < L.length; i++) {
        if (L.data[i] >= 0) {
            L.data[k] = L.data[i];
            k++;
        }
    }
    L.length = k;
}

void merge(SqList A, SqList B, SqList &C) {
    int k = 0;
    int i = 0, j = 0;
    while (i < A.length && j < B.length) {
        if (A.data[i] <= B.data[j]) {
            C.data[k++] = A.data[i++];
        } else {
            C.data[k++] = B.data[j++];
        }
    }
    while (i < A.length) {
        C.data[k++] = A.data[i++];
    }
    while (j < B.length) {
        C.data[j++] = B.data[j++];
    }
    C.length = k;
}

void commonElem(SqList A, SqList B, SqList &C) {
    int k = 0;
    int i = 0, j = 0;
    while (i < A.length && j < B.length) {
        if (A.data[i] < B.data[j]) {
            i++;
        } else if (A.data[i] > B.data[j]) {
            j++;
        } else {
            C.data[k] = A.data[i];
            k++;
            i++;
            j++;
        }
    }
    C.length = k;
}

int topK1(SqList A, SqList B, int k, ElemType &e) {
    int i = 0, j = 0;
    if (k < 1 || k > A.length + B.length) {
        return 0;
    }
    while (i < A.length && j < B.length) {
        k--;
        if (A.data[i] < B.data[j]) {
            if (k == 0) {
                e = A.data[i];
                return 1;
            }
            i++;
        } else {
            if (k == 0) {
                e = B.data[i];
            }
            j++;
        }
    }
    if (i < A.length) {
        e = A.data[i+k-1];
    }
    if (j < B.length) {
        e = B.data[j+k-1];
    }
    return 1;
}


void sqlistTest() {
    int i;
    ElemType e;
    SqList L;

    initList(L);      // 定义一个初始化列表
    insElem(L, 1, 1); // 插入元素
    insElem(L, 3, 2);
    insElem(L, 1, 3);
    insElem(L, 5, 4);
    insElem(L, 4, 5);
    insElem(L, 2, 6);

    printf("线性表:");
    dispList(L);
    printf("长度: %d\n", L.length);

    move(L);
   
    // 获取线性表
    printf("线性表:\n");
    dispList(L);
}