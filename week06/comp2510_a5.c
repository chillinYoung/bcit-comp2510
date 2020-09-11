/*
 * COMP 2510 Assignment #5
 *
 * Young Kim(A01087377)
 * Oct 16, 2020
 */

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_NUMBER_OF_LINES 20
#define MAX_NUMBER_OF_ELEMENTS_ON_EACH_LINE 50
#define NUMBER_OF_ARGUMENTS 1
#define ACTUAL_START_LINE 2
#define NEG_NUM -1
// Error handling constants
#define INVALID_NUMBER_OF_ARGUMENTS 1
#define FILE_NOT_FOUND 2

bool hasNumberInArray(int number, int arrayB[], int arrayBSize) {
    if (!arrayBSize) {
        return false;
    }
    if (number == *arrayB) {
        *arrayB = NEG_NUM;
        return true;
    }
    return hasNumberInArray(number, arrayB + 1, arrayBSize - 1);
}

bool compareTwoArrays(int arrayA[], int arrayB[], int numOfColumns) {
    int arrayBCopy[numOfColumns];
    for (int i = 0; i < numOfColumns; i++) {
        arrayBCopy[i] = *arrayB++;
    }
    for (int i = 0; i < numOfColumns; i++) {
        if (!hasNumberInArray(arrayA[i], arrayBCopy, numOfColumns)) {
            return false;
        }
    }
    return true;
}

bool findAnagramAndPrintResult(int numOfRows, int numOfColumns,
                               int numbers[MAX_NUMBER_OF_LINES][MAX_NUMBER_OF_ELEMENTS_ON_EACH_LINE]) {
    for (int lineA = 0; lineA < numOfRows; lineA++) {
        for (int lineB = lineA + 1; lineB < numOfRows; lineB++) {
            if (compareTwoArrays(numbers[lineA], numbers[lineB], numOfColumns)) {
                printf("Found: lines %d and %d\n", lineA + ACTUAL_START_LINE, lineB + ACTUAL_START_LINE);
                return true;
            }
        }
    }
    printf("Not found\n");
    return false;
}

void storeNumsToArray(FILE *file, int numOfColumns, int numbers[MAX_NUMBER_OF_ELEMENTS_ON_EACH_LINE]) {
    int num;
    for (int i = 0; i < numOfColumns; i++) {
        fscanf(file, "%d", &num);
        numbers[i] = num;
    }
}

void copyFileContentsToArray(char *fileName, int *numOfRows, int *numOfColumns,
                             int numbers[MAX_NUMBER_OF_LINES][MAX_NUMBER_OF_ELEMENTS_ON_EACH_LINE]) {
    FILE *file = fopen(fileName, "r");
    if (file == NULL) {
        perror("#Error: Could not open the file for reading.");
        exit(FILE_NOT_FOUND);
    }
    fscanf(file, "%d %d\n", numOfRows, numOfColumns);
    for (int i = 0; i < *numOfRows; i++) {
        storeNumsToArray(file, *numOfColumns, numbers[i]);
    }
    fclose(file);
}

void findAnagrams(char *fileName) {
    int numOfRows;
    int numOfColumns;
    int numbers[MAX_NUMBER_OF_LINES][MAX_NUMBER_OF_ELEMENTS_ON_EACH_LINE] = {};
    copyFileContentsToArray(fileName, &numOfRows, &numOfColumns, numbers);
    findAnagramAndPrintResult(numOfRows, numOfColumns, numbers);
}

int main(int argc, char *argv[]) {
    if (argc != (NUMBER_OF_ARGUMENTS + 1)) {
        perror("#Error: Need exactly one arguments.");
        exit(INVALID_NUMBER_OF_ARGUMENTS);
    }
    findAnagrams(argv[1]);
    return 0;
}

