#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "merge.h"

#define SIZE 100	//크기

extern int totalComparisons;
extern int totalMoveCount;
extern int comparisonCount;
extern int moveCount;
extern int isFirst;

int main(int argc, char *argv[]) {
    //srand(time(NULL));    //시간 생성랜덤값 생략
    int array[SIZE];

    for (int i = 0; i < 20; i++) {
        generateRandomArray(array);
        comparisonCount = 0;
        moveCount = 0;

        if (i == 0) {
            printf("Merge Sort Run\n");
            mergeSort(array, 0, SIZE - 1);
            
            printf("Result\n");
            printArray(array, SIZE);
            isFirst++;
        } else {
            mergeSort(array, 0, SIZE - 1);
        }

        totalComparisons += comparisonCount;
        totalMoveCount += moveCount;
    }

    printf("\nAverage Comparisons: %.2f\n", totalComparisons / 20.0);
    printf("Average Moves: %.2f\n", totalMoveCount / 20.0);
    return 0;
}