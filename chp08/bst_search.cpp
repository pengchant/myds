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