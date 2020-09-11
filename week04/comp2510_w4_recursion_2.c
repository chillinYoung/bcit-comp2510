/*
 * Write a recursive function that checks whether or not an array of integers has any duplicates.
 */

#include <stdio.h>
#include <stdbool.h>

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
    printf("%d\n", *array);
    return doesArrayContainElement(array + 1, size - 1, *array) || doesArrayHaveDuplicates(array + 1, size - 1);
}

int main() {
    int elements[] = {1, 3, 4, 2, 5, 3};
    bool result = doesArrayHaveDuplicates(elements, 6);
    printf("%s\n", result ? "True" : "False");
}


