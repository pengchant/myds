#include <stdlib.h>
#include <stdio.h>

#define MAX 100

typedef struct node {
    float coef;
    int exp;
    struct node *next;
} PolyNode;


// createListR 尾插法创建链表
void createListR(PolyNode * &L, double a[], int b[], int n) {
    PolyNode *s, *tc;
    L = (PolyNode *) malloc(sizeof(PolyNode));
    tc = L;
    for (int i = 0; i < n; i++) {
        s = (PolyNode *) malloc(sizeof(PolyNode));
        s->coef = a[i];
        s->exp = b[i];
        tc->next = s;
        tc = s;
    }
    tc->next = NULL;
}

void destroyList(PolyNode * &L) {
    PolyNode *pre = L;
    PolyNode *p = pre->next;
    while (p != NULL) {
        free(pre);
        pre = p;
        p = p->next;
    }
    free(pre);
}

void dispPoly(PolyNode *L) {
    PolyNode *p = L->next;
    while (p != NULL) {
        printf("(%gx^%d) ", p->coef, p->exp);
        p = p->next;
    }
    printf("\n");
}

void add(PolyNode *ha, PolyNode *hb, PolyNode * &hc) {
    PolyNode *pa = ha->next;
    PolyNode *pb = hb->next;
    hc = (PolyNode *) malloc(sizeof(PolyNode));
    PolyNode *tc = hc;
    PolyNode *s;
    double c;
    while (pa != NULL && pb != NULL) {
        if (pa->exp > pb->exp) {
            s = (PolyNode *) malloc(sizeof(PolyNode));
            s->coef = pa->coef;
            s->exp = pa->exp;
            tc->next = s;
            tc = s;
            pa = pa->next;
        } else if (pa->exp < pb->exp) {
            s = (PolyNode *) malloc(sizeof(PolyNode));
            s->coef = pb->coef;
            s->exp = pb->exp;
            tc->next = s;
            tc = s;
            pb = pb->next;
        } else {
            c =  pa->coef + pb->coef;
            if (c != 0) {
                s = (PolyNode *) malloc(sizeof(PolyNode));
                s->coef = c;
                s->exp = pa->exp;
                tc->next = s;
                tc = s;
            }
            pa = pa->next;
            pb = pb->next;
        }
    }
    while (pa != NULL) {
        s = (PolyNode *) malloc(sizeof(PolyNode));
        s->exp = pa->exp;
        s->coef = pa->coef;
        tc->next = s;
        pa = pa->next;
    }
    while (pb != NULL) {
        s = (PolyNode *) malloc(sizeof(PolyNode));
        s->exp = pb->exp;
        s->coef = pb->coef;
        tc->next = s;
        pb = pb->next;
    }
    tc->next = NULL;
}

void testRun() {
    PolyNode *p1, *p2, *p3;
    double a[MAX];
    int b[MAX], n;
    // 创建第1个多项式链表
    a[0] = 3.2;
    a[1] = 2.0;
    a[2] = -6.0;
    a[3] = 10.0;
    b[0] = 5;
    b[1] = 3;
    b[2] = 1;
    b[3] = 0;
    n = 4;
    createListR(p1, a, b, n);
    printf("第一个多项式: ");
    dispPoly(p1);

    // 创建第2个多项式链表
    a[0] = 1.8;
    a[1] = -2.5;
    a[2] = -2.0;
    a[3] = 1.0;
    a[4] = 6.0;
    a[5] = -5.0;
    b[0] = 5;
    b[1] = 4;
    b[2] = 3;
    b[3] = 2;
    b[4] = 1;
    b[5] = 0;
    n = 6;
    createListR(p2, a, b, n);
    printf("第2个多项式:");
    dispPoly(p2);

    // 进行相加
    add(p1, p2, p3);
    printf("相加后的多项式:");
    dispPoly(p3);

    // 销毁链表
    destroyList(p1);
    destroyList(p2);
    destroyList(p3);
}

