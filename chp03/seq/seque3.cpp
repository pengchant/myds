#include <stdlib.h>
#include <stdio.h>

typedef char ElemType;

typedef struct QNode {
    ElemType data;
    struct QNode *next;
} QType;

typedef struct qptr {
    QType *front;
    QType *rear;
} LinkQueue;


// initQueue 初始化队列
void initQueue(LinkQueue * &lq) {
    lq = (LinkQueue *) malloc(sizeof(LinkQueue));
    lq->rear = lq->front = NULL;
}

// destroyQueue 销毁队列
void destroyQueue(LinkQueue * &lq) {
    QType *pre = lq->front;
    if (pre == NULL) {
        free(lq);
        return;
    }

    QType *p = pre->next;
    while (p != NULL) {
        free(pre);
        pre = p;
        p = p->next;
    }
    free(lq);
}

// enQueue 进队列
int enQueue(LinkQueue * &lq, ElemType &x) {
    QType *s = (QType *) malloc(sizeof(QType));
    s->data = x;
    s->next = NULL;
    if (lq->front == NULL) {
        lq->rear = s;
        lq->front = s;
        return 1;
    }
    lq->rear->next = s;
    lq->rear = s;
    return 1;
}

// deQueue 出队列
int deQueue(LinkQueue * &lq, ElemType &x) { 
    // 判断队列是否为空
    if (lq->front == NULL) {
        return 0;
    }
    QType *p = lq->front;
    x = p->data;
    if (lq->front == lq->rear) {
        lq->rear = lq->front = NULL;
    } else {
        lq->front = lq->front->next;
    }
    free(p);
    return 1;
}

int getHead(LinkQueue *lq, ElemType &x) {
    if (lq->front == NULL) {
        return 0; // 队列为空
    }
    x = lq->front->data; // 取队列头部元素值
    return 1;
}

int queueEmpty(LinkQueue *lq) {
    if (lq->front == NULL) {
        return 1;
    }
    return 0;
}


void runQueue() {
    LinkQueue *lq;
    ElemType e;
    printf("初始化队列\n");
    initQueue(lq);

    printf("队列 %s\n", queueEmpty(lq) ? "空" : "不空");
    e = 'a';
    printf("a 进队: %d\n", enQueue(lq, e));
    e = 'b';
    printf("b 进队: %d\n", enQueue(lq, e));
    e = 'c';
    printf("c 进队: %d\n", enQueue(lq, e));
    e = 'd';
    printf("d 进队: %d\n", enQueue(lq, e));
    printf("队列 %s\n", queueEmpty(lq) ? "空" : "不空");
    
    getHead(lq, e);
    printf("队头元素: %c\n", e);
    printf("出队次序:");
    while (!queueEmpty(lq)) {
        deQueue(lq, e);
        printf("%c ", e);
    }
    printf("\n");
    destroyQueue(lq);
}



