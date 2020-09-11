#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUMBER_OF_ARGUMENTS 1
#define INIT_STD_NUM 10
#define TEMP_NAME_SIZE 30
#define GRADE_THRESHOLD 3.9
// ERROR CODE
#define INVALID_NUMBER_OF_ARGUMENTS 1
#define FILE_NOT_FOUND 2
#define FAILED_ALLOC_MEM 3

struct Student {
    char *name;
    double gpa;
};

void errorIfArrayIsNull(void *anArray) {
    if (anArray == NULL) {
        perror("#Error: failed to allocate memory.");
        exit(FAILED_ALLOC_MEM);
    }
}

struct Student *resizeArrayTwiceIfNeeded(struct Student *studentArray, int numOfStudents, int *currArrSize) {
    if (numOfStudents >= *currArrSize) {
        *currArrSize += *currArrSize;
        studentArray = (struct Student *) realloc(studentArray, *currArrSize * sizeof(struct Student));
        errorIfArrayIsNull(studentArray);
    }
    return studentArray;
}

struct Student *getNameAndScoreFromFile(char *fileName, struct Student *studentArray, int *numOfStudents, int *currArrSize) {
    FILE *file = fopen(fileName, "r");
    if (file == NULL) {
        perror("#Error: could not open the file for reading.");
        exit(FILE_NOT_FOUND);
    }
    char tempName[TEMP_NAME_SIZE];
    double gpa;
    while (fscanf(file, "%s %lf\n", tempName, &gpa) > 0) {
        struct Student student = {strdup(tempName), gpa};
        errorIfArrayIsNull(student.name);
        studentArray[*numOfStudents] = student;
        *numOfStudents += 1;
        studentArray = resizeArrayTwiceIfNeeded(studentArray, *numOfStudents, currArrSize);
    }
    fclose(file);
    return studentArray;
}

void swapArrayElement(struct Student *studentArray, int firstElemIdx, int secondElemIdx) {
    struct Student temp = studentArray[firstElemIdx];
    studentArray[firstElemIdx] = studentArray[secondElemIdx];
    studentArray[secondElemIdx] = temp;
}

int partitionDescend(struct Student *studentArray, int leftIdx, int rightIdx) {
    int pivotIdx = leftIdx;
    leftIdx++;
    double pivotGpa = studentArray[pivotIdx].gpa;
    while (leftIdx < rightIdx) {
        if (studentArray[leftIdx].gpa < pivotGpa && studentArray[rightIdx].gpa > pivotGpa) {
            swapArrayElement(studentArray, leftIdx, rightIdx);
        }
        if (studentArray[leftIdx].gpa >= pivotGpa) {
            leftIdx++;
        }
        if (leftIdx < rightIdx && studentArray[rightIdx].gpa <= pivotGpa) {
            rightIdx--;
        }
    }
    int finalPivotPos = (studentArray[rightIdx].gpa < pivotGpa) ? rightIdx - 1 : rightIdx;
    swapArrayElement(studentArray, pivotIdx, finalPivotPos);
    return finalPivotPos;
}

void quickSortStudentsByGPADescend(struct Student *studentArray, int leftIdx, int rightIdx) {
    if (leftIdx >= rightIdx) {
        return;
    }
    int pivot = partitionDescend(studentArray, leftIdx, rightIdx);
    quickSortStudentsByGPADescend(studentArray, leftIdx, pivot - 1);
    quickSortStudentsByGPADescend(studentArray, pivot + 1, rightIdx);
}

void printBestStudents(struct Student *studentArray, int numOfStudents) {
    int count = 0;
    while (count < numOfStudents && studentArray[count].gpa > GRADE_THRESHOLD) {
        printf("%s %.3lf\n", studentArray[count].name, studentArray[count].gpa);
        count++;
    }
}

void freeAllStudentNameMemory(struct Student *studentArray, int numOfStudents) {
    for (int i = 0; i < numOfStudents; i++) {
        free(studentArray[i].name);
    }
}

void bestStudents(char *fileName) {
    struct Student *studentArray = (struct Student *) malloc(INIT_STD_NUM * sizeof(struct Student));
    errorIfArrayIsNull(studentArray);
    int numOfStudents = 0;
    int currArrSize = INIT_STD_NUM;
    studentArray = getNameAndScoreFromFile(fileName, studentArray, &numOfStudents, &currArrSize);
    
    quickSortStudentsByGPADescend(studentArray, 0, numOfStudents - 1);
    printBestStudents(studentArray, numOfStudents);
    freeAllStudentNameMemory(studentArray, numOfStudents);
    free(studentArray);
}

int main(int argc, char *argv[]) {
    if (argc != (NUMBER_OF_ARGUMENTS + 1)) {
        perror("#Error: need exactly one arguments: a file name");
        exit(INVALID_NUMBER_OF_ARGUMENTS);
    }
    bestStudents(argv[1]);

    /* Sample Tests */
    // bestStudents("comp2510_lab8_students.txt");
    // bestStudents("comp2510_lab8_students_empty.txt");
    // bestStudents("comp2510_lab8_students_lower.txt");
    // bestStudents("comp2510_lab8_students_higher.txt");
    // bestStudents("comp2510_lab8_students_empty_lines.txt");

    return 0;
}
