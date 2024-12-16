#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

typedef char ElemType;

typedef struct {
    ElemType data[MAX_SIZE];
    int top;
} SqStack;


void initStack(SqStack &st) {
    st.top = -1;
}

void destroyStack(SqStack st) {
}

int push(SqStack &st, ElemType x) {
    if (st.top == MAX_SIZE - 1) {
        return 0;
    }
    st.data[++st.top] = x;
    return 1;
}

int pop(SqStack &st, ElemType &x) {
    if (st.top == -1) {
        return 0;
    }
    x = st.data[st.top--];
    return 1;
}

int getTop(SqStack st, ElemType &x) {
    if (st.top == -1) {
        return 0;
    }
    x = st.data[st.top];
    return 1;
}


int stackEmpty(SqStack st) {
    if (st.top == -1) {
        return 1;
    }
    return 0;
}

void testRun() {
    SqStack st;
    ElemType e;
    printf("初始化栈 st\n");
    initStack(st);
    printf("栈%s\n", (stackEmpty(st) == 1 ? "空" : "不空"));

    printf("a进栈\n");
    push(st, 'a');
    printf("b进栈\n");
    push(st, 'b');
    printf("c进栈\n");
    push(st, 'c');
    printf("d进栈\n");
    push(st, 'd');

    printf("栈%s\n", (stackEmpty(st) == 1 ? "空" : "不空"));
    getTop(st, e);
    printf("栈顶元素: %c\n", e);

    printf("出栈依次顺序:");
    while (!stackEmpty(st)) {
        pop(st, e);
        printf("%c ", e);
    }
    printf("\n");

    // 销毁栈
    destroyStack(st);

}


int judge(char str[], int n) {
    SqStack st;
    ElemType x;
    initStack(st);
    for (int i = 0; i < n; i++) {
        if (str[i] == 'I') {
            push(st, str[i]);
        } else if (str[i] == 'O') {
            if (!pop(st, x)) {
                destroyStack(st);
                return 0;
            }
        }
    }
    if (stackEmpty(st)) {
        destroyStack(st);
        return 1;
    }
    destroyStack(st);
    return 1;
}

// palindrome 判断回文数字
int palindrome(char str[], int n) {
    SqStack st;
    initStack(st);
    for (int i = 0; i < n; i++) {
        push(st, str[i]);
    }
    int i = 0;
    char ch;
    while (!stackEmpty(st)) {
        pop(st, ch);
        if (ch != str[i++]) {
            destroyStack(st);
            return 0;
        }
    }
    destroyStack(st);
    return 1;
}

int match(char exp[], int n) {
    SqStack st;
    initStack(st);
    int flag = 1;
    int i = 0;
    char ch;
    while (i < n && flag == 1) {
        switch (exp[i]) {
        case '(':
        case '[':
        case '{':
            push(st, exp[i]);
            break;
        case ')':
            if (!pop(st, ch) || ch != '(') {
                flag = 0;
            }
            break;
        case ']':
            if (!pop(st, ch) || ch != '[') {
                flag = 0;
            }
            break;
        case '}':
            if (!pop(st, ch) || ch != '{') {
                flag = 0;
            }
            break;
        }
    }
    if (stackEmpty(st) && flag == 1) {
        destroyStack(st);
        return 1;
    }
    
    destroyStack(st);
    return 0;
}


