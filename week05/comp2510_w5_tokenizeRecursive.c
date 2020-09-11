/*
 * COMP 2510
 * tokenize functions from Seyed
 * Oct 8, 2020
 */

#include <stdio.h>
#include <string.h>

#define MAX_WORD_LENGTH 20
#define MAX_NUMBER_OF_WORDS 100
#define SPACE_CHARACTER ' '

char *moveToBeginningOfNextToken(char *inputString) {
    while (*inputString && *inputString == SPACE_CHARACTER) {
        inputString++;
    }
    return inputString;
}
int getCurrentTokenSize(char *inputString) {
    int tokenLength = 0;
    while (*inputString && *inputString++ != SPACE_CHARACTER) {
        tokenLength++;
    }
    return tokenLength;
}
int tokenize(char * paragraph, char tokens[MAX_NUMBER_OF_WORDS][MAX_WORD_LENGTH]) {
    paragraph = moveToBeginningOfNextToken(paragraph);
    if (!*paragraph) {
        return 0;
    }
    int firstWordSize = getCurrentTokenSize(paragraph);
    strncpy(tokens[0], paragraph, firstWordSize);
    tokens[0][firstWordSize] = 0;
    paragraph += firstWordSize;
    return 1 + tokenize(paragraph, tokens + 1);
}

int main() {
    
}
