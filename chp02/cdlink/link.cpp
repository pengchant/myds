#include <stdlib.h>
#include <stdio.h>

typedef int ElemType;

// 循环双链表
typedef struct node {
    int data;
    struct node *prior, *next;
} DLinkNode;

void initList(DLinkNode * &L) {
    L = (DLinkNode *) malloc(sizeof(DLinkNode));
    L->prior = L;
    L->next = L;
}

void destroyList(DLinkNode * &L) {
    DLinkNode *pre = L;
    DLinkNode *p = L->next;
    while (p != L) {
        free(pre);
        pre = p; // pre, p 同步后移
        p = p->next;
    }
    free(pre);
}

int getLength(DLinkNode *L) {
    int i = 0;
    DLinkNode *p = L->next;
    while (p != L) {
        i++;
        p = p->next;
    }
    return i;
}

int getElem(DLinkNode *L, int i, ElemType &e) {
    int j = 1;
    DLinkNode *p = L->next;
    if (i <= 0) {
        return 0;
    }
    while (p != L && j < i) {
        j++;
        p = p->next;
    }
    if (p == L) {
        return 0;
    }
    e = p->data;
    return 1;
}

int locate(DLinkNode *L, ElemType x) {
    int i = 1;
    DLinkNode *p = L->next;
    while (p != L && p->data != x) {
        i++;
        p = p->next;
    }
    if (p == L) {
        return 0;
    }
    return i;
}

int insElem(DLinkNode * &L, ElemType x, int i) {
    int j = 1;
    DLinkNode *p = L->next;
    if (i <= 0) {
        return 0;
    }
    while (p != L && j < i) {
        j++;
        p = p->next;
    }
    if (p == L && i > j+1) {
        return 0;
    }
    DLinkNode *pre = p->prior;
    DLinkNode *s = (DLinkNode *) malloc(sizeof(DLinkNode));
    s->data = x;
    s->next = p;
    p->prior = s;
    s->prior = pre;
    pre->next = s;
    return 1;
}

int delElem(DLinkNode * &L, int i) {
    int j = 1;
    DLinkNode *p = L->next;
    if (i <= 0) {
        return 0;
    }
    if (L->next == L) {
        return 0;
    }
    while (p != L && j < i) {
        p = p->next;
        j++;
    }
    if (p == L) {
        return 0;
    }
    DLinkNode *pre = p->prior;
    pre->next = p->next;
    p->next->prior = pre;
    p->next = NULL;
    p->prior = NULL;
    free(p);
    return 1;
}

void dispList(DLinkNode *L) {
    DLinkNode *p = L->next;
    while (p != L) {
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
}

// reverse 将双循环链表逆序
void reverse(DLinkNode * &L) {
    DLinkNode *p = L->next;
    DLinkNode *q;
    L->next = L->prior = L; // 构造空的双循环链表
    while (p != L) {
        q = p->next;
        p->next = L->next;
        L->next->prior = p;
        p->prior = L;
        L->next = p;
        p = q;
    }
}

// symmetric 判断元素是否对称
int symmetric(DLinkNode *L) {
    DLinkNode *p = L->next;
    DLinkNode *q = L->prior;
    int flag = 1;
    while (p != q) {
        if (p->data != q->data) {
            flag = 0;
            break;
        }
        p = p->next;
        q = q->prior;
    }
    return flag;
}

void runDLink() {
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
    printf("第%d个元素: %d\n", i, e);
    delElem(L, i);
    printf("线性表:");
    dispList(L);
    printf("逆序:");
    reverse(L);
    dispList(L);
    destroyList(L);
}



