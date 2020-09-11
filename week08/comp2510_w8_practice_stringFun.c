#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SPACE_CHAR ' '

void errorIfPointerIsNull(char *pointer) {
    if (pointer == NULL) {
        perror("#Error: failed to allocate memory.");
        exit(1);
    }
}

char *deleteSpaces(char *string) {
    char *result = (char *) malloc(strlen(string) + 1);
    errorIfPointerIsNull(result);
    int count = 0;
    while (*string) {
        if (*string != SPACE_CHAR) {
            result[count++] = *string;
        }
        string++;
    }
    result[count] = 0;
    return result;
}

char *replaceLowerCase(char *string) {
    char *result = (char *) malloc(strlen(string) + 1);
    errorIfPointerIsNull(result);
    int count = 0;
    while (*string) {
        if (*string >= 'a' && *string <= 'z') {
            result[count++] = *string - ('a'-'A');
        } else {
            result[count++] = *string;
        }
        string++;
    }
    result[count] = 0;
    return result;
}

char *duplicateAsterisks(char *string) {
    char *result = (char *) malloc(2 * strlen(string) + 1);
    errorIfPointerIsNull(result);
    int count = 0;
    while (*string) {
        result[count++] = *string;
        if (*string == '*') {
            result[count++] = '*';
        }
        string++;
    }
    result[count] = 0;
    return result;
}

char *stringFun(char *inputString) {
    char *result = deleteSpaces(inputString);
    result = replaceLowerCase(result);
    result = duplicateAsterisks(result);
    return result;
}

int main() {
    char *result1 = stringFun("  Seyed Javadi");
    printf("Result: %s\n", result1);
    free(result1);
    char *result2 = stringFun(" I * c");
    printf("Result: %s\n", result2);
    free(result2);
    char *result3 = stringFun("         ");
    printf("Result: %s\n", result3);
    free(result3);
    char *result4 = stringFun(" * * * ");
    printf("Result: %s\n", result4);
    free(result4);
}
