/*
 * COMP 2510 Midterm Prep
 * Function Collection from Slack
 *
 * Young Kim (A01087377)
 * Oct 21, 2020
 */

/* Feedbacks:
    - Please work on refactoring your code and cleaning it up a bit.
    - warning after you finish with printf always use \n to flush the buffer
    - warning in C use macros for constants, including characters
    - finishLoop <- this is actually a counter, bad identifier
    - use [] notation instead of moving the actual pointer,
        more legible and less prone to error
    - Missing a return 0; from your main().
    - processFile is not a good name for this function.
    - You need to check/validate argc before accessing argv elements:
        argv[1], argv[2], etc. 
        FILE_NOT_FOUND is not a good error for target file if pointer is NULL.
        The target file is expected to not exist.
    - You are not checking argc to make sure user has provided right number of args.
    - Did not state whether an anagram was found or not when there was an anagram.
    - Don't "return" a value from a void function.
    - Don't use strncat or strcat for a problem like this.
        Let the recursion take care of it for you.
*/

#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>


/*
 * Print the string without spaces.
 */
void removeSpaces(char *string) {
    while (*string && *string == ' ' && string++);
    if (!*string) {
        return;
    }
    printf("%c", *string);
    removeSpaces(string + 1);
}


/*
 * Write a function that converts all characters in a string to upper case.
 *
 * USAGE EXAMPLE
 * char *testString = "This is test.";
 * printUpperString(testString);
 */
char convertToUpper(char ch) {
    return (ch >= 'a' && ch <= 'z') ? ch - 'a' + 'A' : ch;
}

void printUpperString(char *string) {
    if (!*string) {
        puts("");
        return;
    }
    putchar(convertToUpper(*string));
    return printUpperString(++string);
}


/*
 * Write a recursive function
 * that finds the maximum element of an array of integers.
 *
 * USAGE EXAMPLE
 * int numArray[] = {0, 5, 1, 2, 6, 3};
 * int maxNum = maxElementOfArray(numArray, 6);
 * printf("%d", maxNum);
 */
int maxElementOfArray(const int numberArray[], int size) {
    if (size == 1) {
        return *numberArray;
    }
    if (*numberArray > numberArray[size - 1]) {
        return maxElementOfArray(numberArray, size - 1);
    } else {
        return maxElementOfArray(numberArray + 1, size - 1);
    }
}


/*
 * Q: How many lines of output do you expect to see for this program?
 * A: 6, empty line after
 */
void pointerAndStrlenFunction() {
    char *message = "Hello  there";
    for (int i = 0; i < strlen(message); ++i) {
        printf("%c\n", *message++);
    }
}

/*
 * Write a recursive function that counts the number of a given character
 * in a given string
 *
 * USAGE EXAMPLE
 * char * string = "Young hi young is sleepy";
 * char character = 'e';
 * int result = countNumberOfCharsInString(string, character);
 * printf("%d\n", result);
 */
int countNumberOfCharsInString(char *input, char targetCharacter) {
    if (!*input) {
        return 0;
    }
    int firstCharacterValue = (*input == targetCharacter) ? 1 : 0;
    return firstCharacterValue + countNumberOfCharsInString(input + 1, targetCharacter);
}


/*
 * Write a resursive function that checks
 * whether or not an array of integers has any duplicates.
 *
 * USAGE EXAMPLE
 * printf("Name of the program: %s\n", argv[0]);
 * if (argc != (NUMBER_OF_ARGUMENTS + 1)) {
 *     perror("Need exactly three arguments.");
 *     exit(INVALID_NUMBER_OF_ARGUMENTS);
 * }
 * doAddition(argv);
 */
bool doesArrayContainElement(int array[], int size, int element) {
    if (!size) {
        return false;
    }
    return (*array == element) || doesArrayContainElement(array + 1, size - 1, element);
}
bool doesArrayHaveDuplicates(int array[], int size) {
    if (size < 2) {
        return false;
    }
    return doesArrayContainElement(array + 1, size - 1, *array) || doesArrayHaveDuplicates(array + 1, size - 1);
}


/*
 * Example of Handling Command Line Arguments
 */
#define NUMBER_OF_ARGUMENTS 3    // 1 2 3
// ERROR CODES
#define INVALID_NUMBER_OF_ARGUMENTS 1
#define ARGUMENT_NOT_A_NUMBER 2

long convertStringArgumentToNumber(char *stringNumber) {
    char *ptr;
    long number = strtol(stringNumber, &ptr, 10);
    if (strlen(ptr) > 0) {
        char error[100];
        sprintf(error, "Argument: %s is not a number.", stringNumber);
        perror(error);
        exit(ARGUMENT_NOT_A_NUMBER);
    }
    return number;
}

void doAddition(char *argv[]) {
    long firstNumber = convertStringArgumentToNumber(argv[1]);
    long secondNumber = convertStringArgumentToNumber(argv[2]);
    long thirdNumber = convertStringArgumentToNumber(argv[3]);
    long sum = firstNumber + secondNumber + thirdNumber;
    printf("Sum = %ld\n", sum);
}


/*
 * Recursive tokenize function (Seyed's solution for Assignment 2&3)
 */
#define SPACE_CHARACTER ' '
#define MAX_WORD_LENGTH 20
#define MAX_NUMBER_OF_WORDS 100

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
    // This can be also
    // return 1 + tokenize(paragraph + firstWordSize, tokens + 1);
    paragraph += firstWordSize;
    return 1 + tokenize(paragraph, tokens + 1);
}


/*
 * Write a recursive function that cleans a string.
 * The signature of the function should be:
 * void cleanString(char * input, char * output)
 *
 * A clean string is a string where all adjacent characters
 * that are the same are reduced to a single char.
 *
 * Examples:
 *    1. “xxyyyyyyzzzzzz”→“xyz”
 *    2. “Hello Howareyou?”→“HeloHowareyou?”
 *    3. “Test”→“Test”
 *    4. “AaA”→“AaA”
*/
void cleanString(char *input, char *output) {
    if (!*input) {
        *output = 0;
        return;
    }
    output[0] = *input;
    while (*(input + 1) == *input) {
        input++;
    }
    cleanString(input + 1, output + 1);
}


/*
 * Write a function named printDigits.
 * The function takes an integer n >= 0 as the parameter.
 * It then prints n 1's, followed by n 2's, followed by n 3's followed by n 4's.
 *
 * Not allowed to use any loops (think recursive)
 * optimize your code for minimum number of recursive calls
 *
 * Examples:
 *  (a) n = 0 → Nothing is printed
 *  (b) n = 1 → Prints: 1234
 *  (c) n = 2 → Prints: 11223344
 *  (d) n = 3 → Prints: 11111222223333344444
 *
 * USAGE EXAMPLE
 * optimizedPrintDigits(10);
 */
void printDigitsWithCount(int n, int count) {
    if (n <= 0) {
        return;
    }
    int digit = (count < n) ? 1 : 2;
    printf("%d", digit);
    printDigitsWithCount(n - 1, count + 1);
    printf("%d", 5 - digit);
}
void optimizedPrintDigits(int n) {
    if (n <= 0) {
        return;
    }
    printDigitsWithCount(2 * n, 0);
}

