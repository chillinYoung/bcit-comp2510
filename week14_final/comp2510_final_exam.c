/*
 * COMP 2510 Final Exam
 *
 * Young Kim(A01087377)
 * Dec 10, 2020
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// ERROR CODES
#define FAIL_ALLOC_MEM 1
#define FILE_NOT_FOUND 2
#define FILE_NOT_CREATED 3
#define EMPTY_ROOT_PASSED 4

struct NameStruct {
    char *name;
};

/*
 ***** Question #1 *****
 *
 * Problem with this function: 
 * node->name is NOT able to free its memory because the memory was not allocated to the heap for node->name.
 * However, in 'destroy' function, it tried to free node->name, so Abort trap: 6 error was raised.
 * Fix: allocate memory for name in NameStruct using strdup().
 */
struct NameStruct *createNameStruct(char *message) {
    struct NameStruct *newNode = (struct NameStruct*) malloc(sizeof(struct NameStruct));
    if (!newNode) {
        perror("Out of memory\n");
        exit(FAIL_ALLOC_MEM);
    }
    newNode->name = strdup(message);
    if (!newNode->name) {
        perror("Out of memory\n");
        exit(FAIL_ALLOC_MEM);
    }
    return newNode;
}

void destroy(struct NameStruct* node) {
    free(node->name);
    free(node);
}

/***** Question #2 *****/
bool areIntegersSame(void *first, void *second) {
    int *firstInt = (int *) first;
    int *secondInt = (int *) second;
    return *firstInt == *secondInt;
}

bool areCharsSame(void *first, void *second) {
    char *firstChar = (char *)first;
    char *secondChar = (char *)second;
    return *firstChar == *secondChar;
}

bool areDoublesSame(void *first, void *second) {
    double *firstDouble = (double *)first;
    double *secondDouble = (double *)second;
    return *firstDouble == *secondDouble;
}

bool areStringsSame(void *first, void *second) {
    char *firstString = *(char **)first;
    char *secondString = *(char **)second;
    return strcmp(firstString, secondString) == 0;
}

void *findNthElement(void *array, int num, size_t sizeOfEachElem) {
    return (char *)array + (num - 1) * sizeOfEachElem;
}

bool areElementsInGenericArrayUnique(void *array, size_t size, size_t sizeOfEachElem, bool (*compare)(void *, void *)) {
    if (size <= 1) {
        return true;
    }
    void *firstElement = findNthElement(array, 1, sizeOfEachElem);
    void *secondElement;
    for (int i = 1; i < size; i++) {
        secondElement = findNthElement(array, i + 1, sizeOfEachElem);
        if (compare(firstElement, secondElement)) {
            return false;
        }
    }
    return areElementsInGenericArrayUnique((array + sizeOfEachElem), size - 1, sizeOfEachElem, compare);
}

/***** Question #3 *****/
void printCharacterCountsOfEachLine(FILE *file) {
    int count = 0;
    char currentChar;
    while ((currentChar = fgetc(file)) != EOF) {
        count++;
        if (currentChar == '\n') {
            printf("%d\n", count - 1);
            count = 0;
        }
    }
    if (count != 0) {
        printf("%d\n", count);
    }    
}

void printFileLineCharacterCount(char *fileName) {
    FILE *file = fopen(fileName, "r");
    if (file == NULL) {
        perror("#Error: Could not open the file for reading.");
        exit(FILE_NOT_FOUND);
    }
    printCharacterCountsOfEachLine(file);
    fclose(file);
}

void createNewFileWithGivenContents(char *newFileName, char *contents) {
    FILE *newFile = fopen(newFileName, "w");
    if (newFile == NULL) {
        perror("#Error: Could not create a file.");
        exit(FILE_NOT_CREATED);
    }
    fprintf(newFile, "%s", contents);
    fclose(newFile);
}

/***** Question #4 *****/
struct LinkNode {
    int data;
    struct LinkNode *next;
};

typedef struct LinkNode * Link;

Link createNode(int data) {
    Link link = (Link) malloc(sizeof(struct LinkNode));
    if (!link) {
        perror("#Error: failed to allocate memory.");
        exit(FAIL_ALLOC_MEM);
    }
    link->data = data;
    link->next = NULL;
    return link;
}

Link createNodeWithNextNode(int data, Link next) {
    Link link = createNode(data);
    link->next = next;
    return link;
}

void push(Link *head, int data) {
    Link newHead = createNodeWithNextNode(data, *head);
    *head = newHead;
}

void addElementToSortedLinkedList(Link *head, int data) {
    if (!*head) {
        *head = createNode(data);
        return;
    }
    if (!(*head)->next && (*head)->data < data) {
        Link newNode = createNode(data);
        (*head)->next = newNode;
    } else if (!(*head)->next) {
        push(head, data);
    }
    if (data <= (*head)->next->data) {
        Link newNode = createNodeWithNextNode(data, (*head)->next);
        (*head)->next = newNode;
        return;
    }
    addElementToSortedLinkedList(&(*head)->next, data);
}

void printLinkedList(Link head) {
    if (!head) {
        printf("\n");
        return;
    }
    printf("%d", head->data);
    if (head->next) {
        printf("->");
    }
    printLinkedList(head->next);
}

void freeLinkedAllLists(Link head) {
    if (!head) {
        return;
    }
    Link oldNode = head;
    head = head->next;
    free(oldNode);
    freeLinkedAllLists(head);
}

/***** Question #5 *****/
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

