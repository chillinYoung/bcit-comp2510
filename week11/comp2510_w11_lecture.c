#include <stdio.h>
#include <stdlib.h>

// ERROR CODES
#define FAIL_ALLOC_MEM 1
#define ROOT_NULL 2

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

int getNumberOfNodesInLongestPath(TreeNode root) {
    if (!root) {
        return 0;
    }
    int left = getNumberOfNodesInLongestPath(root->left);
    int right = getNumberOfNodesInLongestPath(root->right);
    int max = (left > right) ? left : right;
    return max + 1;
}

int getTreeHeight(TreeNode root) {
    if (!root) {
        perror("#Error: root is NULL.");
        exit(ROOT_NULL);
    }
    return getNumberOfNodesInLongestPath(root) - 1;
}

TreeNode findNodeWithData(TreeNode root, int targetData) {
    if (!root) {
        return NULL;
    }
    if (root->data == targetData) {
        return root;
    }
    if (root->data > targetData) {
        return findNodeWithData(root->left, targetData);
    }
    return findNodeWithData(root->right, targetData);
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

void printPreOrder(TreeNode root) {
    if (!root) {
        return;
    }
    printf(" %d", root->data);
    printPreOrder(root->left);
    printPreOrder(root->right);
}

void printPostOrder(TreeNode root) {
    if (!root) {
        return;
    }
    printPostOrder(root->left);
    printPostOrder(root->right);
    printf(" %d", root->data);
}

/*
       5
     /   \
    /     \
   3       8
  /\       /\
 /  \     /  \
1    4   6    9
*/
int main() {
    TreeNode node_1 = createTreeNode(1);
    TreeNode node_6 = createTreeNode(6);
    TreeNode node_9 = createTreeNode(9);
    TreeNode node_4 = createTreeNode(4);
    TreeNode node_3 = createTreeNodeWithChildren(3, node_1, node_4);
    TreeNode node_8 = createTreeNodeWithChildren(8, node_6, node_9);
    TreeNode root = createTreeNodeWithChildren(5, node_3, node_8);

    root = insert(root, 10);

    printTree(root);

    int height = getTreeHeight(root);
    printf("Height = %d\n", height);

    TreeNode node = findNodeWithData(root, 10);
    printTreeNode(node);

    printf("––– newTreeNodes –––\n");
    TreeNode newTreeRoot = NULL;
    newTreeRoot = insert(newTreeRoot, 4);
    newTreeRoot = insert(newTreeRoot, 2);
    newTreeRoot = insert(newTreeRoot, 6);
    newTreeRoot = insert(newTreeRoot, 1);
    newTreeRoot = insert(newTreeRoot, 3);
    newTreeRoot = insert(newTreeRoot, 5);
    newTreeRoot = insert(newTreeRoot, 7);
    // printTree(newTreeRoot);

    printInOrder(newTreeRoot);
    printf("\n");
    return 0;
}
