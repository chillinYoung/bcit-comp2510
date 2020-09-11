/*
 * Hard – Write a program that takes an array of integers and a number.
 * The function should then find out if any five elements of that array
 * add up to this number. For any five elements of the array that sum up
 * to this number, print a row on the output.
 * You must not use five nested loops! Here is an Example:
 * 
 * Array: [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
 * Number = 18
 * Output:
 *     1+2+3+4+8
 *     1+2+3+5+7
 *     1+2+4+5+6
 */

#include <stdio.h>

#define OUTPUT_SIZE 5

void findElements(int Number, int *inputArray, int inputSize, int outputArray[], int outputSize) {
    if (outputSize == 0 && inputSize == 0) {
        return;
    }
    if ()
}

int main() {
    int inputArray[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int outputArray[OUTPUT_SIZE];
    int numberToFind = 18;
    findElements(numberToFind, inputArray, 10, outputArray, OUTPUT_SIZE);
}
