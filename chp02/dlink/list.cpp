#include <stdio.h>
#include <stdlib.h>


typedef int ElemType;

typedef struct node {
    ElemType data;
    struct node *prior, *next;
} DLinkNode;


void initList(DLinkNode * &L) {
    L = (DLinkNode *) malloc(sizeof(DLinkNode));
    L->prior = L->next = NULL;
}


void destroyList(DLinkNode * &L) {
    DLinkNode *pre = L;
    DLinkNode *p = pre->next;
    while (p != NULL) {
        free(pre);
        pre = p;
        p = p->next;
    }
    free(pre);
}


int getLength(DLinkNode *L) {
    int i = 0;
    DLinkNode *p = L->next;
    while (p != NULL) {
        i++;
        p = p->next;
    }
    return i;
}


int getElem(DLinkNode *L, int i, ElemType &e) {
    int j = 0;
    DLinkNode *p = L;
    if (i <= 0) {
        return 0;
    }
    while (p != NULL && j < i) {
        p = p->next;
        j++;
    }
    if (p == NULL) {
        return 0;
    }
    e = p->data;
    return 1;
}


int locate(DLinkNode *L, ElemType e) {
    DLinkNode *p = L->next;
    int i = 1;
    while (p != NULL && p->data != e) {
        p = p->next;
        i++;
    }
    if (p == NULL) {
        return 0;
    }
    return i;
}


int insElem(DLinkNode * &L, ElemType x, int i) {
    int j = 0;
    DLinkNode *p = L;
    DLinkNode *s; // 新增节点
    if (i <= 0) {
        return 0;
    }
    while (p != NULL && j < i-1) {
        p = p->next;
        j++;
    }
    if (p == NULL) {
        return 0;
    }
    s = (DLinkNode *) malloc(sizeof(DLinkNode));
    s->data = x;
    s->next = p->next;
    if (p->next != NULL) {
        p->next->prior = s;
    }
    s->prior = p;
    p->next = s;
    return 1;
}


int delElem(DLinkNode * &L, int i) {
    DLinkNode *p = L;
    if (i <= 0) {
        return 0;
    }
    int j = 0;
    while (p != NULL && j < i) {
        p = p->next;
        j++;
    }
    if (p == NULL) {
        return 0;
    }
    DLinkNode *pre = p->prior;
    if (p->next != NULL) {
        p->next->prior = pre;
    }
    pre->next = p->next;
    p->next = NULL;
    free(p);
    return 1;
}


void dispList(DLinkNode *L) {
    DLinkNode *p = L->next;
    while (p != NULL) {
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
}

void testRunDList() {
    int i;
    ElemType e;
    DLinkNode *L;
    initList(L);
    insElem(L, 1, 1);
    insElem(L, 3, 2);
    insElem(L, 1, 3);
    insElem(L, 5, 4);
    insElem(L, 4, 5);
    insElem(L, 2, 6);

    printf("线性表:");
    dispList(L);
    printf("长度: %d\n", getLength(L));
    i = 3;
    getElem(L, i, e);
    printf("第%d个元素:%d\n", i, e);
    e = 1;
    printf("元素%d是第%d个元素\n", e, locate(L, e));
    i = 4;
    printf("删除第%d个元素", i);
    delElem(L, i);
    printf("线性表:");
    dispList(L);
    destroyList(L);
}

void createListF(DLinkNode * &L, ElemType a[], int n) {
    DLinkNode *s;
    L = (DLinkNode *) malloc(sizeof(DLinkNode));
    L->next = NULL;
    for (int i = 0; i < n; i++) {
        s = (DLinkNode *) malloc(sizeof(DLinkNode));
        s->data = a[i];
        s->next = L->next;
        s->prior = L;
        if (L->next != NULL) {
            L->next->prior = s;
        }
        L->next = s;
    }
}

void createListR(DLinkNode * &L, ElemType a[], int n) {
    L = (DLinkNode *) malloc(sizeof(DLinkNode));
    DLinkNode *tc = L;
    DLinkNode *s;
    for (int i = 0; i < n; i++) {
        s = (DLinkNode *) malloc(sizeof(DLinkNode));
        s->data = a[i];
        tc->next = s;
        s->prior = tc;
        tc = s;
    }
    tc->next = NULL;
}


void delMax(DLinkNode * &L) {
    DLinkNode *p = L->next;
    DLinkNode *maxp = p;
    while (p != NULL) {
        if (p->data > maxp->data) {
            maxp = p;
        }
        p = p->next;
    }
    DLinkNode *pre = maxp->prior;
    DLinkNode *post = maxp->next;
    pre->next = post;
    if (post != NULL) {
        post->prior = pre;
    }
    maxp->next = NULL;
    maxp->prior = NULL;
    free(maxp);
}

// swap 查找第一个为x的结点，将其与后继结点进行交换
int swap(DLinkNode *L, ElemType x) {
    DLinkNode *p = L->next;
    while (p != NULL && p->data != x) {
        p = p->next;
    }
    if (p == NULL) {
        return 0;
    }
    DLinkNode *post = p->next;
    if (post == NULL) {
        return 0;
    }
    p->prior->next = post;
    post->prior = p->prior;
    p->next = post->next;
    if (post->next != NULL) {
        post->next->prior = p;
    }
    p->prior = post;
    post->next = p;
    return 1;
}


