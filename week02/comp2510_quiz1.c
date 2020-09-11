/*
 * Young Kim (A01087377)
 *
 * COMP 2510 Quiz 1
 * Sep 17, 2020
 */

#include <stdio.h>

int findDifference(int firstArray[], int firstSize, int secondArray[], int secondSize) {

    int count = 0;
    for (int i = 0; i < firstSize; i++) {
        for (int j = 0; j < secondSize; j++) {

            if (firstArray[i] == secondArray[j]) {
                j = secondSize;
            } else if (j == (secondSize - 1)) {
                printf("%d\n", firstArray[i]);
                count++;
            }
        }
    }
    return count;
}

int main() {
    int first[] = {1, 2, 3, 4, 5};
    int second[] = {7, 2, 3, 10, 11, 12};
    findDifference(first, 5, second, 6);

    return 0;
}
