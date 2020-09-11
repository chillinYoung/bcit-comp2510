#include <stdio.h>
#include <stdbool.h>
#include <string.h>

int findMax(void *first, void *second) {
    if (*(int *) first > *(int *) second) {
        return *(int *) first;
    }
    return *(int *) second;
}

// Answer from Seyed in exercise #1
int findMaxOfThree(void *a, void *b, void *c, bool (*compare)(void *, void*)) {
    if (compare(a, b)) {
        if (compare(a, c)) {
            return 1;
        }
        return 3;
    }
    if (compare(b, c)) {
        return 2;
    }
    return 3;
}

bool intCompare(void *a, void *b) {
    int firstValue = *(int *)a;
    int secondValue = *(int *)b;
    return (firstValue > secondValue);
}

bool stringCompare(void *a, void *b) {
    char * firstValue = *(char **)a;
    char * secondValue = *(char **)b;
    return strcmp(firstValue, secondValue) > 0;
}

// Hard Answer from Seyed
void printArray(void *array, size_t numberOfElements, size_t sizeOfElements, void (*printElement)(void *)) {
    if (numberOfElements == 0) {
        printf("[]\n");
        return;
    }
    printf("[");
    for (int i = 0; i < numberOfElements - 1; i++) {
        printElement((char *)array + i*sizeOfElements);
        printf(", ");
    }
    printElement((char *)array + (numberOfElements - 1)* sizeOfElements);
    printf("]\n");
}

void printIntegerElement(void *element) {
    printf("%d", *(int *)element);
}

int main() {
    // Easy
    int first = 2;
    int second = 5;
    printf("Max: %d\n", findMax(&first, &second)); 

    // Medium
    char *string1 = "Seyed";
    char *string2 = "Javadi";
    char *string3 = "C";
    printf("Max of three index: %d\n", findMaxOfThree(&string1, &string2, &string3, stringCompare));

    // Hard from Seyed
    int integerArray[5] = {1, -10, 5, 3, 4};
    printArray(integerArray, 5, sizeof(int), printIntegerElement);
    return 0;
}
