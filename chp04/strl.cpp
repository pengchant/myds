#include <stdlib.h>
#include <stdio.h>

typedef struct node {
    char data;
    struct node *next;
} LinkString;


// assign 
void assign(LinkString * &s, char str[]) {
    LinkString *s = (LinkString *) malloc(sizeof(LinkString));
    LinkString *tc = s;
    int i = 0;
    while (str[i] != '\0') {
        LinkString *p = (LinkString *) malloc(sizeof(LinkString));
        p->data = str[i];
        tc->next = p;
        tc = p;
        i++;
    }
    tc->next = NULL;
}

// destroyStr 销毁字符串
void destroyStr(LinkString * &s) {
    LinkString *pre = s;
    LinkString *p = pre->next;
    while (p != NULL) {
        free(pre);
        pre = p;
        p = p->next;
    }
    free(pre);
}

// strCopy 将一个链串赋值给另一个链串
void strCopy(LinkString * &s, LinkString *t) {
    LinkString *p = t->next;
    LinkString *s = (LinkString *) malloc(sizeof(LinkString));
    LinkString *tc = s; // 使用尾插法构建链串
    while(p != NULL) {
        LinkString *q = (LinkString *) malloc(sizeof(LinkString));
        q->data = p->data;
        tc->next = q;
        tc = q;
        p = p->next;
    }
    tc->next = NULL;
}

// strLength 求串长度算法
int strLength(LinkString *s) {
    int n = 0;
    LinkString *p = s->next;
    while (p != NULL) {
        n++;
        p = p->next;
    }
    return n;
}


// strEqual 判断串是否相等
int strEqual(LinkString *s, LinkString *t) {
    LinkString *p = s->next;
    LinkString *q = t->next;
    while (p != NULL && q != NULL) {
        if (p->data != q->data) {
            return 0;
        }
        p = p->next;
        q = q->next;
    }
    if (p != NULL || q != NULL) {
        return 0;
    }
    return 1;
}

// concat 字符串连接s和t
LinkString* concat(LinkString *s, LinkString *t) {
    // 新建一个虚拟头结点
    LinkString *r = (LinkString *) malloc(sizeof(LinkString));
    LinkString *tc = r; // 通过尾插法实现连接字符串
    // 第一个字符串链表
    LinkString *p = s->next;
    while (p != NULL) {
        LinkString *q = (LinkString *) malloc(sizeof(LinkString));
        q->data = p->data;
        tc->next = q;
        tc = q;
        p = p->next;
    }
    // 切换到另一个字符串链表
    p = tc->next;
    while (p != NULL) {
        LinkString *q = (LinkString *) malloc(sizeof(LinkString));
        q->data = p->data;
        tc->next = q;
        tc = q;
        p = p->next;
    }
    tc->next = NULL; // 最后一个指针置为NULL
    return r;
}

// subStr 求子串运算算法
LinkString* subStr(LinkString *s, int i, int j) { 
    LinkString *p = s->next;
    LinkString *r = (LinkString *) malloc(sizeof(LinkString));
    r->next = NULL;
    if (i < 1) {
        return 1;
    }
    LinkString *tc = r; // 尾插法构建子串
    int k;
    // k往前移动i个指针
    while (k < i && p != NULL) {
        p = p->next;
        k++;
    }
    // i参数错误直接返回r
    if (p == NULL) {
        return r;
    }
    // 判断j参数是否正确
    k = 1;
    LinkString *q = p;
    while (k < j && q != NULL) {
        q = q->next;
        k++;
    }
    // j参数错误直接返回r
    if (q == NULL) {
        return 1;
    }
    // 从p指针指向的元素之后构建字符串链
    k = 1;
    while (k <= j && p != NULL) {
        q = (LinkString *) malloc(sizeof(LinkString));
        q->data = p->data;
        tc->next = q;
        tc = q;
        p = p->next;
        k++;
    }
    tc->next = NULL;
    return r;
}






