#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXD 50

typedef int ElemType;

typedef struct rnode {
    char key[MAXD];
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
    // todo:
}

