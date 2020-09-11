#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define GRADE_THRESHOLD 4.3
#define ARRAY_INIT_SIZE 10
// ERROR CODES
#define FAIL_ALLOC_MEM 1

struct Node {
    double grade;
    char *studentName;
    struct Node *left;
    struct Node *right;
};

typedef struct Node *TreeNode;

void errorIfArrayIsNull(void *anArray) {
    if (anArray == NULL) {
        perror("#Error: failed to allocate memory.");
        exit(FAIL_ALLOC_MEM);
    }
}

TreeNode createTreeNode(char *studentName, double grade) {
    TreeNode treeNode = (TreeNode) malloc(sizeof(struct Node));
    errorIfArrayIsNull(treeNode);
    treeNode->studentName = strdup(studentName);
    treeNode->grade = grade;
    treeNode->left = NULL;
    treeNode->right = NULL;
    return treeNode;
}

TreeNode insert(TreeNode root, char *studentName, double grade) {
    if (!root) {
        return createTreeNode(studentName, grade);
    }
    if (grade <= root->grade) {
        root->left = insert(root->left, studentName, grade);
    } else {
        root->right = insert(root->right, studentName, grade);
    }
    return root;
}

void freeTree(TreeNode root) {
    if (!root) {
        return;
    }
    freeTree(root->right);
    freeTree(root->left);
    free(root->studentName);
    free(root);
}

char *resizeArrayTwiceIfNeeded(char **studentArray, size_t numOfTopStudents, size_t *currArrSize) {
    if (numOfTopStudents >= *currArrSize) {
        *currArrSize += *currArrSize;
        studentArray = (char **) realloc(studentArray, (*currArrSize) * sizeof(char *));
        errorIfArrayIsNull(studentArray);
    }
    return *studentArray;
}

void getTopStudentsArray(TreeNode root, double threshold, char **studentArray, size_t *numOfTopStudents, size_t *currArrSize) {
    if (!root) {
        return;
    }
    getTopStudentsArray(root->right, threshold, studentArray, numOfTopStudents, currArrSize);

    if (root->grade >= threshold) {
        studentArray[*numOfTopStudents] = root->studentName;
        *numOfTopStudents += 1;
        *studentArray = resizeArrayTwiceIfNeeded(studentArray, *numOfTopStudents, currArrSize);
    }

    getTopStudentsArray(root->left, threshold, studentArray, numOfTopStudents, currArrSize);
}

char **topStudents(TreeNode root, double threshold, size_t *numOfTopStudents) {
    size_t currArrSize = ARRAY_INIT_SIZE;
    char **studentArray = (char **) malloc(currArrSize * sizeof(char *));
    getTopStudentsArray(root, threshold, studentArray, numOfTopStudents, &currArrSize);
    studentArray[*numOfTopStudents] = 0;

    return studentArray;
}

void printTopStudents(char **studentArray, size_t numOfTopStudents) {
    int count = 0;
    while (count < numOfTopStudents && studentArray[count]) {
        printf("%s\n", studentArray[count]);
        count++;
    }
}

int main() {
    TreeNode root = createTreeNode("Chris Yiwei", 4.2);
    root = insert(root, "Ray Song", 3.9);
    root = insert(root, "Young Kim", 4.4);
    root = insert(root, "Ted Jo", 4.3);
    root = insert(root, "Jae Choi", 4.5);
    root = insert(root, "Jaeyoung So", 3.2);
    root = insert(root, "Sora Lee", 4.3);
    root = insert(root, "Seyed Javadi", 3.5);
    root = insert(root, "Kate Park", 4.2);
    root = insert(root, "Katherine Kim", 4.4);
    root = insert(root, "Somi Han", 2.7);
    root = insert(root, "Niu Yirong", 4.5);
    root = insert(root, "Abby Tamura", 4.4);
    root = insert(root, "Soma Teyaki", 4.3);
    root = insert(root, "James Shikejya", 4.5);
    root = insert(root, "Olivia Somekura", 4.3);

    size_t numOfTopStudents = 0;
    char **studentArray = topStudents(root, GRADE_THRESHOLD, &numOfTopStudents);
    printTopStudents(studentArray, numOfTopStudents);

    free(studentArray);
    freeTree(root);

    return 0;
}
