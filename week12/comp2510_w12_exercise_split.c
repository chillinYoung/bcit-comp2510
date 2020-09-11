/*
 * Write a function that splits a linked list in half.
 * If the number of elements is odd, first half would have one more element than the second half.
 * Be careful when designing the signature of your function:
 * - What parameters should this function take?
 * - What should the output be?
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

void freeLinkedAllLists(Link head) {
    if (!head) {
        return;
    }
    Link oldNode = head;
    head = head->next;
    free(oldNode);
    freeLinkedAllLists(head);
}

int getNumberOfNodes(Link head) {
    if (!head) {
        return 0;
    }
    return 1 + getNumberOfNodes(head->next);
}

// 심심할때 완성해보기 -> recursive
void splitReverse(Link inputHead, Link *firstHalf, Link *secondHalf, int numOfnodes) {
    if (!inputHead) {
        return;
    }
}

void split(Link inputHead, Link *firstHalf, Link *secondHalf) {
    int numOfNodes = getNumberOfNodes(inputHead);
    int counter = 0;
    Link reverseCopy = copyListReverse(inputHead);
    while (reverseCopy) {
        if (counter < (numOfNodes / 2)) {
            push(secondHalf, pop(&reverseCopy));
        } else {
            push(firstHalf, pop(&reverseCopy));
        }
        counter++;
    }
    freeLinkedAllLists(reverseCopy);
}

int main() {
    Link inputList = NULL;
    // push(&inputList, 4);
    // push(&inputList, 3);
    push(&inputList, 2);
    push(&inputList, 1);
    push(&inputList, 0);
    printf("Input List: ");
    printLinkedList(inputList);

    Link firstHalf = NULL;
    Link secondHalf = NULL;
    split(inputList, &firstHalf, &secondHalf);
    printf("First List: ");
    printLinkedList(firstHalf);
    printf("Second List: ");
    printLinkedList(secondHalf);

    freeLinkedAllLists(inputList);
    freeLinkedAllLists(firstHalf);
    freeLinkedAllLists(secondHalf);
}
