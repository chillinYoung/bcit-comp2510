/*
 * For a singly linked list,
 * can you write a function named getPrevious
 * which takes a node (and also the head of the list)
 * and returns the node previous to this node in the list.
 */

#include <stdio.h>
#include <stdlib.h>

// ERROR CODES
#define FAIL_ALLOC_MEM 1
#define EMPTY_LIST_PASSED 2
#define NODE_NOT_FOUND 3

struct Node {
    int data;
    struct Node *next;
};

typedef struct Node* Link;

Link createNode(int data) {
    Link link = (Link) malloc(sizeof(struct Node));
    if (!link) {
        perror("#Error: failed to allocate momery.");
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

Link getPreviousNode(Link head, Link node) {
    if (!head) {
        perror("#Error: empty list is passed to function.");
        exit(EMPTY_LIST_PASSED);
    }
    if (head == node) {
        return NULL;
    }
    if (!head->next) {
        perror("#Error: Node is not found.");
        exit(NODE_NOT_FOUND);
    }
    if (head->next == node) {
        return head;
    }
    return getPreviousNode(head->next, node);
}

int main() {
    Link node = createNodeWithNextNode(10, NULL);
    Link node2 = createNodeWithNextNode(20, node);
    Link head = createNodeWithNextNode(4, node2);
    printLinkedList(head);
    push(&head, 5);
    // 5 -> 4 -> 20 -> 10
    printLinkedList(head);
    Link prev1 = getPreviousNode(head, head);
    printf("prev1 = %s\n", (prev1 == NULL) ? "NULL" : "Not NULL");
    Link prev2 = getPreviousNode(head, head->next);
    printf("prev2 = %d\n", prev2->data);
    Link prev3 = getPreviousNode(head, head->next->next);
    printf("prev3 = %d\n", prev3->data);
    Link prev4 = getPreviousNode(head, head->next->next->next);
    printf("prev4 = %d\n", prev4->data);
    getPreviousNode(head, createNode(10));
    return 0;
}
