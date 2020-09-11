/*
 * DESCRIPTION: 
 *     COMP 2510 Week1 Exercise
 * 
 * NOTE:
 *     Write a program with a function named: printArray
 *     Signature for printArray: void printArray(int elements[], int size);
 *     Given an array like [-1, 10, 0, 4],
 *     the function should print the array in the output.
 *
 * AUTHOR: Young Kim
 * DATE: Sep 10, 2020
 */

#include <stdio.h>

void printArray(int elements[], int size) {
 
    printf("[");

    for (int i = 0; i < size; i++) {
        printf("%d", elements[i]);
        printf(i == (size - 1) ? "" : ", ");
    }

    printf("]\n");
}

int main() {
    int array[] = {-1, 10, 0, 4};
    int size = 4;
    printArray(array, size);
}
