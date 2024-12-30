#include <stdlib.h>

#define MAX_SIZE 100

typedef char ElemType;

typedef struct bthnode {
    ElemType data;
    struct bthnode *lchild, *rchild;
    int ltag, rtag;
} BthNode;

// createBTree 创建二叉树
void createBTree(BthNode *&bt, char *str) {
    // 基于数组的栈存储结构
    BthNode *st[MAX_SIZE]; 
    int top = -1;

    bt = NULL; // 初始化二叉树根结点
    int i = 0;
    char ch = str[i]; // 遍历括号表示法的字符串

    BthNode *p = NULL; // 二叉树结点临时变量
    int flag = 0; // 处理结点的状态标记k=1,其后创建的是左子节点,k=2其后创建的是右子结点
    while (ch != '\0') {
        switch (ch) {
        case '(':
            top++; // 入栈
            st[top] = p;
            flag = 1;
            break;
        case ')':
            top--; // 出栈
            break;
        case ',':
            flag = 2; // 处理右子结点
            break;
        default:
            p = (BthNode *) malloc(sizeof(BthNode));
            p->data = ch;
            p->lchild = p->rchild = NULL;
            if (bt == NULL) {
                bt = p; // p为二叉树的根结点
            } else {
                switch (flag) {
                case 1:
                    st[top]->lchild = p;
                    break; 
                case 2:
                    st[top]->rchild = p;
                    break;
                }
            }
        }  

        i++;
        ch = str[i];
    }
}


// dispBTree 用括号法输出二叉树
void dispBTree(BthNode *bt) {
    if (bt == NULL) {
        return;
    }
    printf("%c", bt->data);
    if (bt->lchild == NULL && bt->rchild == NULL) {
        return;
    }
    printf("(");
    dispBTree(bt->lchild);
    if (bt->rchild != NULL) {
        printf(",");
    }
    dispBTree(bt->rchild);
    printf(")");
}


BthNode *pre;


// thread 以*p为根结点的二叉树进行中序线索化
void thread(BthNode *&p) {
    if (p == NULL) {
        return;
    }
    thread(p->lchild);
    if (p->lchild == NULL) {
        p->lchild = pre;
        p->ltag = 1; // 标记为线索
    } else {
        p->ltag = 0; // 标记为左孩子
    }
    if (pre->rchild == NULL) {
        pre->rchild = p;
        pre->rtag = 1; // 标记为线索
    } else {
        pre->rtag = 0; // 标记为右孩子节点
    }
    pre = p; // 缓存前驱节点
    thread(p->rchild);
}


// createThread 以bt为根结点的二叉树中序线索化，增加一个头结点head
BthNode *creatThread(BthNode *bt) {
    BthNode *head = (BthNode *) malloc(sizeof(BthNode));
    // bt为空树
    if (bt == NULL) {
        head->ltag = 0;
        head->lchild = head;
        head->rtag = 1;
        head->rchild =NULL;
        return head;
    }

    // bt 不为空树
    head->ltag = 0;
    head->lchild = bt;
    head->rtag = 1;
    head->rchild = bt;

    // 缓存前驱节点
    pre = head; 

    // 中序遍历线索化二叉树
    thread(bt);

    pre->rchild = head; // pre中序遍历的最后一个结点指向head，标记为线索
    pre->rtag = 1;

    head->rchild = pre; // head的右子节点只想最后一个结点，标记为线索
    head->rtag = 1;

    return head; // 最终返回头结点
}


void destroyBTree1(BthNode *&b) {
    if (b->ltag == 0) { // b 有左孩子释放左子树
        destroyBTree1(b->lchild);
    }
    if (b->rtag == 0) { // b 有右孩子释放右子树
        destroyBTree1(b->rchild);
    }
    free(b); // 释放b结点
}

void destroyBTree(BthNode *&tb) {
    destroyBTree1(tb->lchild); // 释放以lchild为根结点的树
    free(tb); // 释放头结点
}


// firstNode 在中序线索树中查找中序序列的第一个结点
BthNode *firstNode(BthNode *tb) {
    BthNode *p = tb->lchild; // p 指向根结点
    while (p->ltag == 0) {
        p = p->lchild;
    }
    return p;
}

// lastNode 在中序线索树中查找中序序列的最后一个结点
BthNode *lastNode(BthNode *tb) {
    return tb->rchild;
}

// preNode 查找p结点的中序遍历的前驱结点
// 1) p->ltag 直接是前驱线索标记，直接返回p->lchild;
// 2) p->ltag 不是前驱线索标记，那么就需要找pre前驱结点的最右下的结点(结合中序遍历的结构特点考虑)
BthNode *preNode(BthNode *p) {
    BthNode *pre = p->lchild;
    if (pre->ltag == 1) {
        return pre;
    }
    while (pre->rtag == 0) {
        pre = pre->rchild;
    }
    return pre;
}

// postNode 查找p结点的中序后继结点
// 1) p->rtag == 1 直接返回后继结点;
// 2) 找p的右子树的最左下角的结点
BthNode *postNode(BthNode *p) {
    BthNode *post = p->rchild;
    if (p->rtag == 1) {
        return post;
    }
    while (post->lchild == 0) {
        post = post->lchild;
    }
    return post;
}

// thInOrder 中序遍历输出结点
void thInOrder(BthNode *tb) {
    BthNode *p = firstNode(tb);
    while (p != tb) {
        printf("%c ", p->data);
        p = postNode(p); // 找p的后继结点
    }
    printf("\n");
}

// thInOrder1 中序遍历逆向输出结点
void thInOrder1(BthNode *tb) {
    BthNode *p = lastNode(tb);
    while (p != tb) {
        printf("%c ", p->data);
        p = preNode(p);
    }
    printf("\n");
}


void runBth() {
    BthNode *bt, *tb;
    createBTree(bt, "A(B(D,E(G,H)),C(,F(I)))");
    printf("二叉树bt:");
    dispBTree(bt);
    printf("\n");

    printf("构造中序线索二叉树 tb\n");
    tb = creatThread(bt);

    printf("中序遍历序列:");
    thInOrder(tb);

    printf("逆中序遍历序列:");
    thInOrder1(tb);

    destroyBTree(bt);    
}
