/*
 * COMP 2510 - Week #3 Lab
 *
 * Young Kim (A01087377)
 * Sep 26, 2020
 */

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

void findMinDistance(char *inputString) {
    char *string = inputString;

    int interval = 1;
    bool finishLoop = (strlen(inputString) < 2);
    bool foundRepeats = false;
    while (!finishLoop) {
        // check if same letters are found
        if (*string == string[interval]) {
            finishLoop = true;
            foundRepeats = true;
            printf("Repeated char = %c, min distance = %d\n", *string, interval - 1);
        }
        // if pointer reached at the end, put it back to the start point
        if (interval == strlen(string) - 1) {
            interval++;
            finishLoop = (interval >= strlen(inputString));
            string = inputString;
        } else {
            string++;
        }
    }
    if (!foundRepeats) {
        printf("No repeats found!\n");   
    }
}

int main() {
    // Tests
    char *example1 = "Hi there, how is it going?";
    printf("Example #1: '%s'\n", example1);
    findMinDistance(example1);
    puts("");

    char *example2 = "Hello there, how is it going?";
    printf("Example #2: '%s'\n", example2);
    findMinDistance(example2);
    puts("");

    char *example3 = "123";
    printf("Example #3: '%s'\n", example3);
    findMinDistance(example3);
    puts("");

    char *endToEnd = "AbcdefghijklmnopA";
    printf("End to end: '%s'\n", endToEnd);
    findMinDistance(endToEnd);
    puts("");

    char *emptyString = "";
    printf("Empty string: '%s'\n", emptyString);
    findMinDistance(emptyString);
    puts("");

    char *oneWhiteSpace = " ";
    printf("One white space: '%s'\n", oneWhiteSpace);
    findMinDistance(oneWhiteSpace);
    puts("");

    char *twoWhiteSpaces = "  ";
    printf("Two white spaces: '%s'\n", twoWhiteSpaces);
    findMinDistance(twoWhiteSpaces);
    puts("");

    return 0;
}
