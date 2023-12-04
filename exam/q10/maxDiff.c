
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "BSTree.h"

int getNumNodes(BSTree t);
void makeMax(int max, BSTree t);

int maxDiff(BSTree t) {
    if (t != NULL) {
        int leftTree = getNumNodes(t->left);
        int rightTree = getNumNodes(t->right);
        int diff = abs(leftTree - rightTree);
        int maxDiffVal = diff;
        makeMax(maxDiffVal, t);
        return maxDiffVal;
    }
    return 0;
}

void makeMax(int max, BSTree t) {
    if (t != NULL) {
        if (max < maxDiff(t->left)) {
            max = maxDiff(t->left);
        } 
        if (max < maxDiff(t->right)) {
            max = maxDiff(t->right);
        }
    }
}


int getNumNodes(BSTree t) {
    if (t == NULL) {
        return 0;
    } else if (t->left != NULL && t->right == NULL) {
        return 1 + getNumNodes(t->left);
    } else if (t->left == NULL && t->right != NULL) {
        return 1 + getNumNodes(t->right);
    } else if (t->left == NULL && t->right == NULL) {
        return 1;
    } else {
        return 1 + getNumNodes(t->left) + getNumNodes(t->right);
    }
}
