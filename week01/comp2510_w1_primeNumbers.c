/*
 * Young Kim
 *
 * Print all the prime numbers which are less than 1000.
 */

#include <stdio.h>
#include <math.h>
#include <stdbool.h>

#define UPPERBOUND 1000

bool isPrimeNums(int number) {
    if(number < 2) {
        return false;
    }
    for(int i = 2; i <= sqrt(number); i++) {
        if(number % i == 0) {
            return false;
        }
    }
    return true;
}

void printPrimeNums(int upBound) {
    for(int i = 2; i <= upBound; i++) {
        if(isPrimeNums(i)) {
            printf("%d\n", i);
        }
    }
}

int main() {
    printPrimeNums(UPPERBOUND);

    return 0;
}
