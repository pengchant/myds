#include <stdlib.h>
#include <stdio.h>

// func 求a的i个元素之和递归算法实现
int func(int a[], int i) {
    if (i == 1) {
        return a[0];
    }
    return a[i] + func(a, i -1);
}


typedef struct node {
    int data;
    node *next;
} SLinkNode;

// f1 求最大结点的值
int f1(SLinkNode *L) {
    if (L->next == NULL) {
        return L->data;
    }
    int m = f1(L->next);
    return m > L->data ? m : L->data;
}

// f2 求最小结点值
int f2(SLinkNode *L) {
    if (L->next == NULL) {
        return L->data;
    }
    int m = f2(L->next);
    return m < L->data ? m : L->data;
}

// f3 正向打印输出所有节点的值
void f3(SLinkNode *L) {
    if (L != NULL) {
        printf("%d ", L->data);
        f3(L->next);
    }
}

// f4 逆向打印输出所有节点的值
void f4(SLinkNode *L) {
    if (L != NULL) {
        f4(L->next);
        printf("%d ", L->data);
    }
}