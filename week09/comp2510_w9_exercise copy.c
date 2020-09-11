#include <stdio.h>
#include <stdbool.h>

void function(int integer) {
    printf("Int: %d\n", integer);
}

void funcRun(int integer, void (*funcToPointer)(int)) {
    funcToPointer(integer);
}

int findLargestOne(void *first, void *second, void *third) {
    int largest;
    if (*(int *) first > *(int *) second) {
        largest = *(int *)first;
    } else {
        largest = *(int *)second;
    }
    if (largest < *(int *) third) {
        largest = *(int *)third;
    }
    return largest;
}

// Answer from Seyed
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

bool strCompare(void *a, void *b) {
    char firstValue = *(char *)a;
    char secondValue = *(char *)b;
    return (firstValue > secondValue);
}

// Hard Answer from Seyed
#include <stdio.h>
void *findNthElement(void *array, int n, size_t sizeOfEachElementInBytes) {
    return (char *)array + (n - 1) * sizeOfEachElementInBytes;
}

int main() {
    // Easy
    // funcRun(3, function);

    // Medium
    // int first = 1;
    // int second = 2;
    // int third = 3;
    // printf("largest: %d\n", findLargestOne(&first, &second, &third)); 
    // char firstC = 'a';
    // char secondC = 'b';
    // char thirdC = 'c';
    // printf("largest: %d\n", findLargestOne(&firstC, &secondC, &thirdC));

    // Medium from Seyed
    int num1 = 10;
    int num2 = 45;
    int num3 = 30;
    printf("Max of three index: (%d, %d, %d) = %d\n", num1, num2 , num3, findMaxOfThree(&num1, &num2, &num3, intCompare));
    return 0;

    // Hard from Seyed
    int array[3] = {1, 2, 3};
    int *pointerToSecondElement = (int *) findNthElement(array, 2, sizeof(int));
    printf("Second element = %d\n", *pointerToSecondElement);
    char *name = "Seyed";
    char *pointerToThirdCharacter = (char *) findNthElement(name, 3, sizeof(char));
    printf("Third character of name: %c\n", *pointerToThirdCharacter);
    return 0;
}
