/*
 * COMP 2510 Lab #12
 *
 * Young Kim(A01087377)
 * Nov 27, 2020
 */
#include <stdio.h>
#include <stdlib.h>

#define TENTH 10
// ERROR CODE
#define FAIL_ALLOC_MEM 1
#define NULL_LIST 2

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

DLink getTail(DLink node) {
    if (!node) {
        return NULL;
    }
    if (!(node->next)) {
        return node;
    }
    return getTail(node->next);
}

void sumCalc(DLink *result, DLink firstTail, DLink secondTail, int carryNum) {
    if (!firstTail && !secondTail && carryNum == 0) {
        return;
    }
    int sum = carryNum + (firstTail ? firstTail->data : 0) + (secondTail ? secondTail->data : 0);
    push(result, sum % TENTH);
    sumCalc(result, (firstTail ? firstTail->prev : NULL), (secondTail ? secondTail->prev : NULL), sum / TENTH);
}

DLink sum(DLink firstNumber, DLink secondNumber) {
    if (!firstNumber || !secondNumber) {
        perror("#Error: at least one null list is passed to sum function.");
        exit(NULL_LIST);
    }
    DLink result = NULL;
    sumCalc(&result, getTail(firstNumber), getTail(secondNumber), 0);
    return result;
}

void freeLinkedAllLists(DLink head) {
    if (!head) {
        return;
    }
    DLink oldNode = head;
    head = head->next;
    free(oldNode);
    freeLinkedAllLists(head);
}

int main() {
    printf("––– Test1 ––– (no carry, different digits)\n");
    DLink first1 = NULL;
    push(&first1, 0);
    push(&first1, 1);
    printf("firstNumber:  ");
    printLinkedList(first1);

    DLink second1 = NULL;
    push(&second1, 3);
    printf("secondNumber: ");
    printLinkedList(second1);

    printf("sum:          ");
    DLink sumResult1 = sum(first1, second1);
    printLinkedList(sumResult1);

    freeLinkedAllLists(first1);
    freeLinkedAllLists(second1);
    freeLinkedAllLists(sumResult1);

    printf("\n––– Test2 ––– (increasing digits by carry, different digits)\n");
    DLink first2 = NULL;
    push(&first2, 1);
    push(&first2, 0);
    push(&first2, 9);
    printf("firstNumber:  ");
    printLinkedList(first2);

    DLink second2 = NULL;
    push(&second2, 9);
    push(&second2, 9);
    printf("secondNumber: ");
    printLinkedList(second2);

    printf("sum:          ");
    DLink sumResult2 = sum(first2, second2);
    printLinkedList(sumResult2);

    freeLinkedAllLists(first2);
    freeLinkedAllLists(second2);
    freeLinkedAllLists(sumResult2);

    printf("\n––– Test3 ––– (no carry, same digits)\n");
    DLink first3 = NULL;
    push(&first3, 3);
    push(&first3, 2);
    push(&first3, 1);
    printf("firstNumber:  ");
    printLinkedList(first3);

    DLink second3 = NULL;
    push(&second3, 1);
    push(&second3, 2);
    push(&second3, 3);
    printf("secondNumber: ");
    printLinkedList(second3);

    printf("sum:          ");
    DLink sumResult3 = sum(first3, second3);
    printLinkedList(sumResult3);

    freeLinkedAllLists(first3);
    freeLinkedAllLists(second3);
    freeLinkedAllLists(sumResult3);


    printf("\n––– Test4 ––– (both have one zero)\n");
    DLink first4 = NULL;
    push(&first4, 0);
    printf("firstNumber:  ");
    printLinkedList(first4);

    DLink second4 = NULL;
    push(&second4, 0);
    printf("secondNumber: ");
    printLinkedList(second4);

    printf("sum:          ");
    DLink sumResult4 = sum(first4, second4);
    printLinkedList(sumResult4);

    freeLinkedAllLists(first4);
    freeLinkedAllLists(second4);
    freeLinkedAllLists(sumResult4);
    
    printf("\n––– Test5 ––– (one of the lists is zero)\n");
    DLink first5 = NULL;
    push(&first5, 0);
    printf("firstNumber:  ");
    printLinkedList(first5);

    DLink second5 = NULL;
    push(&second5, 5);
    push(&second5, 3);
    push(&second5, 1);
    printf("secondNumber: ");
    printLinkedList(second5);

    printf("sum:          ");
    DLink sumResult5 = sum(first5, second5);
    printLinkedList(sumResult5);

    freeLinkedAllLists(first5);
    freeLinkedAllLists(second5);
    freeLinkedAllLists(sumResult5);

    printf("\n––– Test6 ––– (one of the lists is null: should have an error)\n");
    DLink first6 = NULL;
    printf("firstNumber:  ");
    printLinkedList(first6);

    DLink second6 = NULL;
    push(&second6, 6);
    push(&second6, 3);
    push(&second6, 1);
    printf("secondNumber: ");
    printLinkedList(second6);

    printf("sum:          ");
    DLink sumResult6 = sum(first6, second6);
    printLinkedList(sumResult6);

    freeLinkedAllLists(second6);
    freeLinkedAllLists(sumResult6);

    return 0;
}
