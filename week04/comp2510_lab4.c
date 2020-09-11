/*
 * COMP 2510 Week 4 Lab
 *
 * Young Kim(A01087377)
 * Oct 2, 2020
 */

#include <stdio.h>
#include <stdlib.h>

#define FILE_NAME_LENGTH 1000
#define MAX_COLUMNS 10

int fromBinary(int *binaryArray, int size) {
    if (!size) {
        return 0;
    }
    int number = fromBinary(binaryArray, size - 1);
    return 2 * number + binaryArray[size - 1];
}

char *getFileName(char *fileName) {
    printf("Please enter the file name including .txt: ");
    scanf("%s", fileName);
    return fileName;
}

void readNextNumberFromFile(FILE * file, int binaryArray[MAX_COLUMNS], int numberOfColumns) {
    int nextBinaryNum;
    for (int i = 0; i < numberOfColumns; i++) {
        fscanf(file, "%d", &nextBinaryNum);
        binaryArray[i] = nextBinaryNum;
    }
    printf("%d\n", fromBinary(binaryArray, numberOfColumns));
}

void processFile(char *fileName) {
    FILE *file = fopen(fileName, "r");
    if (file == NULL) {
        perror("Could not open file for reading.");
        exit(1);
    }
    int numberOfRows;
    int numberOfColumn;
    fscanf(file, "%d %d", &numberOfRows, &numberOfColumn);

    int binaryArray[MAX_COLUMNS];
    for (int i = 0; i < numberOfRows; i++) {
        readNextNumberFromFile(file, binaryArray, numberOfColumn);
    }

    fclose(file);
}

int main() {
    char fileName[FILE_NAME_LENGTH];
    getFileName(fileName);
    processFile(fileName);

    return 0;
}
