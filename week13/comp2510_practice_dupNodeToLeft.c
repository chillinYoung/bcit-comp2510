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

TreeNode createTreeNodeWithChildren(int data, TreeNode left, TreeNode right) {
    TreeNode treeNode = createTreeNode(data);
    treeNode->left = left;
    treeNode->right = right;
    return treeNode;
}

void printTreeNode(TreeNode node) {
    if (!node) {
        printf("NULL\n");
        return;
    }
    if (node->left && node->right) {
        printf("Node: %d, left = %d, right = %d\n", node->data, node->left->data, node->right->data);
        return;
    }
    if (node->left) {
        printf("Node: %d, left = %d, right = NULL\n", node->data, node->left->data);
        return;
    }
    if (node->right) {
        printf("Node: %d, left = NULL, right = %d\n", node->data, node->right->data);
        return;
    }
    printf("Node: %d, left = NULL, right = NULL\n", node->data);
}

void printTree(TreeNode root) {
    if (!root) {
        return;
    }
    printTreeNode(root);
    printTree(root->left);
    printTree(root->right);
}

void freeTree(TreeNode root) {
    if (!root) {
        return;
    }
    freeTree(root->right);
    freeTree(root->left);
    free(root);
}

void insertNewNodeToLeft(TreeNode *node, int data) {
    TreeNode oldLeft = (*node)->left;
    TreeNode newNode = createTreeNode(data);
    (*node)->left = newNode;
    newNode->left = oldLeft;
}

void duplicateNodeToLeft(TreeNode root) {
    if (!root) {
        return;
    }
    insertNewNodeToLeft(&root, root->data);
    duplicateNodeToLeft(root->left->left);
    duplicateNodeToLeft(root->right);
}

int main() {
    // TreeNode node_2 = createTreeNode(20);
    // TreeNode node_1 = createTreeNodeWithChildren(40, node_2, NULL);
    // TreeNode root = createTreeNodeWithChildren(30, NULL, node_1);

    TreeNode node_3 = createTreeNode(3);
    TreeNode node_2 = createTreeNode(2);
    TreeNode root = createTreeNodeWithChildren(1, node_2, node_3);
    // printTree(root);
    duplicateNodeToLeft(root);
    printTree(root);

    freeTree(root);

    return 0;
}
