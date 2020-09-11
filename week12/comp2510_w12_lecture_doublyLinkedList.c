#include <stdio.h>
#include <stdlib.h>

// ERROR CODE
#define FAIL_ALLOC_MEM 1
#define EMPTY_LIST_PASSED 2
#define EMPTY_NODE_PASSED 3


struct Node {
    int data;
    struct Node *next;
    struct Node *prev;
};

typedef struct Node* DLink;

DLink createNode(int data, DLink next, DLink prev) {
    DLink link = (DLink) malloc(sizeof(struct Node));
    if (link == NULL) {
        perror("#Error: failed to allocate memory.");
        exit(FAIL_ALLOC_MEM);
    }
    link->data = data;
    link->next = next;
    link->prev = prev;
    return link;
}

void printLinkedList(DLink head) {
    if (!head) {
        printf("\n");
        return;
    }
    printf("%d", head->data);
    if (head->next) {
        printf("<->");
    }
    printLinkedList(head->next);
}

void push(DLink *head, int data) {
    DLink newHead = createNode(data, *head, NULL);
    if (*head) {
        (*head)->prev = newHead;
    }
    *head = newHead;
}

int pop(DLink *head) {
    if (!*head) {
        perror("#Error: empty list is passed to pop function.");
        exit(EMPTY_LIST_PASSED);
    }
    int data = (*head)->data;
    DLink oldHead = *head;
    *head = (*head)->next;
    if (*head) {
        (*head)->prev = NULL;
    }
    free(oldHead);
    return data;
}

int removeNode(DLink *node) {
    if (!*node) {
        perror("#Error: empty node is passed to removeNode function.");
        exit(EMPTY_NODE_PASSED);
    }
    if (!(*node)->prev) {
        return pop(node);
    }
    if (!(*node)->next) {
        (*node)->prev->next = NULL;
        int data = (*node)->data;
        free(*node);
        return data;
    }
    int data = (*node)->data;
    DLink nextNode = (*node)->next;
    DLink prevNode = (*node)->prev;
    free(*node);
    prevNode->next = nextNode;
    nextNode->prev = prevNode;
    return data;
}

void freeLinkedAllLists(DLink head) {
    while (head->next) {
        DLink oldNode = head;
        head = head->next;
        free(oldNode);
    }
}

int main () {
    /*DLink node_1 = createNode(1, NULL, NULL);
    DLink node_2 = createNode(2, NULL, NULL);
    DLink node_3 = createNode(3, NULL, NULL);
    node_1->next = node_2;
    node_2->prev = node_1;
    node_2->next = node_3;
    node_3->prev = node_2;
    printLinkedList(node_1);*/

    DLink head = NULL;
    push(&head, 3);
    push(&head, 2);
    push(&head, 1);
    printLinkedList(head);

    /*int node_1_data = pop(&head);
    printLinkedList(head);
    int node_2_data = pop(&head);
    printLinkedList(head);
    int node_3_data = pop(&head);
    printLinkedList(head);
    printf("%d %d %d\n", node_1_data, node_2_data, node_3_data);*/

    int data = removeNode(&(head->next));
    printf("Data of node removed: %d\n", data);
    printLinkedList(head);

    freeLinkedAllLists(head);

    return 0;
}


