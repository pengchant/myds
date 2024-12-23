#include <stdio.h>
#include <stdlib.h>

typedef char ElemType;

typedef struct node {
    ElemType data;
    struct node *next;
} QNode;

// initQueue 初始化队列
void initQueue(QNode * &lq) {
    lq = NULL;
}

// destroyQueue 销毁队列
void destroyQueue(QNode * &lq) {
    if (lq == NULL) {
        return;
    }
    QNode *pre = lq;
    QNode *p = lq->next;
    if (p == pre) {
        free(lq);
        return;
    }
    while (p != lq) {
        free(pre);
        pre = p;
        p = p->next;
    }
    free(lq);
}

// enQueue 入队列
void enQueue(QNode * &lq, ElemType x) {
    QNode *s = (QNode *) malloc(sizeof(QNode));
    s->data = x;
    if (lq == NULL) {
        lq = s;
        lq->next = lq;
        return;
    }
    s->next = lq->next;
    lq->next = s;
    lq = s;
}

// deQueue 出队列
int deQueue(QNode * &lq, ElemType &x) {
    if (lq == NULL) {
        return 0;
    }
    if (lq->next == lq) {
        x = lq->data;
        free(lq);
        lq = NULL;
        return 0;
    }
    QNode *s = lq->next;
    x = s->data;
    lq->next = s->next;
    free(s);
    return 1;
}

// getHead 获取队列头元素值
int getHead(QNode *lq, ElemType &x) {
    if (lq == NULL) {
        return 0;
    }
    x = lq->next->data;
    return 1;
}

// queueEmpty 判断队列是否为空
int queueEmpty(QNode *lq) {
    if (lq == NULL) {
        return 1;
    }
    return 0;
}