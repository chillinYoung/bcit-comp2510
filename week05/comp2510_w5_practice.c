#include <stdio.h>

#define SPACE_CHAR ' '
#define MAX_STRING_LENGTH 100

// void stringFun(char input[MAX_STRING_LENGTH], char result[MAX_STRING_LENGTH]) {
//     deleteSpaces(input);
//     replaceLowerCase(input);
//     duplicateAsterisks(input, result);
// }

void deleteSpaces(char *string, char *output) {
    printf("%s\n", output);
    while (*string) {
        if (*string != SPACE_CHAR) {
            output[0] = *string;
            output++;
        }
        string++;
    }
    output[0] = 0;
}

void replaceLowerCase(char *string, char *output) {
    while (*string) {
        if (*string >= 'a' && *string <= 'z') {
            output[0] = *string - ('a'-'A');
            output++;
        }
        string++;
    }
    output[0] = 0;
}

void duplicateAsterisks(char *string, char *output) {
    while (*string) {
        if (*string == '*') {
            output[0] = '*';
            output[1] = '*';
            output += 2;
        }
        string++;
    }
    output[0] = 0;
} 

void stringFun(char *input, char *output) {
    char spaceDeleted[MAX_STRING_LENGTH];
    deleteSpaces(input, spaceDeleted);

    char replacedToLowercase[MAX_STRING_LENGTH];
    replaceLowerCase(spaceDeleted, replacedToLowercase);

    duplicateAsterisks(replacedToLowercase, output);
}

int main() {
    char output1[MAX_STRING_LENGTH];
    stringFun("Seyed Javadi", output1);
    printf("%s\n", output1);

    char output2[MAX_STRING_LENGTH];
    stringFun("I * c", output2);
    printf("%s\n", output2);
    
    char output3[MAX_STRING_LENGTH];
    stringFun("         ", output3);
    printf("%s\n", output3);
    
    char output4[MAX_STRING_LENGTH];
    stringFun("***", output4);
    printf("%s\n", output4);
}
