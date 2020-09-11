/*
 * COMP 2510 Quiz #2
 *
 * Young Kim(A01087377)
 * Oct 8, 2020
 */

#include <stdio.h>
#include <string.h>


void cleanString(char *input, char *output) {
    if (!*input) {
        *output = 0;
        return;
    }
    output[0] = *input;
    while (*input == *output) {
        input++;
    }
    cleanString(input, output + 1);
}

int main() {
    const int resultLength = 100;

    char firstString[resultLength];
    cleanString("AaA", firstString);
    printf("first = %s\n", firstString);

    char secondString[resultLength];
    cleanString("          qdjkhqkwdhaaaaaaaaaaaaaa aaaa xyz  ", secondString);
    printf("second = %s\n", secondString);

    char thirdString[resultLength];
    cleanString("", thirdString);
    printf("third = %s\n", thirdString);

    char fourthString[resultLength];
    cleanString("a a a a a a", fourthString);
    printf("fourth = %s\n", fourthString);

    char fifthString[resultLength];
    cleanString("SSSSeyed Mohammad       Javadi!!", fifthString);
    printf("fifth = %s\n", fifthString);

    return 0;
}
