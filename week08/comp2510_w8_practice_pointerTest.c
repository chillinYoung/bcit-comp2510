#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *createNewPointer() {
    char *result = (char *) malloc(10);
    return result;
}

char *newPointers() {
    char *result = createNewPointer();
    result = createNewPointer();
    result = createNewPointer();
    return result;
}

int main() {
    char *test1 = newPointers();
    
}
