#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

typedef int ElemType;

typedef struct node {
    ElemType data;
    struct node *lchild, *rchild;
} BTNode;


// createBTree 创建二叉树
void createBTree(BTNode *&bt, char *str) {
    // 基于数组的栈存储结构
    BTNode *st[MAX_SIZE]; 
    int top = -1;

    bt = NULL; // 初始化二叉树根结点
    int i = 0;
    char ch = str[i]; // 遍历括号表示法的字符串

    BTNode *p = NULL; // 二叉树结点临时变量
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
            p = (BTNode *) malloc(sizeof(BTNode));
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

// sum 递归的方式求所有结点的和
int sum(BTNode *b) {
    if (b == NULL) {
        return 0;
    }
    return b->data + sum(b->lchild) + sum(b->rchild);
}

// destroyBTree 销毁二叉树
void destroyBTree(BTNode *&bt) {
    if (bt == NULL) {
        return;
    }
    destroyBTree(bt->lchild);
    destroyBTree(bt->rchild);
    free(bt);
}

// btHeight 求二叉树高度运算算法
int btHeight(BTNode *bt) {
    if (bt == NULL) {
        return 0;
    }
    int l = btHeight(bt->lchild);
    int r = btHeight(bt->rchild);
    return l > r ? l + 1 : r + 1;
}

// nodeCount 求二叉树结点个数运算算法
int nodeCount(BTNode *bt) {
    if (bt == NULL) {
        return 0;
    }
    int num1 = nodeCount(bt->lchild);
    int num2 = nodeCount(bt->rchild);
    return num1 + num2 + 1;
}


// leafCount 求叶子结点的个数
int leafCount(BTNode *bt) {
    if (bt == NULL) {
        return 0;
    }
    if (bt->lchild == NULL && bt->rchild == NULL) {
        return 1;
    }
    int num1 = leafCount(bt->lchild);
    int num2 = leafCount(bt->rchild);
    return num1 + num2;
}

// dispBTree 用括号法输出二叉树
void dispBTree(BTNode *bt) {
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


void runBTree() {
    BTNode *bt;
    createBTree(bt, "A(B(D,E(G,H)),C(,F(I)))");
    printf("二叉树bt:");
    dispBTree(bt);
    printf("\n");
    printf("二叉树的高度: %d\n", btHeight(bt));
    printf("二叉树的结点数: %d\n", nodeCount(bt));
    printf("二叉树的子结点数: %d\n", leafCount(bt));
    destroyBTree(bt);
}