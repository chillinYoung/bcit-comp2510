#include <stdio.h>
#include <stdlib.h>

int maxElementOfArray(int numberArray[], int size) {
    if (size == 1) {
        return *numberArray;
    }
    if (*numberArray > numberArray[size - 1]) {
        return maxElementOfArray(numberArray, size - 1);
    } else {
        return maxElementOfArray(numberArray + 1, size - 1);
    }
}

int main() {
    int numArray[] = {0, 5, 1, 2, 6, 3};
    int maxNum = maxElementOfArray(numArray, 6);
    printf("Final Max Number: %d\n", maxNum);
    // int *pointer = numArray;
    // printf("%d\n", *pointer);
    // pointer++;
    // printf("%d\n", *pointer);
    // printf("%d\n", pointer[1]);
    return 0;
}
