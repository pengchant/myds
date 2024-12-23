#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct LNode{
    char data[10];
    struct LNode *next;
} QType;

typedef struct {
    QType *front;
    QType *rear;
} LQueue;

// initQueue 初始化队列
void initQueue(LQueue * &lq) {
    lq = (LQueue *) malloc(sizeof(LQueue));
    lq->rear = lq->front = NULL;
}

// destroyQueue 销毁队列
void destroyQueue(LQueue * &lq) {
    QType *pre = lq->front;
    if (pre == NULL) {
        free(lq);
        return;
    }
    if (pre == lq->rear) {
        free(pre);
        free(lq);
        return;
    }
    QType *p = pre->next;
    while (p != NULL) {
        free(pre);
        pre = p;
        p = p->next;
    }
    free(pre);
    free(lq);
    return;
}

// enQueue 入队列
void enQueue(LQueue * &lq, char x[]) {
    QType *s = (QType *) malloc(sizeof(QType));
    strcpy(s->data, x);
    s->next = NULL;
    if (lq->front == NULL) {
        lq->front = s;
        lq->rear = s;
        return;
    }
    lq->rear->next = s;
    lq->rear = s;
    return;
}

// deQueue 出队列
int deQueue(LQueue * &lq, char x[]) {
    if (lq->front == NULL) {
        return 0;
    }
    QType *p = lq->front;
    strcpy(x, p->data);
    // 如果队列中只有一个结点
    if (lq->front == lq->rear) {
        free(lq->front);
        lq->front = lq->rear = NULL;
        return 1;
    }
    // 如果队列中有多个结点
    lq->front = lq->front->next;
    free(p);
    return 1;
}

// queueEmpty 判断队列是否为空
int queueEmpty(LQueue *lq) {
    if (lq->front == NULL) {
        return 1;
    }
    return 0;
}

// dispQueue 输出队列中所有元素
int dispQueue(LQueue *lq) {
    if (queueEmpty(lq)) {
        return 0;
    }
    QType *p = lq->front;
    while (p != NULL) {
        printf("%s ", p->data);
        p = p->next;
    }
    printf("\n");
    return 1;
}


// runQueueApp 队列的实际应用
void runQueueApp() {
    int sel; // 记录用户的选择
    int flag = 1;
    char name[10];
    LQueue *lq; // 存储队列
    initQueue(lq);
    while (flag == 1) {
        printf("1: 排队 2:看医生 3:查看排队 0:下班 请选择:");
        scanf("%d", &sel);
        switch (sel) {
        case 0: // 下班
            if (!queueEmpty(lq)) {
                printf("    >>请排队的换成明天就医\n");
            }
            destroyQueue(lq);
            flag = 0;
            break;
        case 1: // 排队
            printf("    >>输入患者姓名:");
            scanf("%s", name);
            enQueue(lq, name);
            break;
        case 2: // 看医生
            if (!deQueue(lq, name)) {
                printf("    >>没有排队的患者\n");
            } else {
                printf("    >>患者%s看医生\n", name);
            }
            break;
        case 3: // 查看排队
            printf("    >>排队患者:");
            if (!dispQueue(lq)) {
                printf("    >>没有排队的患者\n");
            }
            break;
        default:
            break;
        }
    }
}
