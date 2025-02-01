#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXD 50
#define MAXR 10

typedef int ElemType;

typedef struct rnode {
    char key[MAXD]; // 关键字
    ElemType data;
    struct rnode *next;
} RadixNode;

// createSLink 创建不带头结点的单链表
void createSLink(RadixNode *&h, char *A[], int n) {
    h = (RadixNode *) malloc(sizeof(RadixNode));
    strcpy(h->key, A[0]);
    RadixNode *tc = h;
    RadixNode *p;
    for (int i = 1; i < n; i++) {
        p = (RadixNode *) malloc(sizeof(RadixNode));
        strcpy(p->key, A[i]);
        tc->next = p;
        tc = p;
    }
    tc->next = NULL;
}

//destroySLink 销毁不带头结点
void destroySLink(RadixNode *&h) {
    RadixNode *pre = h;
    RadixNode *p = pre->next;
    while (p != NULL) {
        free(pre);
        pre = p;
        p = p->next;
    }
    free(pre);
}

// dispLink 打印列表
void dispLink(RadixNode *h) {
    RadixNode *p = h;
    while (p != NULL) {
        printf("%s ", p->key);
        p = p->next;
    }
    printf("\n");
}

// radixSort 基数排序,h待排序数列单链表指针
// r为基数,d为关键字位数
void radixSort(RadixNode *&h, int d, int r) {
    RadixNode *head[MAXR];
    RadixNode *tail[MAXR];
    RadixNode *p;
    RadixNode *tc;
    int k;
    // 从高位到低位循环
    for (int i = d - 1; i >= 0; i--) {
        for (int j = 0; j < r; j++) {
            head[j] = tail[j] = NULL; // 初始化各链队首、尾指针
        }

        // 分配操作
        p = h;
        while (p != NULL) {
            k = p->key[i] - '0'; // 找第k个链队
            if (head[k] == NULL) {
                head[k] = tail[k] = p;
            } else {
                tail[k]->next = p;
                tail[k] = p;
            }
            p = p->next;
        }

        // 收集操作
        h = NULL;
        for (int j = 0; j < r; j++) {
            if (head[j] != NULL) {
                if (h == NULL) {
                    h = head[j];
                    tc = tail[j];
                } else {
                    tc->next = head[j];
                    tc = tail[j];
                }
            }
        }
        tc->next = NULL;
        printf("i=%d排序的结果：", i);
        dispLink(h);
    }
}

void testRadixSort() {
    char *A[] = {"75", "87", "68", "92", "88", "61", "77", "96", "80", "72"};
    int n = 10;
    RadixNode *h;
    createSLink(h, A, n);
    printf("初始队列:   ");
    dispLink(h);
    radixSort(h, 2, 10);
    printf("排序结果：  ");
    dispLink(h);
    destroySLink(h);
}