/*
 * COMP 2510 Lab #10
 *
 * Young Kim(A01087377)
 * Nov 13, 2020
 */
# include <stdio.h>
# include <stdlib.h>

// ERROR CODES
#define FAIL_ALLOC_MEM 1
#define EMPTY_LIST_PASSED 2

struct Node {
    int data;
    struct Node *next;
};

typedef struct Node *Link;

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

void errorIfPointerIsNull(Link *pointer) {
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

void errorIfEmtpyListPassed(Link head) {
    if (!head) {
        perror("#Error: empty list is passed to function.");
        exit(EMPTY_LIST_PASSED);
    }
}

int pop(Link *head) {
    errorIfEmtpyListPassed(*head);
    int data = (*head)->data;
    Link oldHead = *head;
    *head = (*head)->next;
    free(oldHead);
    return data;
}

void freeLinkedAllLists(Link head) {
    while (head->next) {
        Link oldNode = head;
        head = head->next;
        free(oldNode);
    }
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

Link copyListReverse(Link head) {
    if (!head) {
        return NULL;
    }
    Link headCopy = copyList(head);
    Link copyReverseHead = createNode(pop(&headCopy));
    while (headCopy) {
        push(&copyReverseHead, pop(&headCopy));
    }
    return copyReverseHead;
}

int main() {
    Link inputList = NULL;
    push(&inputList, 4);
    push(&inputList, 3);
    push(&inputList, 2);
    push(&inputList, 1);
    printf("Input List: ");
    printLinkedList(inputList);

    Link copy = copyList(inputList);
    printf("Copy: ");
    printLinkedList(copy);

    Link copyReverse = copyListReverse(inputList);
    printf("Copy Reverse: ");
    printLinkedList(copyReverse);
    
    printf("Input List: ");
    printLinkedList(inputList);

    freeLinkedAllLists(inputList);
    freeLinkedAllLists(copy);
    freeLinkedAllLists(copyReverse);
}
