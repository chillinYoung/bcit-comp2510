/*
 * COMP 2510 Assignment #5
 *
 * Young Kim(A01087377)
 * Oct 16, 2020
 */

#include <stdio.h>

#define mystery(x) ((((x) - 1) & (x)) == 0)

int midpoint_bad(int x, int y) {
    return (x + y) / 2;
}

int midpoint_better(int x, int y) {
    return x + ((y - x) / 2);
  }

int midpoint_knuth(int x, int y) {
    return (x & y) + ((x ^ y) >> 1);
}



int main() {
   printf("BAD: %d\n", midpoint_bad(2140000000, 2147483000));
   printf("BAD neg: %d\n", midpoint_bad(-2140000000, -2147483000));
   printf("BETTER: %d\n", midpoint_better(2140000000, 2147483000));
   printf("BETTER neg: %d\n", midpoint_better(-2140000000, -2147483000));
   printf("KNUTH: %d\n", midpoint_knuth(1790000000, 2007423000));
   printf("KNUTH neg: %d\n", midpoint_knuth(-2147000000, -1575921000));
   printf("KNUTH one neg: %d\n", midpoint_knuth(1734123000, -2121210000));
}
