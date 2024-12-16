#include <stdio.h>
#include <stdlib.h>

typedef int ElemType;

// 链表节点
typedef struct node {
    ElemType data;
    struct node *next;
} SLinkNode;


void initList(SLinkNode * &L) {
    L = (SLinkNode *)malloc(sizeof(SLinkNode));
    L->next = NULL;
}

void destroyList(SLinkNode * &L) {
    SLinkNode *pre = L;
    SLinkNode *p = pre->next;
    while (p != NULL) {
        free(pre);
        pre = p;
        p = p->next;
    }
    free(pre);
}

int getLength(SLinkNode *L) {
    int i = 0;
    SLinkNode *p = L->next;
    while (p != NULL) {
        i++;
        p = p->next;
    }
    return i;
}

int getElem(SLinkNode *L, int i, ElemType &e) {
    int j = 0;
    SLinkNode *p = L;
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


int locate(SLinkNode *L, ElemType e) {
    SLinkNode *p = L->next;
    int j = 1;
    while (p != NULL && p->data != e) {
        p = p->next;
        j++;
    }
    if (p == NULL) {
        return 0;
    }
    return j;
}


int insElem(SLinkNode * &L, ElemType x, int i) {
    if (i <= 0) {
        return 0;
    }
    int j = 0;
    SLinkNode *p = L;
    SLinkNode *s;
    while (p != NULL && j < i - 1) {
        j++;
        p = p->next;
    }
    if (p == NULL) {
        return 0;
    }

    s = (SLinkNode *)malloc(sizeof(SLinkNode));
    s->data = x;
    s->next = p->next;
    p->next = s;
    return 1;
}


int delElem(SLinkNode * &L, int i) {
    if (i <= 0) {
        return 0;
    }

    int j = 0;
    SLinkNode *p = L;
    SLinkNode *q;
    while (p != NULL && j < i - 1) {
        j++;
        p = p->next;
    }
    if (p == NULL) {
        return 0;
    }

    q = p->next;
    if (q == NULL) {
        return 0;
    }
    p->next = q->next;
    q->next = NULL;
    free(q);
    return 1;
}


void dispList(SLinkNode *L) {
    SLinkNode *p = L->next;
    while (p != NULL) {
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
}

void createListF(SLinkNode *&L, ElemType a[], int n) {
    SLinkNode *s;
    // 虚拟头结点
    L = (SLinkNode *)malloc(sizeof(SLinkNode));
    L->next = NULL;
    // create link list
    for (int i = 0; i < n; i++) {
        s = (SLinkNode *)malloc(sizeof(SLinkNode));
        s->data = a[i];
        s->next = L->next;
        L->next = s;
    }
}

void createListR(SLinkNode * &L, ElemType a[], int n) {
    SLinkNode *s;
    SLinkNode *tc;
    L = (SLinkNode *)malloc(sizeof(SLinkNode));
    tc = L;
    for (int i = 0; i < n; i++) {
        s = (SLinkNode *) malloc(sizeof(SLinkNode));
        s->data = a[i];
        tc->next = s;
        tc = s;
    }
    tc->next = NULL;
}



void testLink() {
    int i;
    ElemType e;
    SLinkNode *L;
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
    e = 1;
    printf("元素%d是第%d个元素\n", e, locate(L, e));
    i = 4;
    printf("删除第%d个元素\n", i);
    delElem(L, i);
    printf("线性表:");
    dispList(L);
    destroyList(L);
}





// 算法设计
SLinkNode *maxNode(SLinkNode *L) {
    SLinkNode *p = L->next;
    SLinkNode *maxp = p;
    while (p != NULL) {
        if (maxp->data < p->data) {
            maxp = p;
        }
        p = p->next;
    }
    return maxp;
}

SLinkNode *preMaxNode(SLinkNode *L) {
    SLinkNode *p = L->next;
    SLinkNode *pre = L;
    SLinkNode *maxp = p;
    SLinkNode *maxpre = L;
    while (p != NULL) {
        if (maxp->data < p->data) {
            maxp = p;
            maxpre = pre;
        }
        pre = p;
        p = p->next;
    }
    if (maxpre == L) {
        return NULL;
    }
    return maxpre;
}

void delMaxNode(SLinkNode * &L) {
    SLinkNode *p = L->next;
    SLinkNode *pre = L;
    SLinkNode *maxp = p;
    SLinkNode *maxpre = pre;
    while (p != NULL) {
        if (maxp->data < p->data) {
            maxp = p;
            maxpre = pre;
        }
        pre = p;
        p = p->next;
    }
    maxpre->next = maxp->next;
    maxp->next = NULL;
    free(maxp);
}

void reverse(SLinkNode * &L) {
    SLinkNode *p = L->next;
    SLinkNode *q;
    L->next = NULL;
    // 采用尾插法
    while (p != NULL) {
        q = p->next;
        p->next = L->next;
        L->next = p;
        p = q;
    }
}

// move1: 奇数移动到偶数前面
void move1(SLinkNode * &L) {
    if (L == NULL) {
        return;
    }
    SLinkNode *p = L->next;
    SLinkNode *q, *tc;
    L->next = NULL;
    tc = L; // tc为尾节点指针
    while (p != NULL) {
        // 如果为奇数采用头插法
        if ((p->data & 1) == 1) {
            q = p->next; 
            // 如果L为空表
            if (L->next == NULL) {
                p->next = L->next;
                L->next = p;
                tc = p;
            } else {
                p->next = L->next;
                L->next = p;
            }
            p = q;
        } else {
            // 如果为偶数采用尾插法
            tc->next = p;
            tc = p;
            p = p->next;
        }
    }
    tc->next = NULL;
}



void merge(SLinkNode *ha, SLinkNode *hb, SLinkNode * &hc) {
    SLinkNode *pa = ha->next;
    SLinkNode *pb = hb->next;
    SLinkNode *tc;
    hc = ha;
    tc = hc;
    free(hb);
    while (pa != NULL && pb != NULL) {
        if (pa->data < pb->data) {
            tc->next = pa;
            pa = pa->next;
        } else {
            tc->next = pb;
            pb = pb->next;
        }
    }
    tc->next = NULL;
    if (pa != NULL) {
        tc->next = pa;
    }
    if (pb != NULL) {
        tc->next = pb;
    }
}

void commonElem(SLinkNode *ha, SLinkNode *hb, SLinkNode * &hc) {
    SLinkNode *pa = ha->next;
    SLinkNode *pb = hb->next;
    SLinkNode *tc, *s;
    hc = (SLinkNode *) malloc(sizeof(SLinkNode));
    tc = hc;
    while (pa != NULL && pb != NULL) {
        if (pa->data < pb->data) {
            pa = pa->next;
        } else if (pb->data < pa->data) {
            pb = pb->next;
        } else {
            s = (SLinkNode *) malloc(sizeof(SLinkNode));
            s->data = pa->data;
            tc->next = s;
            tc = s;
            pa = pa->next;
            pb = pa->next;
        }
    }
    tc->next = NULL;
}

// 设计一个完整的应用程序要求根据用户输入的学生人数n(n>=3)以及每个学生的姓名和成绩建立一个
// 单链表，并按照学生成绩递减排序，然后按名次输出所有学生姓名和成绩

typedef struct snode {
    char name[10];
    int score;
    struct snode *next;
} StudList;

// createStudent 创建学生单链表
void createStudent(StudList * &sl) {
    int n, i;
    StudList *s, *tc;
    sl = (StudList *) malloc(sizeof(StudList));
    tc = sl;
    printf("学生人数:");
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        s = (StudList *) malloc(sizeof(StudList));
        printf("第%d个学生学生姓名和成绩:", i+1);
        scanf("%s", s->name);
        scanf("%d", &s->score);
        tc->next = s;
        tc = s;
    }
    tc->next = NULL;
}


// destroyList 销毁学生单链表
void destroyList(StudList * &L) {
    StudList *pre = L;
    StudList *p = pre->next;
    while (p != NULL) {
        free(pre);
        pre = p;
        p = p->next;
    }
    free(pre);
}

void dispList(StudList *L) {
    StudList *p = L->next;
    int i = 1;
    printf("\t\t名次\t\t姓名\t\t成绩\n");
    while (p != NULL) {
        printf("\t\t%d\t\t", i++);
        printf("%s\t\t", p->name);
        printf("%d\n", p->score);
        p = p->next;
    }
}


void sortList(StudList * &L) {
    if (L->next == NULL) {
        return;
    }
    StudList *p, *pre, *q;
    p = L->next->next;
    L->next->next = NULL;
    while (p != NULL) {
        q = p->next; // 缓存后面的list
        pre = L;
        while (pre->next != NULL && pre->next->score > p->score) {
            pre = pre->next;
        }
        // 插入新元素
        p->next = pre->next;
        pre->next = p;
        p = q; // 让p重新指向第二个链表
    }
}


void runStudList() {
    StudList *st;
    printf("(1)创建学生单链表\n");
    createStudent(st);
    printf("(2)按成绩递减排序\n");
    sortList(st);
    printf("(3)排序后的结果\n");
    dispList(st);
    printf("(4)销毁学生单链表\n");
    destroyList(st);
}