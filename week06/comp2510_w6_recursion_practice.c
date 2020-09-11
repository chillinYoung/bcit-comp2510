#include <stdio.h>

void printDigitsWithCount(int n, int count) {
    if (n <= 0) {
        return;
    }
    int digit = (count < n) ? 1 : 2;
    printf("%d", digit);
    printDigitsWithCount(n - 1, count + 1);
    printf("%d", 5 - digit);
}
void optimizedPrintDigits(int n) {
    if (n <= 0) {
        return;
    }
    printDigitsWithCount(2 * n, 0);
}
int main() {
    // optimizedPrintDigits(10);
    printDigitsWithCount(2 * 1, 0);
    return 0;
}

/*
void printOneNumber(int toPrint, int count) {
    if (count == 0) {
        // printf("\n");
        return;
    }
    if (toPrint > 4)
    printf("%d", toPrint);
    printOneNumber(toPrint, count - 1);
}

void printDigits(int number) {
    printOneNumber(1, number);
    printDigits()
}

void printDigits(int number) {
    printOneNumber(1, number);
    printOneNumber(2, number);
    printOneNumber(3, number);
    printOneNumber(4, number);
}

int main() {
    printDigits(3);
}*/
