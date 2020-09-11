/*
 * COMP 2510 Week 13 Lab & Assignment Combo: BST
 *
 * Young Kim(A01087377)
 * Dec 1, 2020
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// ERROR CODES
#define FAIL_ALLOC_MEM 1

struct Node {
    int data;
    struct Node *left;
    struct Node *right;
};

typedef struct Node *TreeNode;

TreeNode createTreeNode(int data) {
    TreeNode treeNode = (TreeNode) malloc(sizeof(struct Node));
    if (treeNode == NULL) {
        perror("#Error: fail to allocate memory.");
        exit(FAIL_ALLOC_MEM);
    }
    treeNode->data = data;
    treeNode->left = NULL;
    treeNode->right = NULL;
    return treeNode;
}

TreeNode insert(TreeNode root, int data) {
    if (!root) {
        return createTreeNode(data);
    }
    if (data <= root->data) {
        root->left = insert(root->left, data);
    } else {
        root->right = insert(root->right, data);
    }
    return root;
}

void printInOrder(TreeNode root) {
    if (!root) {
        return;
    }
    printInOrder(root->left);
    printf(" %d", root->data);
    printInOrder(root->right);
}

void freeTree(TreeNode root) {
    if (!root) {
        return;
    }
    freeTree(root->right);
    freeTree(root->left);
    free(root);
}

bool equals(TreeNode firstRoot, TreeNode secondRoot) {
    if (!firstRoot && !secondRoot) {
        return true;
    }
    if (!firstRoot || !secondRoot) {
        return false;
    }
    return (firstRoot->data == secondRoot->data) && equals(firstRoot->left, secondRoot->left) && equals(firstRoot->right, secondRoot->right);
}

bool containsPathWithSum(TreeNode root, int sum) {
    if (!root) {
        return false;
    }
    if (!root->left && !root->right) {
        return !(sum - root->data);
    }
    return containsPathWithSum(root->left, sum - root->data) || containsPathWithSum(root->right, sum - root->data);
}

void mirror(TreeNode root) {
    if (!root) {
        return;
    }
    TreeNode temp = root->left;
    root->left = root->right;
    root->right = temp;

    mirror(root->left);
    mirror(root->right);
}

int main() {
    /*
               5
              / \
             /   \
            4     10
           /      /\
          /      /  \
        -8      7    12
    */
    TreeNode manyLeavesTree = NULL;
    manyLeavesTree = insert(manyLeavesTree, 5);
    manyLeavesTree = insert(manyLeavesTree, 4);
    manyLeavesTree = insert(manyLeavesTree, 10);
    manyLeavesTree = insert(manyLeavesTree, -8);
    manyLeavesTree = insert(manyLeavesTree, 7);
    manyLeavesTree = insert(manyLeavesTree, 12);    

    /*
              4
             /
            /
           2
          /
         /
        1
    */
    TreeNode oneLineTree = NULL;
    oneLineTree = insert(oneLineTree, 4);
    oneLineTree = insert(oneLineTree, 2);
    oneLineTree = insert(oneLineTree, 1);

    /*
               7
              / \
             /   \
            0     9
           / \
          /   \
        -1     3
    */
    TreeNode zeroContainTree = NULL;
    zeroContainTree = insert(zeroContainTree, 7);
    zeroContainTree = insert(zeroContainTree, 0);
    zeroContainTree = insert(zeroContainTree, 9);
    zeroContainTree = insert(zeroContainTree, 3);
    zeroContainTree = insert(zeroContainTree, -1);

    TreeNode oneNodeTree = NULL;
    oneNodeTree = insert(oneNodeTree, 1);

    /* Null */
    TreeNode nullTree = NULL;

    printf("== equals Tests ==\n");
    printf("Same many leaves Trees: %s\n", equals(manyLeavesTree, manyLeavesTree) ? "True" : "False");
    printf("Same One Node Trees:    %s\n", equals(oneNodeTree, oneNodeTree) ? "True" : "False");
    printf("Different Trees:        %s\n", equals(oneLineTree, manyLeavesTree) ? "True" : "False");
    printf("Both Null Trees:        %s\n", equals(nullTree, nullTree) ? "True" : "False");
    printf("Null and Not Null Tree: %s\n", equals(nullTree, zeroContainTree) ? "True" : "False");

    printf("\n== containsPathWithSum Tests ==\n");
    printf("–– Tree with many leaves Test: expected 1, 22, and 27 to be true.\n");
    printf("1:  %s\n", containsPathWithSum(manyLeavesTree, 1) ? "True" : "False");
    printf("5:  %s\n", containsPathWithSum(manyLeavesTree, 5) ? "True" : "False");
    printf("9:  %s\n", containsPathWithSum(manyLeavesTree, 9) ? "True" : "False");
    printf("15: %s\n", containsPathWithSum(manyLeavesTree, 15) ? "True" : "False");
    printf("22: %s\n", containsPathWithSum(manyLeavesTree, 22) ? "True" : "False");
    printf("27: %s\n", containsPathWithSum(manyLeavesTree, 27) ? "True" : "False");

    printf("\n–– One Line Tree Test: expected 7 to be true.\n");
    printf("4:  %s\n", containsPathWithSum(oneLineTree, 4) ? "True" : "False");
    printf("6:  %s\n", containsPathWithSum(oneLineTree, 6) ? "True" : "False");
    printf("7:  %s\n", containsPathWithSum(oneLineTree, 7) ? "True" : "False");
    printf("10: %s\n", containsPathWithSum(oneLineTree, 10) ? "True" : "False");

    printf("\n–– Zero Contain Tree Test: expected 6, 10, and 16 to be true.\n");
    printf("0:  %s\n", containsPathWithSum(zeroContainTree, 0) ? "True" : "False");
    printf("6:  %s\n", containsPathWithSum(zeroContainTree, 6) ? "True" : "False");
    printf("7:  %s\n", containsPathWithSum(zeroContainTree, 7) ? "True" : "False");
    printf("10: %s\n", containsPathWithSum(zeroContainTree, 10) ? "True" : "False");
    printf("16: %s\n", containsPathWithSum(zeroContainTree, 16) ? "True" : "False");

    printf("\n–– One Node Test: expected 1 to be true.\n");
    printf("1:  %s\n", containsPathWithSum(oneNodeTree, 1) ? "True" : "False");
    printf("5:  %s\n", containsPathWithSum(oneNodeTree, 5) ? "True" : "False");
    printf("10: %s\n", containsPathWithSum(oneNodeTree, 10) ? "True" : "False");

    printf("\n–– Null Test: expected all to be false.\n");
    printf("0:  %s\n", containsPathWithSum(nullTree, 0) ? "True" : "False");
    printf("4:  %s\n", containsPathWithSum(nullTree, 4) ? "True" : "False");
    printf("6:  %s\n", containsPathWithSum(nullTree, 6) ? "True" : "False");
    printf("10: %s\n", containsPathWithSum(nullTree, 10) ? "True" : "False");

    printf("\n== mirror Tests ==\n");
    printf("Input Tree:        ");
    printInOrder(manyLeavesTree);
    printf("\n");
    mirror(manyLeavesTree);
    printf("After Mirror Tree: ");
    printInOrder(manyLeavesTree);
    printf("\n");

    printf("Input Tree:        ");
    printInOrder(oneLineTree);
    printf("\n");
    mirror(oneLineTree);
    printf("After Mirror Tree: ");
    printInOrder(oneLineTree);
    printf("\n");

    printf("Input Tree:        ");
    printInOrder(oneNodeTree);
    printf("\n");
    mirror(oneNodeTree);
    printf("After Mirror Tree: ");
    printInOrder(oneNodeTree);
    printf("\n");

    printf("Input Tree (NULL): ");
    printInOrder(nullTree);
    printf("\n");
    mirror(nullTree);
    printf("After Mirror Tree: ");
    printInOrder(nullTree);
    printf("\n");

    freeTree(manyLeavesTree);
    freeTree(oneLineTree);
    freeTree(zeroContainTree);
    freeTree(oneNodeTree);

    return 0;
}

