#include <stdio.h>

#define MAX_SIZE 20

typedef char ElemType;

typedef struct {
    ElemType data[MAX_SIZE];
    int front, rar;
} SqQueue;

void initQueue(SqQueue &sq) {
    sq.rar = sq.front = 0; // 指针初始化
}


void destroyQueue(SqQueue sq) {
    // todo: do nothing
}

int enQueue(SqQueue &sq, ElemType x) {
    if ((sq.rar + 1) % MAX_SIZE == sq.front) {
        return 0; // 队列满了
    }
    sq.rar = (sq.rar + 1) % MAX_SIZE;
    sq.data[sq.rar] = x;
    return 1;
}

int deQueue(SqQueue &sq, ElemType &x) {
    if (sq.rar == sq.front) {
        return 0; // 队列为空
    }
    sq.front = (sq.front + 1) % MAX_SIZE;
    x = sq.data[sq.front];
    return 1;
}

int getHead(SqQueue sq, ElemType &x) {
    if (sq.rar == sq.front) {
        return 0; // 队列为空
    }
    x = sq.data[(sq.front+1) % MAX_SIZE];
    return 1;
}


int queueEmpty(SqQueue sq) {
    if (sq.rar == sq.front) {
        return 1;
    }
    return 0;
}


void testRunQueue() {
    SqQueue sq;
    ElemType e;
    printf("初始化队列\n");
    initQueue(sq);
    printf("队 %s\n", (queueEmpty(sq) ? "空" : "不空"));
    printf("a 进队 %d\n", enQueue(sq, 'a'));
    printf("b 进队 %d\n", enQueue(sq, 'b'));
    printf("c 进队 %d\n", enQueue(sq, 'c'));
    printf("d 进队 %d\n", enQueue(sq, 'd'));
    printf("队 %s\n", (queueEmpty(sq) ? "空" : "不空"));
    getHead(sq, e);
    printf("队头元素: %c\n", e);
    printf("出队次序:");
    // 依次出队列
    while (!queueEmpty(sq)) {
        deQueue(sq, e);
        printf("%c ", e);
    }
    printf("\n");
    destroyQueue(sq);
}





