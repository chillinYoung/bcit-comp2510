#include <stdio.h>

int turnOnFirstAndThirdBitFromRight(int num) {
    int mask = 5;
    return num | mask;
}

int main() {
    printf("8 → %d\n", turnOnFirstAndThirdBitFromRight(8));
    printf("0 → %d\n", turnOnFirstAndThirdBitFromRight(0));
    printf("17 → %d\n", turnOnFirstAndThirdBitFromRight(17));
    printf("29 → %d\n", turnOnFirstAndThirdBitFromRight(29));
}
