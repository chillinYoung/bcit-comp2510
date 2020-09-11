#include <stdio.h>
#include <stdbool.h>

struct date {
    int year;
    int month;
    int day;
};

// mine
/*
bool ifFirstDateBeforeSecondDate(struct date firstDate, struct date secondDate) {
    if (firstDate.year > secondDate.year) {
        return false;
    }
    if (firstDate.year < secondDate.year) {
        return true;
    }
    if (firstDate.month > secondDate.month) {
        return false;
    }
    if (firstDate.month < secondDate.month) {
        return true;
    }
    return (firstDate.day >= secondDate.day);
}

void printDatesHowFar(struct date firstDate, struct date secondDate) {
    if (!ifFirstDateBeforeSecondDate(firstDate, secondDate)) {
        return printDatesHowFar(secondDate, firstDate);
    }
    int year = secondDate.year - firstDate.year;
    int month = secondDate.month - firstDate.month;
    int day = secondDate.day - firstDate.day;
    if (day < 0) {
        day += 30;
        month--;
    }
    if (month < 0) {
        month += 12;
        year--;
    }
    printf("It is far %d years, %d months, and %d days.\n", year, month, day);
}
*/

// solution from slides → segmentation error for the same date hahaha
bool isFirstDateAfterSecondDate(struct date firstDate, struct date secondDate) {
    if (firstDate.year < secondDate.year) {
        return false;
    }
    if (firstDate.year > secondDate.year) {
        return true;
    }
    if (firstDate.month < secondDate.month) {
        return false;
    }
    if (firstDate.month > secondDate.month) {
        return true;
    }
    return firstDate.day > secondDate.day;
}

void printDateDelta(struct date firstDate, struct date secondDate) {
    if (!isFirstDateAfterSecondDate(firstDate, secondDate)) {
        return printDateDelta(secondDate, firstDate);
    }
    struct date delta;
    delta.year = firstDate.year - secondDate.year;
    delta.month = firstDate.month - secondDate.month;
    delta.day = firstDate.day - secondDate.day;
    if (delta.day < 0) {
        delta.day += 30;
        delta.month--; }
    if (delta.month < 0) {
        delta.month += 12; delta.year--;
    }
    printf("Delta = %d years and %d months and %d days\n", delta.year, delta.month, delta.day);
}

int main() {
    struct date first = {2020, 3, 2};
    // struct date second = {2019, 4, 29};
    struct date second = {2020, 3, 2};
    // printDatesHowFar(first, second);
    printDateDelta(first, second);
    // bool result = ifFirstDateBeforeSecondDate(first, second);
    // printf("%s\n", result ? "True" : "False");
    // bool result2 = ifFirstDateBeforeSecondDate(second, first);
    // printf("%s\n", result2 ? "True" : "False");
}
