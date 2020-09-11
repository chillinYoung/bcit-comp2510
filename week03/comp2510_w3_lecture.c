//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//
//int main() {
//    char ageString[3];
//    // long age;
//    // printf("your age: ");
//    scanf("%s", ageString);
//    printf("Hah??? %s\n", ageString);
//    // age = strtol(ageString, NULL, 10);
//    // printf("Hello, %ld\n", age);
//
//    printf("%p\n", ageString);
//
//    char *newStr = ageString;
//    printf("%p\n", newStr);
//
//    printf("%lu\n", strlen(ageString));
//    printf("%lu\n", strlen(newStr));
//    while (*newStr) {
//        printf("%c\n", *newStr);
//        newStr++;
//    }
//    printf("TEST\n");
//
//    while (*ageString) {
//        printf("%c\n", *ageString);
//        ageString++;
//    }
//
//    return 0;
//}
//






/*
#include <stdio.h>

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

int main() {
    char *testString = "This is test.";
    printUpperString(testString);
}
*/




/*
#include <stdio.h>
#include <stdbool.h>


bool isSumOfArrayElementsEqualTo(int elements[], int size, int sum) {
    if (size == 1) {
        return !(sum-elements[0]);
    }
    return isSumOfArrayElementsEqualTo(elements, size - 1, sum - elements[size-1]);
}

int main() {
    int elements[] = {1, 3, 5, 7, 9, 11, 13};    // 49
    bool result = isSumOfArrayElementsEqualTo(elements, 7, 49);
    printf("Result: %d\n", result);
}
*/
