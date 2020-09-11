/*
 * COMP 2510 Lab #5
 * 
 * Young Kim (A01087377)
 * Oct 9,
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUMBER_OF_ARGUMENTS 2
// error handling constants
#define FILE_NOT_FOUND 1
#define NEW_NAME_NOT_GIVEN 2
#define FILE_NOT_CREATED 3
#define INVALID_NUMBER_OF_ARGUMENTS 4

void createNewFileWithGivenFileContents(FILE *originFile, char *newFileName) {
    FILE *newFile = fopen(newFileName, "w");
    if (newFile == NULL) {
        perror("Could not create the file for writing.");
        exit(FILE_NOT_CREATED);
    }
    char originChar;
    while ((originChar = fgetc(originFile)) != EOF) {
        fprintf(newFile, "%c", originChar);
    }
    fclose(newFile);
}

void copyFileContents(char *fileName, char *newFileName) {
    FILE *file = fopen(fileName, "r");
    if (file == NULL) {
        perror("#Error: Could not open file for reading.");
        exit(FILE_NOT_FOUND);
    }
    if (newFileName == NULL) {
        perror("#Error: New file name is not given.");
        exit(NEW_NAME_NOT_GIVEN);
    }
    createNewFileWithGivenFileContents(file, newFileName);
    fclose(file);
}

int main(int argc, char *argv[]) {
    if (argc != (NUMBER_OF_ARGUMENTS + 1)) {
        perror("#Error: Need exactly one arguments.");
        exit(INVALID_NUMBER_OF_ARGUMENTS);
    }
    copyFileContents(argv[1], argv[2]);
    return 0;
}
