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

void destroyBST(BSTNode *&bt) {
    if (bt == NULL) {
        return;
    }
    destroyBST(bt->lchild);
    destroyBST(bt->rchild);
    free(bt);
}