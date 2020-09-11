#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void errorIfPointerIsNull(char *pointer) {
    if (pointer == NULL) {
        perror("#Error: failed to allocate memory.");
        exit(1);
    }
}

char *append(char *data[], int count) {
    size_t allCount = 0;
    for (int i = 0; i < count; i++) {
        allCount += strlen(data[i]);
    }
    char *result = (char *) malloc(allCount + 1);
    errorIfPointerIsNull(result);
    strcpy(result, "");
    for (int i = 0; i < count; i++) {
        strcat(result, data[i]);
    }
    result[allCount] = 0;
    return result;
}

int main() {
    char *string[4] = {"What ", "am ", "I ", "diong?"};
    char *returned = append(string, 4);
    printf("Returned: %s\n", returned);
    free(returned);
}


/*
#include <stdio.h>
#include <stdlib.h>

int main() {
    char myName[10] = "Seyed";
    free(myName);

    return 0;
}
*/


/*
#include <stdio.h>
#include <stdlib.h>

int main() {
    int *array = (int *) malloc(10 * sizeof(int));
    int *copy = array;
    free(copy);
    printf("=== after free copy in main() ===\n");
    free(array);
    return 0;
}
*/


/*
#include <stdio.h>
#include <stdlib.h>

#define INIT_ARRAY_SIZE 10
// ERROR CODE
#define FAIL_ALLOC_MEMORY 1

int takeNumbersFromUser() {
    int number;
    printf("Enter a number: \n");
    scanf("%d", &number);
    return number;
}

void printArrayElements(int userInputs[]) {
    printf("The numbers you entered: \n");
    while(*userInputs >= 0) {
        printf("%d\n", *userInputs);
        userInputs++;
    }
}

void errorIfArrayNull(int *numArray) {
    if (numArray == NULL) {
        perror("#Error: Failed to allocate memory.");
        exit(FAIL_ALLOC_MEMORY);
    }
}

int *increaseArraySizeTwiceIfNeeded(int *numArray, int usedLen, int *currentSize) {
    if (usedLen < *currentSize) {
        return numArray;
    }
    *currentSize += *currentSize;
    numArray = (int *) realloc(numArray, *currentSize);
    errorIfArrayNull(numArray);
    return numArray;
}

void takeStorePrintNumbers() {
    int *numArray = (int *) malloc(INIT_ARRAY_SIZE * sizeof(int));
    errorIfArrayNull(numArray);
    int arraySize = INIT_ARRAY_SIZE;
    int number = 0;
    int count = 0;
    while (number >= 0) {
        numArray = increaseArraySizeTwiceIfNeeded(numArray, count, &arraySize);
        number = takeNumbersFromUser();
        numArray[count] = number;
        count++;
    }
    printArrayElements(numArray);
    free(numArray);
}

int main() {
    takeStorePrintNumbers();
    return 0;
}
*/


/*
#include <stdio.h>

#define max(a, b) (((a) > (b)) ? (a) : (b))
#define IS_POWER_OF_TWO(x) ((((x) - 1) & (x)) == 0)
#define IS_POWER_OF_TWO_BAD(x) ((x - 1) & x) == 0

int main() {
    printf("%d\n", IS_POWER_OF_TWO(16) + 1);
    printf("%d\n\n", IS_POWER_OF_TWO_BAD(16) + 1);    // ((16 - 1) & 16) == 0 + 1
    // int x = 5;
    // int y = 10;
    // printf("max = %d\n", max(x++, y--));
    // printf("max → x = %d, y = %d\n\n", x, y);
}
*/
