/*
 * COMP 2510 Assignment #4
 *
 * Young Kim(A01087377)
 * Oct 7, 2020
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_LINE_SIZE 1000
#define NEG_NUM -1
#define NUMBER_OF_ARGUMENTS 2
// error handling constants
#define FILE_NOT_FOUND 1
#define WORD_NOT_GIVEN 2
#define INVALID_NUMBER_OF_ARGUMENTS 3


bool doesStringStartWith(char *string, char *word) {
    if (!*word) {
        return true;
    }
    if (!*string) {
        return false;
    }
    return (*string == *word) && doesStringStartWith(string + 1, word + 1);
}

int countCharUntilFindWord(char *line, char *word) {
    if (!*line) {
        return 1;
    }
    if (*line == *word && doesStringStartWith(line, word)) {
        return 1;
    }
    return 1 + countCharUntilFindWord(line + 1, word);
}

int findPositionOfWord(char *line, char *word) {
    int result = countCharUntilFindWord(line, word);
    if (result > strlen(line)) {
        return NEG_NUM;
    }
    return result;
}

void searchWordInLinesAndPrintPosition(FILE *file, char *word) {
    char line[MAX_LINE_SIZE];
    int lineCount = 1;
    int wordPositionInLine = NEG_NUM;
    while (fgets(line, MAX_LINE_SIZE, file) != NULL && wordPositionInLine == NEG_NUM) {
        wordPositionInLine = findPositionOfWord(line, word);
        if (wordPositionInLine >= 0) {
            printf("Line: %d, character: %d\n", lineCount, wordPositionInLine);
        }
        lineCount++;
    }
    if (wordPositionInLine == NEG_NUM) {
        printf("Not found!\n");
    }
}

void searchWordInFileAndPrintResult(char *fileName, char *word) {
    FILE *file = fopen(fileName, "r");
    if (file == NULL) {
        perror("#Error: Could not open file for reading.");
        exit(FILE_NOT_FOUND);
    }
    if (word == NULL) {
        perror("#Error: Word to find is not given.");
        exit(WORD_NOT_GIVEN);
    }
    searchWordInLinesAndPrintPosition(file, word);
    fclose(file);
}

int main(int argc, char *argv[]) {
    if (argc != (NUMBER_OF_ARGUMENTS + 1)) {
        perror("#Error: Need exactly one arguments.");
        exit(INVALID_NUMBER_OF_ARGUMENTS);
    }
    searchWordInFileAndPrintResult(argv[1], argv[2]);
    
    return 0;
}
