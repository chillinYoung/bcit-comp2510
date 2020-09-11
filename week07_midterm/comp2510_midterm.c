/*
 * COMP 2510 Midterm Exam
 *
 * Young Kim(A01087377)
 * Oct 22, 2020
 */
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define EMPTY_CHAR ' '
#define MAX_NUMBER_OF_LINES 200
#define MAX_NUMBER_OF_NAME_CHAR 50
#define FULL_SCORE 100
#define TEN 10
// ERROR CODE
#define INVALID_ARGUMENTS 1
#define FILE_NOT_FOUND 2

int getOddPositionedDigit(int number, int digitPosition) {
    if (number == 0) {
        return 0;
    }
    int remainder = number % (TEN);
    int nextNum = number / (TEN * TEN);
    int newNum = remainder * digitPosition;
    return newNum + getOddPositionedDigit(nextNum, digitPosition * TEN);
}

int getOddPositionedDigits(int number) {
    return getOddPositionedDigit(number, 1);
}

void countCharFrequency(int countArray[], char *inputString) {
    while (*inputString) {
        if (*inputString != EMPTY_CHAR) {
            countArray[*inputString] += 1;
        }
        inputString++;
    }
}

void printCharacterFrequency(char *inputString) {
    int countArray[('z'+1)] = { 0 };
    countCharFrequency(countArray, inputString);
    for (int i = 0; i < ('z'+1); i++) {    // for (int i = 'A'; i <= 'z'; i++)
        if (countArray[i] > 0) {
            printf("%c: %d\n", i, countArray[i]);
        }
    }
}

int bitFun(int positiveNum) {
    if (positiveNum < 0) {
        perror("#Error: Given number is a negative number.");
        exit(INVALID_ARGUMENTS);
    }
    int onMask = 6;
    int offMask = 8;
    int newNum = positiveNum | onMask;
    if (newNum & offMask) {
        newNum -= offMask;
    }
    return newNum;
}
// // Answer from Seyed
// unsigned int bitFun(unsigned int number) {
//     return (number | 6u) & ~8u;
// }

/*
Question #5

This mystery function determines if input string has only integer digits
and returns a boolean value for it.
Since the ASCII number of char '0' to '9' is same in integer value (0 to 9),
it is possible to check if the char is a number between 0 and 9.
However, whether it has only digits or digits + chars (excluding it doesn't have any digits in it),
mystery function catenates the given number and the numbers in input string as an integer
UNTIL the next char in input string is non-digit value.
If the input string starts with the non-digit, the final *number will be empty.

name: catenateNumbers()
*/
bool mystery(char *string , int *number) {
    if (!*string) {
        return true;
    }
    if (*string > '9' || *string < '0') {
        return false;
    }
    *number *= 10;
    *number += (*string - '0');
    return mystery(string + 1, number);
}

void printTopStudents(int score, int scoreArray[], int numOfStudent,
                      char names[MAX_NUMBER_OF_LINES][MAX_NUMBER_OF_NAME_CHAR]) {
    if (score < 0) {
        return;
    }
    for (int i = 0; i < numOfStudent; i++) {
        if (scoreArray[i] == score) {
            printf("%s", names[i]);
            printf(" %d\n", scoreArray[i]);
        }
    }
    printTopStudents(score - 1, scoreArray, numOfStudent, names);
}

void getNameAndScoreFromFile(char *fileName, int scoreArray[], int *numOfStudent,
                             char names[MAX_NUMBER_OF_LINES][MAX_NUMBER_OF_NAME_CHAR]) {
    FILE *file = fopen(fileName, "r");
    if (file == NULL) {
        perror("#Error: Could not open the file for reading.");
        exit(FILE_NOT_FOUND);
    }
    char name[MAX_NUMBER_OF_NAME_CHAR];
    int score;
    while (fscanf(file, "%s %d\n", name, &score) > 0) {
        scoreArray[*numOfStudent] = score;
        for (int i = 0; i < strlen(name); i++) {
            names[*numOfStudent][i] = name[i];
        }
        names[*numOfStudent][strlen(name)] = '\0';
        *numOfStudent += 1;
    }
    fclose(file);
}

void topStudents(char *fileName) {
    int scoreArray[MAX_NUMBER_OF_LINES] = { 0 };
    char names[MAX_NUMBER_OF_LINES][MAX_NUMBER_OF_NAME_CHAR] = { };
    int numOfStudent = 0;
    getNameAndScoreFromFile(fileName, scoreArray, &numOfStudent, names);
    printTopStudents(FULL_SCORE, scoreArray, numOfStudent, names);
}

/*
int main() {
    // Test for Qustion #4
    topStudents("input.txt");

    // // Test for Qustion #1
    // printf("89201 -> %d\n", getOddPositionedDigits(89201));
    // printf("-123 -> %d\n", getOddPositionedDigits(-123));
    // printf("20 -> %d\n", getOddPositionedDigits(20));
    // printf("87654321 -> %d\n", getOddPositionedDigits(87654321));

    // // Test for Question #3
    // printf("9 -> %d\n", bitFun(9));
    // printf("0 -> %d\n", bitFun(0));
    // printf("17 -> %d\n", bitFun(17));
    // printf("31 -> %d\n", bitFun(31));

    // // Test for Question #2
    // char *testString = "I really like C";
    // printCharacterFrequency(testString);

    return 0;
}
*/

/* Test main function from the marker. */
void test_q1() {
    int test_cases[] = { -1, 1, 2, 123, 234, 89201 };
    int test_results[] = { -1, 1, 2, 13, 24, 821};
    for (int i = 0; i < 6; i++) {
        int result = getOddPositionedDigits(test_cases[i]);
        if (result != test_results[i]) {
            printf("q1: failed test %d\n", i);
        }
    }
}
void test_q2() {
    char * test_cases[] = {
            "z", // z : 1
            "AA", // A : 2
            "ABC", // A : 1, B : 1, C : 1
            "AABBCC", // A : 2, B : 2, C : 2
            "AB AC CB D", // A : 2, B : 2, C : 2, D : 1
            "abcde fghi abfg hihihihi!]]" // a : 2, b : 2, c : 1, d : 1, e : 1, f : 2, g : 2, h : 5, i : 5
    };
    for (int i = 0; i < 6; i++) {
        printf("\nq2: test %d\n", i + 1);
        printCharacterFrequency(test_cases[i]);
    }
}
void test_q3() {
    unsigned int test_cases[] = { 9, 15, 7, 0, 31};
    unsigned int test_results[] = { 7, 7, 7, 6, 23};
    for (int i = 0; i < 5; i++) {
        unsigned int result = bitFun(test_cases[i]);
        if (result != test_results[i]) {
            printf("q3: failed test %d\n", i);
        }
    }
}
void test_q4() {
    char * test_files[] = {
            "empty",
            "1_row",
            "5_row_different",
            "5_row_2_same",
            "file_does_not_exist"
    };
    for (int i = 0; i < 5; i++) {
        printf("\nFILE %s\n", test_files[i]);
        topStudents(test_files[i]);
    }
}
int main() {
    test_q1();
    test_q2();
    test_q3();
    // puts("\nq4\n");
    // test_q4();
    return 0;
}
