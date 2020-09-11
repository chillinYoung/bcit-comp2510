#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *doubleString(char *inputString) {
    char *result = (char *) malloc(2 * strlen(inputString) + 1);
    if (result == NULL) {
        perror("#Error: failed to allocate memory.");
        exit(1);
    }
    strcpy(result, "");
    for (int i = 0; i < 2; i++) {
        strcat(result, inputString);
    }
    return result;
}

int main() {
    char *test1 = doubleString("Seyed");
    printf("%s\n", test1);
    free(test1);

    char *test2 = doubleString(" Hello, there!");
    printf("%s\n", test2);
    free(test2);
}
