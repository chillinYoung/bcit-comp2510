#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

bool integerCompare(void *firstPointer, void *secondPointer) {
    int *firstIntegerPointer = (int *)firstPointer;
    int *secondIntegerPointer = (int *)secondPointer;
    return *firstIntegerPointer > *secondIntegerPointer;
}

void *findElement(void *array, int index, size_t sizeOfEachElementInBytes) {
    return (char *)array + index * sizeOfEachElementInBytes;
}

void addElementsToArray(void *source, size_t sourceSize, int sourceFromIndex, size_t numberOfBytesPerElement, void *destination,
                        int destinationFromIndex) {
    while (sourceFromIndex < sourceSize) {
        void *firstElement = findElement(source, sourceFromIndex, numberOfBytesPerElement);
        void *combinedElement = findElement(destination, destinationFromIndex, numberOfBytesPerElement);
        memcpy(combinedElement, firstElement, numberOfBytesPerElement);
        sourceFromIndex++;
    }
}

void *merge(void *firstArray, size_t firstSize, void *secondArray, size_t secondSize, size_t numberOfBytesPerElement, bool (*compare)(void *,void *)) {
    void *combined = malloc((firstSize + secondSize) * numberOfBytesPerElement);
    int firstIndex = 0, secondIndex = 0, combinedIndex = 0;
    while ((firstIndex < firstSize) && (secondIndex < secondSize)) {
        void *firstElement = findElement(firstArray, firstIndex, numberOfBytesPerElement);
        void *secondElement = findElement(secondArray, secondIndex, numberOfBytesPerElement);
        void *combinedElement = findElement(combined, combinedIndex, numberOfBytesPerElement);
        if (compare(firstElement, secondElement)) {
            memcpy(combinedElement, secondElement, numberOfBytesPerElement);
            secondIndex++;
        } else {
            memcpy(combinedElement, firstElement, numberOfBytesPerElement);
            firstIndex++;
        }
        combinedIndex++;
    }

    addElementsToArray(firstArray, firstSize, firstIndex, numberOfBytesPerElement, combined, combinedIndex);
    addElementsToArray(secondArray, secondSize, secondIndex, numberOfBytesPerElement, combined, combinedIndex);
    return combined;
}

int main() {
    int firstArray[5] = {1, 15, 20, 35, 40};
    int secondArray[4] = {-1, 18, 19, 37};
    int *mergedArray = (int *) merge(firstArray, 5, secondArray, 4, sizeof(int), integerCompare);
    for (int i = 0; i < 9; i++) {
        printf("mergedArray[%d] = %d\n", i, mergedArray[i]);
    }
    free(mergedArray);
    return 0;
}

