/*
 * COMP 2510 - Assignment Weeks 2 and 3
 *
 * Young Kim (A01087377)
 * Oct 1, 2020
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define MAX_WORD_LENGTH 20
#define MAX_NUMBER_OF_WORDS 100
#define SPACE_CHAR ' '
// Error constants
#define EXCEED_MAX_WORD_LENGTH 1

char *moveToBeginningOfNextToken(char *inputString) {
    while(*inputString == SPACE_CHAR) {
        inputString++;
    }
    return inputString;
}

int getCurrentTokenSize(char *inputString) {
    int counter = 0;
    while(*inputString && *inputString != SPACE_CHAR) {
        counter++;
        inputString++;
    }
    if (counter > MAX_WORD_LENGTH - 1) {
        perror("# ERROR: given string has the word exceeded the maximum length!");
        exit(EXCEED_MAX_WORD_LENGTH);
    }
    return counter;
}

int tokenize(char *paragraph, char tokens[MAX_NUMBER_OF_WORDS][MAX_WORD_LENGTH]) {
    int tokenCount = 0;
    int tokenSize;

    while(*paragraph) {
        paragraph = moveToBeginningOfNextToken(paragraph);
        tokenSize = getCurrentTokenSize(paragraph);

        for (int i = 0; i < tokenSize; i++) {
            tokens[tokenCount][i] = *paragraph;
            paragraph++;
        }
        tokens[tokenCount][tokenSize] = '\0';
        // not to increase tokenCount for tokenSize zero
        tokenCount = (tokenSize) ? tokenCount + 1 : tokenCount;
    }

    return tokenCount;
}

int getNumberOfWordsForNextLine(char tokens[MAX_NUMBER_OF_WORDS][MAX_WORD_LENGTH],
                                int numberOfWordsProcessedSoFar, int totalNumberOfWords, int lineLength) {
    int numOfWords = 0;
    int numOfChar = 0;
    int estimatedSum;

    for(int i = numberOfWordsProcessedSoFar; i < totalNumberOfWords; i++) {
        estimatedSum = numOfChar + numOfWords + strlen(tokens[i]);

        if (estimatedSum <= lineLength) {
            numOfWords++;
            numOfChar += strlen(tokens[i]);
        } else {
            i = totalNumberOfWords;
        }
    }
    return numOfWords;
}

void printWordAndSpaces(char word[MAX_WORD_LENGTH], int numberOfSpaces) {
    printf("%s", word);
    for (int i = 0; i < numberOfSpaces; i++) {
        printf("%c", SPACE_CHAR);
    }
}

void formatAndPrintCurrentLine(char tokens[MAX_NUMBER_OF_WORDS][MAX_WORD_LENGTH],
                               int numberOfWordsProcessedSoFar, int numberOfWordsOnNextLine, int lineLength) {
    int numOfChar = 0;
    for (int i = 0; i < numberOfWordsOnNextLine; i++) {
        numOfChar += strlen(tokens[numberOfWordsProcessedSoFar + i]);
    }
    // initialize number of whitespace array to zero
    int numOfSpace[numberOfWordsOnNextLine];
    for (int i = 0; i < numberOfWordsOnNextLine; i++) {
        numOfSpace[i] = 0;
    }
    // distribute whitespaces
    if (numberOfWordsOnNextLine == 1) {
        numOfSpace[0] = lineLength - numOfChar;
    } else {
        for (int i = 0; i < lineLength - numOfChar; i++) {
            numOfSpace[i % (numberOfWordsOnNextLine - 1)] += 1;
        }        
    }
    // print current line
    for (int i = 0; i < numberOfWordsOnNextLine; i++) {
        printWordAndSpaces(tokens[numberOfWordsProcessedSoFar + i], numOfSpace[i]);
    }
    printf("\n");
}

void formatAndPrintWords(char tokens[MAX_NUMBER_OF_WORDS][MAX_WORD_LENGTH],
                         int totalNumberOfWords, int lineLength) {
    int numberOfWordsProcessedSoFar = 0;
    int numberOfWordsOnNextLine;

    while (numberOfWordsProcessedSoFar < totalNumberOfWords) {
        numberOfWordsOnNextLine = getNumberOfWordsForNextLine(tokens, numberOfWordsProcessedSoFar,
                                                              totalNumberOfWords, lineLength);
        formatAndPrintCurrentLine(tokens, numberOfWordsProcessedSoFar, numberOfWordsOnNextLine, lineLength);
        numberOfWordsProcessedSoFar += numberOfWordsOnNextLine;
    }
}

void formatAndPrintParagraph(char *paragraph, int lineLength) {
    char tokens[MAX_NUMBER_OF_WORDS][MAX_WORD_LENGTH];
    int tokenCount = tokenize(paragraph, tokens);
    formatAndPrintWords(tokens, tokenCount, lineLength);

}

int main() {
    char paragraph[] = "         Hi everyone. This is          the 2nd assignment. Please make sure you start early as this is going to take some time!     ";
    char tokens[MAX_NUMBER_OF_WORDS][MAX_WORD_LENGTH];
    int numberOfTokens = tokenize(paragraph, tokens);
    assert(numberOfTokens == 21);
    for (int i = 0; i < numberOfTokens; i++) {
        printf("Token[%d] = %s\n", i, tokens[i]);
    }
    printf("\n");
    formatAndPrintParagraph(paragraph, 11);
    printf("\n");
    formatAndPrintParagraph(paragraph, 23);
    printf("\n");
    formatAndPrintParagraph(paragraph, 35);
    printf("\n");
    formatAndPrintParagraph(paragraph, 100);
    printf("\n");
    formatAndPrintParagraph(paragraph, 120);
    return 0;
}
