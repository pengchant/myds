#include <stdio.h>
#include <stdlib.h>

typedef int ElemType;

typedef struct node {
    ElemType data;
    struct node *next;
} SLinkNode;

// initList 初始化循环单链表
void initList(SLinkNode * &L) {
    L = (SLinkNode *) malloc(sizeof(SLinkNode));
    L->next = L;
}


void destroyList(SLinkNode * &L) {
    SLinkNode *pre = L;
    SLinkNode *p = pre->next;
    while (p != L) {
        free(pre);
        pre = p;
        p = p->next;
    }
    free(pre);
}

int getLength(SLinkNode *L) {
    int i = 0;
    SLinkNode *p = L->next;
    while (p != L) {
        i++;
        p = p->next;
    }
    return i;
}

int getElem(SLinkNode *L, int i, ElemType &e) {
    int j = 1;
    SLinkNode *p = L->next;
    if (i <= 0) {
        return 0;
    }
    while (p != NULL && j < i) {
        j++;
        p = p->next;
    }
    if (p == NULL) {
        return 0;
    }
    e = p->data;
    return 1;
}

int locate(SLinkNode *L, ElemType x) {
    int i = 1;
    SLinkNode *p = L->next;
    while (p != L && p->data != x) {
        i++;
        p = p->next;
    }
    if (p == L) {
        return 0;
    }
    return i;
}


int insElem(SLinkNode * &L, ElemType x, int i) {
    int j = 1;
    SLinkNode *pre = L;
    SLinkNode *p = pre->next;
    if (i <= 0) {
        return 0;
    }
    while (p != L && j < i) {
        j++;
        pre = p;
        p = p->next;
    }
    if (p == L && i > j+1) {
        return 0;
    }
    SLinkNode *s = (SLinkNode *)malloc(sizeof(SLinkNode));
    s->data = x;
    s->next = pre->next;
    pre->next = s;
    return 1;
}


int delElem(SLinkNode * &L, int i) {
    int j = 0;
    SLinkNode *p = L;
    SLinkNode *post;
    if (i <= 0) {
        return 0;
    }
    while (p->next != L && j < i - 1) {
        p = p->next;
        j++;
    }
    if (p->next == L) { // 未找到直接返回
        return 0;
    }
    post = p->next;
    p->next = post->next;
    post->next = NULL;
    free(post);
    return 1;
}

void dispList(SLinkNode *L) {
    SLinkNode *p = L->next;
    while (p != L) {
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
}


void runCSLink() {
    int i;
    ElemType e;
    SLinkNode *L;
    initList(L); // 初始化循环链表
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
    printf("删除第%d个元素\n", i);
    delElem(L, i);
    printf("线性表:");
    dispList(L);
    destroyList(L);
}

int nodes(SLinkNode *L, ElemType x) {
    int i = 0;
    SLinkNode *p = L->next;
    while (p != L) {
        if (p->data == x) {
            i++;
        }
        p = p->next;
    }
    return i;
}

int delAllX(SLinkNode * &L, ElemType x) {
    SLinkNode *pre = L;
    SLinkNode *p = L->next;
    // 找到第一个值为x的p
    while (p->data != x) {
        pre = p;
        p = p->next;
    }
    // 如果没有找到,直接退出
    if (p == L) {
        return 0;
    }
    // 查找到所有值为x的节点,并删除
    while (p != L && p->data == x) {
        pre->next = p->next;
        p->next = NULL;
        free(p);
        p = pre->next;
    }
    return 1;
}

// 求解约瑟夫问题
typedef struct jNode {
    int no;
    struct jNode *next;
} Child;


void createList(Child * &L, int n) {
    int i;
    Child *p, *tc;
    L = (Child *)malloc(sizeof(Child));
    L->no = 1;
    tc = L;
    for (int i = 2; i <= n; i++) {
        p = (Child *)malloc(sizeof(Child));
        p->no = i;
        tc->next = p;
        tc = p;
    }
    tc->next = L;
}

void Joseph(int n, int m) {
    int i, j;
    Child *L, *p, *q;
    createList(L, n);
    // 出列n个小孩
    for (i = 1; i <= n; i++) {
        p = L;
        j = 1;
        // 跳过m-1个数
        while (j < m - 1) {
            j++;
            p = p->next;
        }
        q = p->next; // q为第m个数
        printf("%d ", q->no);
        p->next = q->next;
        q->next = NULL;
        free(q);
        L = p->next; // L指向下一个节点
    }
}


void runJoseph() {
    int n = 6, m = 5;
    printf("n=%d,m=%d的约瑟夫序列:", n, m);
    Joseph(n, m);
    printf("\n");
}