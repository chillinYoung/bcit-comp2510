/*
 * COMP 2510 Quiz #4
 *
 * Young Kim(A01087377)
 * Nov 27, 2020
 */
#include <stdio.h>
#include <stdlib.h>

// ERROR CODE
#define FAIL_ALLOC_MEM 1

struct Node {
    int data;
    struct Node *next;
};

typedef struct Node* Link;

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

void errorIfPointerIsNull(void *pointer) {
    if (pointer == NULL) {
        perror("#Error: failed to allocate memory.");
        exit(FAIL_ALLOC_MEM);
    }
}

Link createNode(int data) {
    Link link = (Link) malloc(sizeof(struct Node));
    errorIfPointerIsNull(&link);
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

Link copyList(Link head) {
    if (!head) {
        return NULL;
    }
    Link copyHead = createNode(head->data);
    Link currentTail = copyHead;
    while (head->next) {
        head = head->next;
        Link newNode = createNode(head->data);
        currentTail->next = newNode;
        currentTail = newNode;
    }
    currentTail->next = NULL;
    return copyHead;
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

Link getTail(Link head) {
    if (!head) {
        return NULL;
    }
    if (!(head->next)) {
        return head;
    }
    return getTail(head->next);
}

Link concatenateSelf(Link head) {
    if (!head) {
        return NULL;
    }
    Link newHead = copyList(head);
    getTail(newHead)->next = copyList(head);
    return newHead;
}

int main() {
    Link test_1 = NULL;
    push(&test_1, 3);
    push(&test_1, 2);
    push(&test_1, 1);
    printf("Input: ");
    printLinkedList(test_1);
    Link testResult_1 = concatenateSelf(test_1);
    printf("Output: ");
    printLinkedList(testResult_1);

    Link test_2 = NULL;
    push(&test_2, 10);
    printf("Input: ");
    printLinkedList(test_2);
    Link testResult_2 = concatenateSelf(test_2);
    printf("Output: ");
    printLinkedList(testResult_2);

    Link test_3 = NULL;
    printf("Input: ");
    printLinkedList(test_3);
    Link testResult_3 = concatenateSelf(test_3);
    printf("Output: ");
    printLinkedList(testResult_3);

    Link test_4 = NULL;
    push(&test_4, 1);
    push(&test_4, 1);
    printf("Input: ");
    printLinkedList(test_4);
    Link testResult_4 = concatenateSelf(test_4);
    printf("Output: ");
    printLinkedList(testResult_4);

    freeLinkedAllLists(test_1);
    freeLinkedAllLists(testResult_1);
    freeLinkedAllLists(test_2);
    freeLinkedAllLists(testResult_2);
    freeLinkedAllLists(test_3);
    freeLinkedAllLists(testResult_3);
    freeLinkedAllLists(test_4);
    freeLinkedAllLists(testResult_4);

    return 0;
}
