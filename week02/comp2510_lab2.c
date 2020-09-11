/*
 * COMP 2510 - Week #2 Lab
 *
 * Young Kim (A01087377)
 * Sep 18, 2020
 */

#include <stdio.h>

void printTokens(char *inputString) {
    const char whiteSpace = ' ';
    char previousChar = whiteSpace;

    while(*inputString) {
        if (*inputString != whiteSpace) {
            printf("%c", *inputString);
        } else if (previousChar != whiteSpace) {
            printf("\n");
        }
        previousChar = *inputString++;
    }
    if (previousChar != whiteSpace) {
        printf("\n");
    }
}

int main() {
    char *testString = "  Hi there!   How is it     going?  ";
    printTokens(testString);
}
