/*
 * COMP 2510 Lab #11
 *
 * Young Kim(A01087377)
 * Nov 20, 2020
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// ERROR CODES
#define FAIL_ALLOC_MEM 1

struct Node {
    void *data;
    struct Node *left;
    struct Node *right;
};

typedef struct Node *TreeNode;

TreeNode createTreeNode(void *data) {
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

bool compareDouble(void *first, void *second) {
    double firstData = *(double *)first;
    double secondData = *(double *)second;
    return (firstData >= secondData);
}

bool compareString(void *first, void *second) {
    return strcmp(*(char **) first, *(char **) second) > 0;
}

bool compareInteger(void *first, void *second) {
    int *firstInt = (int *) first;
    int *secondInt = (int *) second;
    return *firstInt > *secondInt;
}

bool compareChar(void *first, void *second) {
    char *firstChar = (char *)first;
    char *secondChar = (char *)second;
    return *firstChar > *secondChar;
}

TreeNode insert(TreeNode root, void *data, bool (*compareFunc)(void*, void*)) {
    if (!root) {
        return createTreeNode(data);
    }
    if (!compareFunc(data, root->data)) {    // data < root->data
        root->left = insert(root->left, data, compareFunc);
    } else {
        root->right = insert(root->right, data, compareFunc);
    }
    return root;
}

void printDouble(void *data) {
    printf(" %.2lf", *(double *)data);
}

void printString(void *data) {
    printf(" %s", *(char **) data);
}

void printInteger(void *data) {
        printf(" %d", *(int *)data);
}

void printChar(void *data) {
        printf(" %c", *(char *)data);
}

void printInOrder(TreeNode root, void (*printFunc)(void*)) {
    if (!root) {
        return;
    }
    printInOrder(root->left, printFunc);
    printFunc(root->data);
    printInOrder(root->right, printFunc);
}

void printTree(TreeNode root, void (*printFunc)(void*)) {
    printInOrder(root, printFunc);
    printf("\n");
}

void freeTree(TreeNode root) {
    if (!root) {
        return;
    }
    freeTree(root->right);
    freeTree(root->left);
    free(root);
}

void *findNthElement(void *array, int num, size_t sizeOfEachElemInBytes) {
    return (char *)array + (num - 1) * sizeOfEachElemInBytes;
}

void bstSort(void *array, int dataSize, size_t sizeOfEachElemInBytes,
                    bool (*compareFunc)(void*, void*), void (*printFunc)(void*)) {
    TreeNode root = NULL;
    for (int i = 1; i <= dataSize; i++) {
        void *inputData = findNthElement(array, i, sizeOfEachElemInBytes);
        root = insert(root, inputData, compareFunc);
    }
    printTree(root, printFunc);
    freeTree(root);
}

int main() {
    int integerArray[] = {10, 1, -2, 5, 7};
    bstSort(integerArray, 5, sizeof(int), compareInteger, printInteger);

    char charArray[] = {'o', 'l', 'l', 'e', 'H'};
    bstSort(charArray, 5, sizeof(char), compareChar, printChar);

    double doubleArray[] = {1.44, 0.55, 3.22, 4.11, 2.33};
    bstSort(doubleArray, 5, sizeof(double), compareDouble, printDouble);

    char *stringArray[] = {"why", "this", "does", "not", "work"};
    bstSort(stringArray, 5, sizeof(stringArray[0]), compareString, printString);

    char* words[] = {"Seyed", "Jack", "Vicky", "123", "????"};
    bstSort(words, 5, sizeof(words[0]), compareString, printString);

    return 0;
}
