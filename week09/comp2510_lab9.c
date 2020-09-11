/*
 * COMP 2510 Lab #9
 *
 * Young Kim(A01087377)
 * Nov 6, 2020
 */
# include <stdio.h>
# include <stdbool.h>
# include <string.h>

void swap(void *first, void *second, size_t numberOfBytes) {
    char temp[numberOfBytes];
    memcpy(temp, first, numberOfBytes);
    memcpy(first, second, numberOfBytes);
    memcpy(second, temp, numberOfBytes);
}

bool intCompare(void *first, void *second) {
    int *firstInt = (int *) first;
    int *secondInt = (int *) second;
    return *firstInt > *secondInt;
}

bool charCompare(void *first, void *second) {
    char *firstChar = (char *)first;
    char *secondChar = (char *)second;
    return *firstChar > *secondChar;
}

bool doubleCompare(void *first, void *second) {
    double *firstDouble = (double *)first;
    double *secondDouble = (double *)second;
    return *firstDouble > *secondDouble;
}

bool stringCompare(void *first, void *second) {
    char *firstString = *(char **)first;
    char *secondString = *(char **)second;
    return strcmp(firstString, secondString) > 0;
}

void *findNthElement(void *array, int num, size_t sizeOfEachElementInBytes) {
    return (char *)array + (num - 1) * sizeOfEachElementInBytes;
}

void arrayBubbleSort(void *array, size_t size, size_t sizeOfEachElementInBytes, bool (*compare)(void *, void *)) {
    while (true) {
        bool swapped = false;
        void *firstElement;
        void *secondElement;
        for (int i = 1; i < size; i++) {
            firstElement = findNthElement(array, i, sizeOfEachElementInBytes);
            secondElement = findNthElement(array, i + 1, sizeOfEachElementInBytes);
            if (compare(firstElement, secondElement)) {
                swapped = true;
                swap(firstElement, secondElement, sizeOfEachElementInBytes);
            }
        }
        if (!swapped) {
            return;
        }
    }
}

void printArray(void *array, size_t numberOfElements, size_t sizeOfElements, void (*printElement)(void *)) {
    if (numberOfElements == 0) {
        printf("\n");
        return;
    }
    for (int i = 0; i < numberOfElements ; i++) {
        printf("A[%d] = ", i);
        printElement((char *)array + (i * sizeOfElements));
        printf("\n");
    }
}

void printIntegerElement(void *element) {
        printf("%d", *(int *)element);
}

void printCharElement(void *element) {
        printf("%c", *(char *)element);
}

void printDoubleElement(void *element) {
        printf("%lf", *(double *)element);
}

void printStringElement(void *element) {
        printf("%s", *(char **)element);
}

int main() {
    const int size = 5;

    int integerArray[size] = {10, 1, -2, 5, 7};
    arrayBubbleSort(integerArray, size, sizeof(int), intCompare);
    printArray(integerArray, size, sizeof(int), printIntegerElement);

    char charArray[size] = {'o', 'l', 'l', 'e', 'H'};
    arrayBubbleSort(charArray, size, sizeof(char), charCompare);
    printArray(charArray, size, sizeof(char), printCharElement);

    double doubleArray[size] = {1.44, 0.55, 3.22, 4.11, 2.33};
    arrayBubbleSort(doubleArray, size, sizeof(double), doubleCompare);
    printArray(doubleArray, size, sizeof(double), printDoubleElement);

    char *stringArray[size] = {"why", "this", "does", "not", "work"};
    arrayBubbleSort(stringArray, size, sizeof(stringArray[0]), stringCompare);
    printArray(stringArray, size, sizeof(stringArray[0]), printStringElement);

    return 0;
}


