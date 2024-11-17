#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "sorting.h"

#define ARRAY_SIZE 100	//수정


int main()
{
	srand(time(0));	//
	int array[ARRAY_SIZE];
	int comparisonCount, moveCount;

	generateRandomNumbers(array);

	//Shell Sort
	printf("Shell Sort (n/2): \n");
	doShellSort(array, 2, &comparisonCount, &moveCount);
	printf("Shell Sort (n/2) - Comparisons: %d, Moves: %d\n\n", comparisonCount, moveCount);	
	
	printf("Shell Sort (n/3): \n");
	doShellSort(array, 3, &comparisonCount, &moveCount);
	printf("Shell Sort (n/3) - Comparisons: %d, Moves: %d\n\n", comparisonCount, moveCount);	
	
	// Insertion Sort – 보너스
	printf("Insertion Sort: \nSorted Insertion Array: \n");
	doInsertionSort(array, ARRAY_SIZE, &comparisonCount, &moveCount);
	printf("Insertion Sort - Comparisons: %d, Moves: %d\n", comparisonCount, moveCount);

	return 0;
}