void freeTree(TreeNode root) {
    if (!root) {
        return;
    }
    freeTree(root->right);
    freeTree(root->left);
    free(root);
}

void findMaxNode(TreeNode root, TreeNode *maxNode) {
    if (!root) {
        return;
    }
    if (root->data > (*maxNode)->data) {
        (*maxNode) = root;
    }
    findMaxNode(root->left, maxNode);
    findMaxNode(root->right, maxNode);
}

TreeNode findMaxNodeInBinaryTree(TreeNode root) {
    if (!root) {
        perror("#Error: empty root is passed as an argument.");
        exit(EMPTY_ROOT_PASSED);
    }
    TreeNode maxNode = root;
    findMaxNode(root, &maxNode);
    return maxNode;
}

int main() {
    // Question #2 Tests
    printf("––– Question #2 Test –––\n");
    const int size = 5;

    int integerArray[size] = {10, 1, -2, 5, 7};
    printf("Expect True: %s\n", areElementsInGenericArrayUnique(integerArray, size, sizeof(int), areIntegersSame) ? "True" : "False");

    char charArray[size] = {'o', 'l', 'l', 'e', 'H'};
    printf("Expect False: %s\n", areElementsInGenericArrayUnique(charArray, size, sizeof(char), areCharsSame) ? "True" : "False");

    double doubleArray[size] = {1.44, 0.55, 3.22, 4.11, 2.33};
    printf("Expect True: %s\n", areElementsInGenericArrayUnique(doubleArray, size, sizeof(double), areDoublesSame) ? "True" : "False");

    char *stringArray[size] = {"why", "why", "does", "not", "work"};
    printf("Expect False: %s\n", areElementsInGenericArrayUnique(stringArray, size, sizeof(char *), areStringsSame) ? "True" : "False");

    int emptyIntegerArray[0];
    printf("Expect True: %s\n", areElementsInGenericArrayUnique(emptyIntegerArray, 0, sizeof(int), areIntegersSame) ? "True" : "False");


    // Question #3 Tests
    printf("\n––– Question #3 Test –––\n");
    printf("Test with given example:\n");
    char *testString = "This is a text file.\nThis is a line in the text file.\nC is the best programming language ever\n";
    createNewFileWithGivenContents("testTextFile.txt", testString);
    printFileLineCharacterCount("testTextFile.txt");

    printf("Test with empty lines:\n");
    char *testStringEmptyLines = "\n\n\nThis is fourth line.";
    createNewFileWithGivenContents("testTextFileEmptyLines.txt", testStringEmptyLines);
    printFileLineCharacterCount("testTextFileEmptyLines.txt");



    // Question #4 Tests
    printf("\n––– Question #4 Test –––\n");
    Link firstTestHead = NULL;
    addElementToSortedLinkedList(&firstTestHead, 1);
    addElementToSortedLinkedList(&firstTestHead, 2);
    addElementToSortedLinkedList(&firstTestHead, 7);
    addElementToSortedLinkedList(&firstTestHead, 10);
    printf("Before add 5:  ");
    printLinkedList(firstTestHead);

    addElementToSortedLinkedList(&firstTestHead, 5);
    printf("After add 5:   ");
    printLinkedList(firstTestHead);

    freeLinkedAllLists(firstTestHead);


    Link secondTestHead = NULL;
    addElementToSortedLinkedList(&secondTestHead, 1);
    printf("\nBefore add 7:  ");
    printLinkedList(secondTestHead);

    addElementToSortedLinkedList(&secondTestHead, 7);
    printf("After add 7:   ");
    printLinkedList(secondTestHead);

    freeLinkedAllLists(secondTestHead);


    Link thirdTestHead = NULL;
    addElementToSortedLinkedList(&thirdTestHead, 5);
    printf("\nBefore add 3:  ");
    printLinkedList(thirdTestHead);

    addElementToSortedLinkedList(&thirdTestHead, 3);
    printf("After add 3:   ");
    printLinkedList(thirdTestHead);

    freeLinkedAllLists(thirdTestHead);


    // Question #5 Tests
    printf("\n––– Question #5 Test –––\n");
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

    TreeNode maxOfManyLeavesTree = findMaxNodeInBinaryTree(manyLeavesTree);
    printf("Max Node of manyLeavesTree (expect 12): %d\n", maxOfManyLeavesTree->data);
    freeTree(manyLeavesTree);


    /*
              4
             / \
            /   \
           5     2
          /
         /
        1
    */
    TreeNode oneLineTree_1 = createTreeNode(1);
    TreeNode oneLineTree_5 = createTreeNodeWithChildren(5, oneLineTree_1, NULL);
    TreeNode oneLineTree_2 = createTreeNode(2);
    TreeNode oneLineTree = createTreeNodeWithChildren(4, oneLineTree_5, oneLineTree_2);

    TreeNode maxOfOneLineTree = findMaxNodeInBinaryTree(oneLineTree);
    printf("Max Node of oneLineTree    (expect 5):  %d\n", maxOfOneLineTree->data);
    freeTree(oneLineTree);


    TreeNode oneNodeTree = NULL;
    oneNodeTree = insert(oneNodeTree, 1);

    TreeNode maxOfOneNodeTree = findMaxNodeInBinaryTree(oneNodeTree);
    printf("Max Node of oneNodeTree    (expect 1):  %d\n", maxOfOneNodeTree->data);
    freeTree(oneNodeTree);

    return 0;
}
