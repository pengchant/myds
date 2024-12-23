#include <stdlib.h>
#include <stdio.h>

typedef struct node {
    char data;
    struct node *next;
} LinkString;


// assign 
void assign(LinkString * &s, char str[]) {
    s = (LinkString *) malloc(sizeof(LinkString));
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
    s = (LinkString *) malloc(sizeof(LinkString));
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
    LinkString *q;
    while (p != NULL) {
        q = (LinkString *) malloc(sizeof(LinkString));
        q->data = p->data;
        tc->next = q;
        tc = q;
        p = p->next;
    }
    // 切换到另一个字符串链表
    p = t->next;
    while (p != NULL) {
        q = (LinkString *) malloc(sizeof(LinkString));
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
        return r;
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
        return r;
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

// index 返回子串t在主串t
int index(LinkString *s, LinkString *t) {
    int i = 1;
    LinkString *p = s->next;
    LinkString *q;
    LinkString *p1, *q1;
    while (p != NULL) {
        q = t->next; // 子串的第一个元素
        if (p->data == q->data) { // 如果首字符相同,则继续比较
            // p,q同时往后移动一个位置
            p1 = p->next;
            q1 = q->next;
            // 一直进行主串和子串的比较
            while (p1 != NULL && q1 != NULL && p1->data == q1->data) {
                p1 = p1->next;
                q1 = q1->next;
            }
            if (q1 == NULL) { // 若都相同，则返回相同的起始位置
                return i;
            }
        }
        p = p->next; // 原始链表继续后移
        i++; // i位置累加
    }
    return 0; // 没有找到返回0
}

// insStr 将子串t插入链串s的第i个位置
int insStr(LinkString * &s, int i, LinkString *t) {
    if (i < 1) {
        return 0;
    }
    // p 往后移动i-1个位置
    LinkString *p = s;
    int k = 1;
    while (k < i && p != NULL) {
        p = p->next;
        k++;
    }
    // 如果参数i错误直接返回
    if (p == NULL) {
        return 0;
    }
    // 开始遍历子串
    LinkString *q = t->next;
    LinkString *r;
    while (q != NULL) {
        r = (LinkString *) malloc(sizeof(LinkString));
        r->data = q->data;
        r->next = p->next;
        p->next = r;
        p = p->next;
        q = q->next;
    }
    return 1;
}

// delStr 删除串中从第i个位置开始的j个字符
int delStr(LinkString * &s, int i, int j) {
    if (i < 1 || j < 1) {
        return 0;
    }
    LinkString *p = s;
    int k = 1;
    while (k < i && p != NULL) {
        p = p->next;
        k++;
    }
    if (p == NULL) {
        return 0;
    }

    k = 1;
    LinkString *q = p->next;
    while (k < j && q != NULL) {
        q = q->next;
        k++;
    }
    if (q == NULL) {
        return 0;
    }

    k = 1;
    // 执行删除
    while (k <= j) {
        q = p->next; // q重新指向待删除的第一个节点
        if (q->next == NULL) {
            free(q);
            p->next = NULL;
        } else {
            p->next = q->next;
            free(q);
        }
        k++;
    }
    return 1;
}

LinkString * replaceAll(LinkString *s, LinkString *s1, LinkString *s2) {
    int i = index(s, s1);
    while (i > 0) {
        delStr(s, i, strLength(s1));
        insStr(s, i, s2);
        i = index(s, s1);
    }
    return s;
}

void dispStr(LinkString *s) {
    LinkString *p = s->next;
    while (p != NULL) {
        printf("%c ", p->data);
        p = p->next;
    }
    printf("\n");
}

void testRun() {
    LinkString *s1, *s2, *s3, *s4, *s5, *s6, *s7;
    assign(s1, "abcd");
    printf("s1:");
    dispStr(s1);
    printf("s1的长度:%d\n", strLength(s1));
    printf("s1=>s2\n");
    strCopy(s2, s1);
    printf("s2:");
    dispStr(s2);
    printf("s1和s2%s\n", (strEqual(s1, s2) == 1 ? "相同" : "不相同"));
    assign(s3, "12345678");
    printf("s3:");
    dispStr(s3);
    printf("s1和s3连接=>s4\n");
    s4 = concat(s1, s3);
    printf("s4:");
    dispStr(s4);
    printf("s3[2..5]=>s5\n");
    s5 = subStr(s3, 2, 4);
    printf("s5:");
    dispStr(s5);
    assign(s6, "567");
    printf("s6:");
    dispStr(s6);
    printf("s6在s3中位置:%d\n", index(s3, s6));
    printf("从s3中删除s3[3..6]字符\n");
    delStr(s3, 3, 4);
    printf("s3:");
    dispStr(s3);
    printf("从s4中将s6替换成s1=>s7\n");
    s7 = replaceAll(s4, s6, s1);
    printf("s7:");
    dispStr(s7);
    // destroy
    destroyStr(s1);
    destroyStr(s2);
    destroyStr(s3);
    destroyStr(s4);
    destroyStr(s5);
    destroyStr(s6);
}







