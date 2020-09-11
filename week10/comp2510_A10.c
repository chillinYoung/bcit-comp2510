/*
 * COMP 2510 Week10 Assignment
 *
 * Young Kim(A01087377)
 * Nov 8, 2020
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// ERROR CODE
#define FAIL_ALLOC_MEM 1

struct memBlockNode {
    bool isHole;
    int processId;
    int base;
    int limit;
    struct memBlockNode *next;
};

typedef struct memBlockNode *MemBlock;

void errorIfPointerIsNull(MemBlock *pointer) {
    if (pointer == NULL) {
        perror("#Error: failed to allocate memory.");
        exit(FAIL_ALLOC_MEM);
    }
}

MemBlock createNode(bool isHole, int processId, int base, int limit) {
    MemBlock memBlock = (MemBlock) malloc(sizeof(struct memBlockNode));
    errorIfPointerIsNull(&memBlock);
    memBlock->isHole = isHole;
    memBlock->processId = processId;
    memBlock->base = base;
    memBlock->limit = limit;
    memBlock->next = NULL;
    return memBlock;
}

MemBlock createNodeWithNextNode(bool isHole, int processId, int base, int limit, MemBlock next) {
    MemBlock memBlock = createNode(isHole, processId, base, limit);
    memBlock->next = next;
    return memBlock;
}

bool areTwoConsecutiveHolesFromThisHead(MemBlock head) {
    if (head->isHole && head->next->isHole) {
        return true;
    }
    return false;
}

void mergeFreeBlocks(MemBlock head) {
    if (!head || !head->next) {
        return;
    }
    if (areTwoConsecutiveHolesFromThisHead(head)) {
        head->limit = head->limit + head->next->limit;
        MemBlock oldNode = head->next;
        head->next = head->next->next;
        free(oldNode);
        mergeFreeBlocks(head);
    } else {
        mergeFreeBlocks(head->next);
    }
}

int compactBlocks(MemBlock *head, int nextBase) {
    if (!*head) {
        return 0;
    }
    int holeLimit = 0;
    if ((*head)->isHole) {
        holeLimit = (*head)->limit;
        MemBlock oldNode = *head;
        *head = (*head)->next;
        free(oldNode);
        return holeLimit + compactBlocks(head, nextBase);
    }
    (*head)->base = nextBase;
    nextBase = (*head)->base + (*head)->limit;
    return holeLimit + compactBlocks(&(*head)->next, nextBase);

}

MemBlock getTail(MemBlock head) {
    if (!head) {
        return NULL;
    }
    if (!head->next) {
        return head;
    }
    return getTail(head->next);
}

void addHoleAtLast(MemBlock *head, int limit) {
    if (!*head) {
        MemBlock newTail = createNode(true, -1, 0, limit);
        *head = newTail;
        return;
    }
    MemBlock currentTail = getTail(*head);
    MemBlock newTail = createNode(true, -1, currentTail->base + currentTail->limit, limit);
    currentTail->next = newTail;
}

void compaction(MemBlock *head) {
    int holeLimit = compactBlocks(head, 0);
    if (holeLimit > 0) {
        addHoleAtLast(head, holeLimit);
    }
}

void printMemoryNode(MemBlock head, int counter) {
    if (!head) {
        return;
    }
    if (head->isHole) {
        printf("Node %d: H (Hole), base = %d, limit = %d\n", counter, head->base, head->limit);
    } else {
        printf("Node %d: P%d, base = %d, limit = %d\n", counter, head->processId, head->base, head->limit);
    }
    printMemoryNode(head->next, counter + 1);
}

void printMemory(MemBlock head) {
    printMemoryNode(head, 1);
}

void freeLinkedAllLists(MemBlock head) {
    if (!head) {
        return;
    }
    MemBlock oldNode = head;
    head = head->next;
    free(oldNode);
    freeLinkedAllLists(head);
}

/* This function is used only for test cases in the main function */
void push(MemBlock *head, bool isHole, int processId, int base, int limit) {
    MemBlock newHead = createNodeWithNextNode(isHole, processId, base, limit, *head);
    *head = newHead;
}

int main() {
    // test
    MemBlock testHead = NULL;
    push(&testHead, true, -1, 27, 5);
    push(&testHead, true, -1, 26, 1);
    push(&testHead, false, 3, 16, 10);
    push(&testHead, true, -1, 15, 1);
    push(&testHead, true, -1, 11, 4);
    push(&testHead, true, -1, 7, 4);
    push(&testHead, false, 2, 6, 1);
    push(&testHead, false, 1, 1, 5);
    push(&testHead, true, -1, 0, 1);
    
    printf("––– Input List –––\n");
    printMemory(testHead);
    printf("––– Merge Test –––\n");
    mergeFreeBlocks(testHead);
    printMemory(testHead);
    printf("––– Compaction Test –––\n");
    compaction(&testHead);
    printMemory(testHead);

    freeLinkedAllLists(testHead);

    return 0;
}
