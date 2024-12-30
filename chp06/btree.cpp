#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

typedef int ElemType;

typedef ElemType SqBinTree[MAX_SIZE];

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

// preOrder 先序遍历
void preOrder(BTNode *bt) {
    if (bt == NULL) {
        return;
    }
    printf("%c ", bt->data);
    preOrder(bt->lchild);
    preOrder(bt->rchild);
}

// inOrder 中序遍历
void inOrder(BTNode *bt) {
    if (bt == NULL) {
        return;
    }
    inOrder(bt->lchild);
    printf("%c ", bt->data);
    inOrder(bt->rchild);
}

// postOrder 后续遍历
void postOrder(BTNode *bt) {
    if (bt == NULL) {
        return;
    }
    postOrder(bt->lchild);
    postOrder(bt->rchild);
    printf("%c ", bt->data);
}

void levelOrder(BTNode *bt) {
    BTNode *p;
    BTNode *qu[MAX_SIZE]; // 模拟队列
    int front = 0, rear = 0; // 队列的队首，队尾指针
    rear++;
    qu[rear] = bt;
    while (front != rear) {
        // 队首元素出队列并打印
        front = (front + 1) % MAX_SIZE;
        p = qu[front];
        printf("%c ", p->data);

        // 判断左右子结点
        if (p->lchild != NULL) {
            rear = (rear + 1) % MAX_SIZE;
            qu[rear] = p->lchild; // 左子结点入队列
        }
        if (p->rchild != NULL) {
            rear = (rear + 1) % MAX_SIZE;
            qu[rear] = p->rchild; // 右子结点入队列
        }
        
    }
}

// onenodes1 求二叉树中单分支结点个数
int onenodes1(BTNode *bt) {
    if (bt == NULL) {
        return 0;
    }
    int m = onenodes1(bt->lchild);
    int n = onenodes1(bt->rchild);
    if (bt->lchild == NULL && bt->rchild != NULL ||
        bt->rchild == NULL && bt->lchild != NULL)  {
        return 1+m+n;
    }
    return 0;
}

// twonodes 求二叉树中双分支结点个数
int twonodes(BTNode *bt) {
    if (bt == NULL) {
        return 0;
    }
    if (bt->lchild != NULL && bt->rchild != NULL) {
        return 1 + twonodes(bt->lchild) + twonodes(bt->rchild);
    }
    return twonodes(bt->lchild) + twonodes(bt->rchild);
}

// copyBTree 拷贝二叉树
void copyBTree(BTNode *bt, BTNode *&nt) {
    if (bt == NULL) {
        nt = NULL;
        return;
    }
    nt = (BTNode *) malloc(sizeof(BTNode)); // 复制根结点
    nt->data = bt->data; 
    copyBTree(bt->lchild, nt->lchild); // 递归复制左子树
    copyBTree(bt->rchild, nt->rchild); // 递归复制右子树
}


// trans1 给定二叉树链存储结构转化为顺序存储结构
void trans1(BTNode *bt, SqBinTree &sb, int i) {
    if (bt == NULL) {
        sb[i] = '#';
        return;
    }
    sb[i] = bt->data;
    trans1(bt->lchild, sb, 2*i);
    trans1(bt->rchild, sb, 2*i+1);
    return;
}

// trans2 给定二叉树的顺序存储结构建其对应的二叉链存储结构
void trans2(BTNode *&bt, SqBinTree sb, int i) {
    if (i >= MAX_SIZE || sb[i] == '#') {
        bt = NULL;
        return;
    }
    bt = (BTNode *) malloc(sizeof(BTNode));
    bt->data = sb[i];
    trans2(bt->lchild, sb, 2*i);
    trans2(bt->rchild, sb, 2*i+1);
    return;
}

// ancestor1 输出每个叶子结点的所有祖先结点
void ancestor1(BTNode *bt, ElemType path[], int pathlen) {
    if (bt == NULL) {
        return;
    }
    // bt 为叶子结点
    if (bt->lchild == NULL && bt->rchild == NULL) {
        printf("    %c 结点的所有祖先结点:", bt->data);
        for(int i = pathlen - 1; i >= 0; i--) {
            printf("%c ", path[i]);
        }
        printf("\n");
    } else {
        // bt 为非叶子结点，存入path中
        path[pathlen] = bt->data;
        pathlen++;
        ancestor1(bt->lchild, path, pathlen);
        ancestor1(bt->rchild, path, pathlen);
    }
}


// ancestor2 采用层次遍历方法求解
void ancestor2(BTNode *bt) {
    struct {
        BTNode *s;
        int parent; // 存放其双亲结点的下标
    } qu[MAX_SIZE];
    int front = -1; // 队头指针
    int rear = -1; // 队尾指针

    rear++;
    qu[rear].s = bt;
    qu[rear].parent = -1; // 根结点无双亲

    BTNode *p;
    while (front != rear) {
        front++;
        p = qu[front].s;
        // 当前结点为叶子结点，直接输出值
        if (p->lchild == NULL && p->rchild == NULL) {
            printf("    %c 结点的所有祖先结点:", p->data);
            int i = qu[front].parent;
            while (i != -1) {
                printf("%c ", qu[i].s->data);
                i = qu[i].parent;
            }
            printf("\n");
        }
        // 左子结点不为空，入队列
        if (p->lchild != NULL) {
            rear++;
            qu[rear].s = p->lchild;
            qu[rear].parent = front;
        }
        // 右子结点不为空，入队列
        if (p->rchild != NULL) {
            rear++;
            qu[rear].s = p->rchild;
            qu[rear].parent = front;
        }
    }

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

void runBTreeTraverse() {
    BTNode *bt;
    createBTree(bt, "A(B(D,E(G,H)),C(,F(I)))");
    printf("二叉树bt:");
    dispBTree(bt);
    printf("\n");

    printf("先序遍历序列:");
    preOrder(bt);
    printf("\n");

    printf("中序遍历序列:");
    inOrder(bt);
    printf("\n");

    printf("后序遍历序列:");
    postOrder(bt);
    printf("\n");

    printf("层序遍历序列:");
    levelOrder(bt);
    printf("\n");

    destroyBTree(bt);
}


void runAncestor() {
    BTNode *bt;
    ElemType path[MAX_SIZE];
    createBTree(bt, "A(B(D,E(G,H)),C(,F(K)))");
    printf("bt括号表示方法:");
    dispBTree(bt);
    printf("\n");

    printf("解法1:\n");
    printf("输出每个叶子结点的所有祖先结点:\n");
    ancestor1(bt, path, 0);

    printf("解法2:\n");
    printf("输出每个叶子结点的所有祖先结点:\n");
    ancestor2(bt);

    destroyBTree(bt);
}