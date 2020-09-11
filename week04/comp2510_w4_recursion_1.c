/*
 * Write a recursive function that counts the number of a given character
 * in a given string
 */

#include <stdio.h>

int countNumberOfCharsInString(char *input, char targetCharacter) {
    if (!*input) {
        return 0;
    }
    int firstCharacterValue = (*input == targetCharacter) ? 1 : 0;
    return firstCharacterValue + countNumberOfCharsInString(input + 1, targetCharacter);
}

int main() {
    char * string = "Young hi young is sleepy";
    char character = 'e';
    int result = countNumberOfCharsInString(string, character);
    printf("%d\n", result);
}


