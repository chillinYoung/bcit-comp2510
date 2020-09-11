/*
 * COMP 2510 Quiz #3
 *
 * Young Kim(A01087377)
 * Nov 6, 2020
 */
# include <stdio.h>
# include <stdlib.h>

// ERROR CODE
#define FAILED_ALLOC_MEM 1

void errorIfPointerIsNull(int *pointer) {
    if (pointer == NULL) {
        perror("#Error: failed to allocate memory.");
        exit(FAILED_ALLOC_MEM);
    }
}

int *subtractArray(int *firstArray, int *secondArray, int size) {
    int *result = (int *) malloc(size * sizeof(int));
    errorIfPointerIsNull(result);
    for (int i = 0; i < size; i++) {
        result[i] = firstArray[i] - secondArray[i];
    }
    return result;
}

void printArray(int *aArray, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d\n", aArray[i]);
    }
}

int main() {
    int firstArray[] = {1, 2, 3, 4, 5};
    int secondArray[] = {4, 3, 2, 1, 5};
    int size = 5;
    int *result = subtractArray(firstArray, secondArray, size);
    printArray(result, size);
    free(result);
    return 0;
}
