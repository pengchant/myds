#include <stdlib.h>
#include <stdio.h>

typedef char ElemType;

typedef struct node {
    ElemType data;
    struct node *next;
} LinkStack;


void initStack(LinkStack * &ls) {
    ls = NULL;
}

void destroyStack(LinkStack * &ls) {
    LinkStack *pre = ls;
    LinkStack *p;
    if (pre == NULL) {
        return;
    }
    p = pre->next;
    while (p != NULL) {
        free(pre);
        pre = p;
        p = p->next;
    }
    free(pre);
}


int push(LinkStack * &ls, ElemType x) {
    LinkStack *p;
    p = (LinkStack *) malloc(sizeof(LinkStack));
    p->data = x;
    p->next = ls;
    ls = p; // 栈顶元素
    return 1;
}


int pop(LinkStack * &ls, ElemType &x) {
    if (ls == NULL) {
        return 0;
    }
    LinkStack *p = ls;
    x = p->data;
    ls = p->next;
    free(p);
    return 1;
}


int getTop(LinkStack *ls, ElemType &x) {
    if (ls == NULL) {
        return 0;
    }
    x = ls->data;
    return 1;
}

int stackEmpty(LinkStack *ls) {
    if (ls == NULL) {
        return 1;
    }
    return 0;
}

void runLinkStack() {
    ElemType e;
    LinkStack *st;

    printf("初始化栈 st\n");
    initStack(st);
    printf("栈 %s\n", (stackEmpty(st) == 1 ? "空" : "不空"));

    printf("a 进栈\n");
    push(st, 'a');
    printf("b 进栈\n");
    push(st, 'b');
    printf("c 进栈\n");
    push(st, 'c');
    printf("d 进栈\n");
    push(st, 'd');

    printf("栈 %s\n", (stackEmpty(st) == 1 ? "空" : "不空"));
    getTop(st, e);
    printf("栈顶元素: %c\n", e);
    printf("出栈顺序: ");
    while (!stackEmpty(st)) {
        pop(st, e);
        printf("%c ", e);
    }
    printf("\n");

    destroyStack(st);
}

