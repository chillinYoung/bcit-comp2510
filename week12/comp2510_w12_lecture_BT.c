#include <stdio.h>
#include <stdlib.h>

// ERROR CODES
#define FAIL_ALLOC_MEM 1
#define NULL_NODE 2

struct Node {
    int data;
    struct Node *parent;
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

TreeNode createTreeNode(int data, TreeNode parent, TreeNode left, TreeNode right) {
    TreeNode node = (TreeNode) malloc(sizeof(struct Node));
    errorIfPointerIsNull(&node);
    node->data = data;
    node->parent = parent;
    node->left = left;
    node->right = right;
    return node;
}

void printNodeWithTag(char *tag, TreeNode node) {
    if (!node) {
        printf("%s: NULL\t", tag);
        return;
    }
    printf("%s: %d\t", tag, node->data);
}

void printParent(TreeNode node) {
    printNodeWithTag("Parent", node->parent);
}

void printLeft(TreeNode node) {
    printNodeWithTag("Left", node->left);
}

void printRight(TreeNode node) {
    printNodeWithTag("Right", node->right);
}

void printSelf(TreeNode node) {
    printNodeWithTag("Node", node);
}

void printTreeNode(TreeNode node) {
    if (!node) {
        printf("NULL\n");
        return;
    }
    printSelf(node);
    printParent(node);
    printLeft(node);
    printRight(node);
    printf("\n");
}

void printTree(TreeNode root) {
    if (!root) {
        return;
    }
    printTreeNode(root);
    printTree(root->left);
    printTree(root->right);
}

TreeNode insert(TreeNode root, int data) {
    if (!root) {
        return createTreeNode(data, NULL, NULL, NULL);
    }
    if (data <= root->data) {
        root->left = insert(root->left, data);
        root->left->parent = root;
    } else {
        root->right = insert(root->right, data);
        root->right->parent = root;
    }
    return root;
}

struct PathNode {
    TreeNode treeNode;
    struct PathNode *next;
};

typedef struct PathNode* PathLink;

PathLink createPathNode(TreeNode treeNode) {
    PathLink link = (PathLink) malloc(sizeof(struct PathNode));
    errorIfPointerIsNull(&link);
    link->treeNode = treeNode;
    link->next = NULL;
    return link;
}

PathLink createPathNodeWithNextNode(TreeNode treeNode, PathLink next) {
    PathLink link = createPathNode(treeNode);
    link->next = next;
    return link;
}

void push(PathLink *head, TreeNode treeNode) {
    PathLink newHead = createPathNodeWithNextNode(treeNode, *head);
    *head = newHead;
}

PathLink getPathToRoot(TreeNode node) {
    if (!node) {
        perror("#Error: node is null.");
        exit(NULL_NODE);
    }
    PathLink path = NULL;
    while (node) {
        push(&path, node);
        node = node->parent;
    }
    return path;
}

void printPath(PathLink head) {
    if (!head) {
        printf("\n");
        return;
    }
    printf("%d", head->treeNode->data);
    if(head->next) {
        printf("->");
    }
    printPath(head->next);
}

TreeNode findLowestCommonAncestor(TreeNode firstNode, TreeNode secondNode) {
    PathLink firstPath = getPathToRoot(firstNode);
    PathLink secondPath = getPathToRoot(secondNode);
    TreeNode result = NULL;
    while (firstPath && secondPath && (firstPath->treeNode == secondPath->treeNode)) {
        result = firstPath->treeNode;
        firstPath = firstPath->next;
        secondPath = secondPath->next;
    }
    return result;
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

TreeNode findLowestCommonAncestorBST(TreeNode root, TreeNode firstNode, TreeNode secondNode) {
    if (root->data < firstNode->data && root->data < secondNode->data) {
        return findLowestCommonAncestorBST(root->right, firstNode, secondNode);
    }
    if (root->data > firstNode->data && root->data > secondNode->data) {
        return findLowestCommonAncestorBST(root->left, firstNode, secondNode);
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
    printPath(getPathToRoot(root->right->right));

    TreeNode lowestCommonAncestor = findLowestCommonAncestor(root->left, root->right->left);
    printTreeNode(lowestCommonAncestor);
    
    freeTree(root);
    return 0;
}

