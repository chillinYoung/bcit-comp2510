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

void errorIfPointerIsNull(void *pointer) {
    if (pointer == NULL) {
        perror("#Error: failed to allocate memory.");
        exit(FAIL_ALLOC_MEM);
    }
}

TreeNode createTreeNode(int data) {
    TreeNode treeNode = (TreeNode) malloc(sizeof(struct Node));
    errorIfPointerIsNull(&treeNode);
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

enum LeftOrRight {Left, Right};
typedef enum LeftOrRight Direction;

Direction *allocateDirectionArray(int height) {
    Direction *directions = (Direction *) calloc(height, sizeof(enum LeftOrRight));
    errorIfPointerIsNull(directions);
    return directions;
}

void findNode(TreeNode root, int targetData, Direction *directions) {
    if (root->data == targetData) {
        return;
    }
    if (root->data > targetData) {
        *directions = Left;
        findNode(root->left, targetData, directions + 1);
    } else  {
        *directions = Right;
        findNode(root->right, targetData, directions + 1);
    }
}

TreeNode findLowestCommonNode(TreeNode root, Direction *firstNodeDirections, Direction *secondNodeDirections) {
    if (!*firstNodeDirections || !*secondNodeDirections || *firstNodeDirections != *secondNodeDirections) {
        return root;
    }
    TreeNode nextNode = (*firstNodeDirections == Left) ? root ->left : root->right;
    return findLowestCommonNode(nextNode, firstNodeDirections + 1, secondNodeDirections + 1);
}

/*TreeNode findLowestCommonAncestorBST(TreeNode root, TreeNode firstNode, TreeNode secondNode, int height) {
    Direction *firstNodeDirections = allocateDirectionArray(height);
    findNode(root, firstNode->data, firstNodeDirections);
    Direction *secondNodeDirections = allocateDirectionArray(height);
    findNode(root, secondNode->data, secondNodeDirections);
    return findLowestCommonNode(root, firstNodeDirections, secondNodeDirections);
}*/

/*
 * Q: why works? what was the bug?
 * Guess before figure it out: the height might be different between firstNode and secondNode.
 *                              and that can lead an error.
 */
TreeNode findLowestCommonAncestorBST_better(TreeNode root, TreeNode firstNode, TreeNode secondNode) {
    if (root->data < firstNode->data && root->data < secondNode->data) {
        return findLowestCommonAncestorBST_better(root->right, firstNode, secondNode);
    }
    if (root->data > firstNode->data && root->data > secondNode->data) {
        return findLowestCommonAncestorBST_better(root->left, firstNode, secondNode);
    }
    return root;
}

void freeTree(TreeNode root) {
    if (!root) {
        return;
    }
    freeTree(root->right);
    freeTree(root->left);
    free(root);
}

/*
       4
     /   \
    /     \
   2       6
  /\       /\
 /  \     /  \
1    3   5    7
*/
int main() {
    TreeNode root = NULL;
    root = insert(root, 4);
    root = insert(root, 2);
    root = insert(root, 6);
    root = insert(root, 1);
    root = insert(root, 3);
    root = insert(root, 5);
    root = insert(root, 7);
    
    TreeNode lowestCommonAncestor = findLowestCommonAncestorBST_better(root, root->right->right, root->right->left);
    printf("LCA: %d\n", lowestCommonAncestor->data);

    freeTree(root);
    return 0;
}
