
#include <stdio.h>

int main() {
    
}



/*
#include <stdio.h>

int main() {
    int test = 2;
    int *pointer = &test;
    int copy = test;
    int *pointer2 = &copy;

    printf("%p\n", pointer);
    printf("%p\n", pointer2);
    printf("%d\n", test);
    printf("%d\n", copy);
}

*/

/*
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(int c, char **v) {
    while (--c > 1 && !fork());
    int val = atoi(v[c]);
    sleep(val);
    printf("%d\n", val);
    waitpid(-1, NULL, 0);
    return 0;
}
*/



/*
#include <stdio.h>
    void swapPointers(int **p, int **q) {
    int *temp = *p;
    *p = *q;
    *q = temp;
}

int main() {
    int firstNumber = 1;
    int secondNumber = 2;
    int *firstPointer = &firstNumber;
    int *secondPointer = &secondNumber;
    swapPointers(&firstPointer, &secondPointer);
    printf("*firstPointer = %d, *secondPointer = %d\n", *firstPointer, *secondPointer);
    return 0;
}

*/


/*
#include <stdio.h>

void swapPointers(int *p, int *q) {
    int *temp = p;
    p = q;
    q = temp;
}

int main() {
    int firstNumber = 1;
    int secondNumber = 2;
    int *firstPointer = &firstNumber;
    int *secondPointer = &secondNumber;
    swapPointers(firstPointer, secondPointer);
    printf("*firstPointer = %d, *secondPointer = %d\n", *firstPointer, *secondPointer); return 0;
}
*/
