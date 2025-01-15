#include <stdio.h>
#include <stdlib.h>

typedef int KeyType;

typedef int ElemType;

typedef struct bstnode {
    KeyType key;
    ElemType data;
    struct bstnode *lchild, *rchild;
} BSTNode;

BSTNode *bstSearch(BSTNode *bt, KeyType k) {
    BSTNode *p = bt;
    while (p != NULL) {
        if (p->key == k) {
            return p;
        } else if (k < p->key) {
            p = p->lchild;
        } else {
            p = p->rchild;
        }
    }
    return NULL;
}


int bstInsert(BSTNode *&bt, KeyType k) {
    BSTNode *f; // f 缓存插入结点的指针
    BSTNode *p = bt;
    while (p != NULL) {
        if (p->key == k) {
            return 0;
        }
        f = p; // f 指向 p 结点的双亲结点
        if (k < p->key) {
            p = p->lchild;
        } else {
            p = p->rchild;
        }
    }
    // 新建结点
    p = (BSTNode *) malloc(sizeof(BSTNode));
    p->key = k;
    p->lchild = p->rchild = NULL;
    // 然后再对应的位置插入结点
    if (bt == NULL) {
        bt = p;
    } else if (k < f->key) {
        f->lchild = p;
    } else {
        f->rchild = p;
    }
    return 1;
}

// createBST 创建二叉树运算算法
void createBST(BSTNode *&bt, KeyType a[], int n) {
    bt = NULL;
    int i = 0;
    while (i < n) {
        bstInsert(bt, a[i]); // 将关键字a[i]插入二叉树bt中
        i++;
    }
}

// destroyBST 销毁BST
void destroyBST(BSTNode *&bt) {
    if (bt == NULL) {
        return;
    }
    destroyBST(bt->lchild);
    destroyBST(bt->rchild);
    free(bt);
}

// dispBST 把二叉排序树按照括号表示法输出
void dispBST(BSTNode *bt) {
    if (bt == NULL) {
        return;
    }
    printf("%d", bt->key);
    if (bt->lchild != NULL || bt->rchild != NULL) {
        printf("(");
        dispBST(bt->lchild);
        if (bt->rchild != NULL) {
            printf(",");
        }
        dispBST(bt->rchild);
        printf(")");
    }
}

// bstDelete 删除结点
int bstDelete(BSTNode *&bt, KeyType k) {
    if (bt == NULL) {
        return 0;
    }
    // 先遍历二叉搜索树，找到对应关键字key
    BSTNode *p = bt;
    BSTNode *f = NULL;
    while (p != NULL) {
        if (p->key == k) {
            break;
        }
        f = p;
        if (k < p->key) {
            p = p->lchild;
        } else {
            p = p->rchild;
        }
    }
    if (p == NULL) {
        return 0;
    }
    // 判断不同的情形
    if (p->lchild == NULL) {
        // 左子树为空
        if (f == NULL) {
            bt = p->rchild;
        } else if (f->lchild == p) { // p 位于左半部分
            f->lchild = p->rchild;
        } else if (f->rchild == p) { // p 位于右半部分
            f->rchild = p->rchild;
        }
        free(p);
    } else if (p->rchild == NULL) {
        // 右子树为空
        if (f == NULL) {
            bt = p->lchild;
        } else if (f->lchild == p) {
            f->lchild = p->lchild;
        } else if (f->rchild == p) {
            f->rchild = p->lchild;
        }
        free(p);
    } else {
        // 左右子树全不为空
        BSTNode *q = p->lchild;  // q指向p结点的左孩子
        if (q->rchild == NULL) {
            p->key = q->key; // p 点的值用 q点的值替换
            p->data = q->data;
            p->lchild = q->lchild;
            free(q);
        } else {
            BSTNode *f1 = q;
            BSTNode *q1 = f1->rchild;
            // 查找q结点下最右下结点q1,f1指向其双亲
            while (q1->rchild != NULL) {
                f1 = q1;
                q1 = q1->rchild;
            }
            // 将p结点用q1结点值代替
            p->key = q1->key;
            p->data = q1->data;
            f1->rchild = q1->lchild;
            free(q1);
        }
    }
    return 1;
}


void runBST() {
    KeyType a[] = {25, 18, 46, 2, 53, 39, 32, 4, 74, 67, 60, 11};
    int k = 25;
    int n = 12;
    BSTNode *bt;
    createBST(bt, a, n); // 由关键字序列a创建二叉排序树bt
    printf("BST:");
    dispBST(bt);
    printf("\n");

    printf("删除关键字%d\n", k);
    if (bstDelete(bt, k)) {
        printf("BST:");
        dispBST(bt);
        printf("\n");
    } else {
        printf("未找到关键字为%d的结点\n", k);
    }
    printf("插入关键字%d\n", k);
    if (bstInsert(bt, k)) {
        printf("BST:");
        dispBST(bt);
        printf("\n");
    } else {
        printf("存在重复的关键字%d\n", k);
    }
    destroyBST(bt);
}