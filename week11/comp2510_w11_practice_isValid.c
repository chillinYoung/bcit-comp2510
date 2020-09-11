/*
 * Write a function named filter that takes a singly linked list as the input.
 * Each link in the list holds a float as the data.
 * The function should also take a pointer to a function
 * that takes a float and returns a boolean.
 * Let's call this pointer function isValid. Your function (filter) is
 * supposed to remove any link from the list which is not valid.
 * The validity of the link is determined by this:
 * - if isValid(link->data) returns true => This link is valid.
 * - if isValid(link->data) returns false => This link is not valid.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define THRESHOLD 3
// ERROR CODES
#define FAIL_ALLOC_MEM 1

struct Node {
    float data;
    struct Node *next;
};

typedef struct Node* Link;

Link createNode(float data) {
    Link link = (Link) malloc(sizeof(struct Node));
    if (!link) {
        perror("#Error: failed to allocate momery.");
        exit(FAIL_ALLOC_MEM);
    }
    link->data = data;
    link->next = NULL;
    return link;
}

Link createNodeWithNextNode(float data, Link next) {
    Link link = createNode(data);
    link->next = next;
    return link;
}

void printLinkedList(Link head) {
    if (!head) {
        printf("\n");
        return;
    }
    printf("%.2f", head->data);
    if (head->next) {
        printf("->");
    }
    printLinkedList(head->next);
}

/* Test Case 1 */
bool returnFalseAlways(float data) {
    return false;
}

/* Test Case 2 */
bool isGreaterThanThreshold(float data) {
    return (data > 3.4f);
}

void filter(Link *head, bool (*isValid)(float)) {
    if (!*head) {
        return;
    }
    if (!isValid((*head)->data)) {
        Link oldNode = *head;
        *head = (*head)->next;
        free(oldNode);
        filter(head, isValid);
    } else {
        filter(&(*head)->next, isValid);
    }
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

int main() {
    Link node_4 = createNode(5.1);
    Link node_3 = createNodeWithNextNode(4.2, node_4);
    Link node_2 = createNodeWithNextNode(3.3, node_3);
    Link node_1 = createNodeWithNextNode(2.4, node_2);
    Link head = createNodeWithNextNode(1.5, node_1);
    printf("First Test: isGreaterThanThreshold\n");
    printf("Before: ");
    printLinkedList(head);

    filter(&head, isGreaterThanThreshold);
    printf("After: ");
    printLinkedList(head);

    Link anotherNode_4 = createNode(5.1);
    Link anotherNode_3 = createNodeWithNextNode(4.2, anotherNode_4);
    Link anotherNode_2 = createNodeWithNextNode(3.3, anotherNode_3);
    Link anotherNode_1 = createNodeWithNextNode(2.4, anotherNode_2);
    Link anotherHead = createNodeWithNextNode(1.5, anotherNode_1);
    printf("\nSecond Test: returnFalseAlways\n");
    printf("Before: ");
    printLinkedList(anotherHead);

    filter(&anotherHead, returnFalseAlways);
    printf("After: ");
    printLinkedList(anotherHead);

    freeLinkedAllLists(anotherHead);
    return 0;
}
