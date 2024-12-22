#include <stdio.h>

#define MAX_SIZE 20

typedef char ElemType;

typedef struct {
    ElemType data[MAX_SIZE];
    int front;
    int count;
} SQueue;


// initQueue 初始化队列
void initQueue(SQueue &qu) {
    qu.front = qu.count = 0;
}

void destroyQueue(SQueue sq) {

}

// enQueue 元素进队列算法
int enQueue(SQueue &sq, ElemType x) {
    if (sq.count == MAX_SIZE) {
        return 0;
    }
    sq.count++;
    sq.data[(sq.front + sq.count)%MAX_SIZE] = x;
    return 1;
}


int deQueue(SQueue &sq, ElemType &x) {
    if (sq.count == 0) {
        return 0;
    }
    sq.count--;
    sq.front = (sq.front + 1) % MAX_SIZE;
    x = sq.data[sq.front];
    return 1;
}

int getHead(SQueue sq, ElemType &x) {
    if (sq.count == 0) {
        return 0;
    }
    x = sq.data[(sq.front + 1) % MAX_SIZE];
    return 1;
}

int queueEmpty(SQueue sq) {
    if (sq.count == 0) {
        return 1;
    }
    return 0;
}

