#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "bogan.h"

#define SIZE 10000	//크기

int compareCount = 0;	

int main(int argc, char *argv[]) {
    srand(time(NULL));
    int array[SIZE];

    generateRandomArray(array);

    quickSort(array, 0, SIZE - 1);
    printArray(array);

    printf("Average Binary Search Compare Count: %.2f\n",
        getAverageBinarySearchCompareCount(array));

    printf("Average Interpolation Search Compare Count: %.2f\n",
        getAverageInterpolationSearchCompareCount(array));

    return 0;
}