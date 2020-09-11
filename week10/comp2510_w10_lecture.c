# include <stdio.h>
# include <stdlib.h>

// ERROR CODES
#define FAIL_ALLOC_MEM 1
#define EMPTY_LIST_PASSED 2
#define INVALID_POSITION_PASSED 3

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

int getLinkedListLength(Link head) {
    int length = 0;
    Link currentNode = head;
    while (currentNode) {
        currentNode = currentNode->next;
        length++;
    }
    return length;
}

int getLinkedListLengthRecursive(Link head) {
    if (!head) {
        return 0;
    }
    return 1 + getLinkedListLengthRecursive(head->next);
}

void push(Link *head, int data) {
    Link newHead = createNodeWithNextNode(data, *head);
    *head = newHead;
}

Link getTail(Link head) {
    if (!head) {
        return NULL;
    }
    if (!head->next) {
        return head;
    }
    return getTail(head->next);
}

void addLast(Link *head, int data) {
    Link newTail = createNode(data);
    if (!*head) {
        *head = newTail;
        return;
    }
    Link currentTail = getTail(*head);
    currentTail->next = newTail;
}

int removeTail(Link *head) {
    if (!*head) {
        perror("#Error: empty list is passed to removeTail function.");
        exit(EMPTY_LIST_PASSED);
    }
    Link currentNode = *head;
    if (!currentNode->next) {
        *head = NULL;
        int data = currentNode->data;
        free(currentNode);
        return data;
    }
    while(currentNode->next->next) {
        currentNode = currentNode->next;
    }
    Link oldTail = currentNode->next;
    int oldTailData = oldTail->data;
    free(oldTail);
    currentNode->next = NULL;
    return oldTailData;
}

int pop(Link *head) {
    if (!*head) {
        perror("#Error: empty list is passed to pop function");
        exit(EMPTY_LIST_PASSED);
    }
    int data = (*head)->data;
    Link oldHead = *head;
    *head = (*head)->next;
    free(oldHead);
    return data;
}

void errorIfEmtpyListPassed(Link head) {
    if (!head) {
        perror("#Error: empty list is passed to function.");
        exit(EMPTY_LIST_PASSED);
    }
}

void errorIfNodePositionInvalid(Link head, int position) {
    if (position >= getLinkedListLength(head) || position < 0) {
        perror("#Error: invalid position is passed to function.");
        exit(INVALID_POSITION_PASSED);
    }
}

Link moveToNodeAtPosition(Link head, int position) {
    Link currentNode = head;
    for (int i = 0; i < position; i++) {
        currentNode = currentNode->next;
    }
    return currentNode;
}

/* Exercise 1 */
int addElementAfterPosition(Link head, int data, int position) {
    errorIfEmtpyListPassed(head); 
    errorIfNodePositionInvalid(head, position); 
    Link currentNode = moveToNodeAtPosition(head, position);
    Link newNode = createNodeWithNextNode(data, currentNode->next);
    currentNode->next = newNode;
    return 0;
}

/* Exercise 2 */
int deleteNodeAtPosition(Link *head, int position) {
    errorIfEmtpyListPassed(*head);
    errorIfNodePositionInvalid(*head, position);
    if (position == 0) {
        return pop(head);
    }
    Link beforeNode = moveToNodeAtPosition(*head, position - 1);
    Link oldNode = beforeNode->next;
    int oldData = beforeNode->next->data;
    beforeNode->next = beforeNode->next->next;
    free(oldNode);
    return oldData;
}

int main() {
    Link head = NULL;
    addLast(&head, 4);
    addLast(&head, 20);
    addLast(&head, 10);
    addLast(&head, 100);
    printLinkedList(head);
    deleteNodeAtPosition(&head, 3);
    printLinkedList(head);

    Link head2 = NULL;
    addLast(&head2, 4);
    addLast(&head2, 20);
    addLast(&head2, 10);
    addLast(&head2, 100);
    printLinkedList(head2);
    addElementAfterPosition(head2, -7, 3);
    printLinkedList(head2);

    return 0;
}
