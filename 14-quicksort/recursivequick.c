#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX_SIZE 100

void printArray(int list[]) {	//리스트 출력 함수, 넘겨받은 인자n만큼 출력
    for (int i = 0; i < MAX_SIZE; i++)
        printf("%d ", list[i]);
    printf("\n");
}

void generateRandomArray(int array[]) {	//랜덤숫자 생성 함수
    for (int i = 0; i < MAX_SIZE; i++) {
        array[i] = rand() % 1000;
    }
}

// 배열을 분할하는 함수
int partition(int array[], int left, int right, int *compareCount, int *moveCount) {
    int pivot = array[right];
    int i = left - 1;
    for (int j = left; j < right; j++) {
        (*compareCount)++;
        if (array[j] <= pivot) {
            i++;
            int temp = array[i];
            array[i] = array[j];
            array[j] = temp;
            (*moveCount) += 3; // temp에 값을 넣고, array[i]와 array[j]를 교환
        }
    }
    int temp = array[i + 1];
    array[i + 1] = array[right];
    array[right] = temp;
    (*moveCount) += 3; // temp에 값을 넣고, array[i+1]과 array[right]를 교환
    return i + 1;
}

void quickSort(int array[], int left, int right, int *compareCount, int *moveCount) {	//퀵정렬
    if (left < right) {
        int q = partition(array, left, right, compareCount, moveCount);
        quickSort(array, left, q - 1, compareCount, moveCount);
        quickSort(array, q + 1, right, compareCount, moveCount);
    }
}

int getQuickSortCompareCount(int array[], int *moveCount) {	//퀵정렬 비교횟수
    int compareCount = 0;
    *moveCount = 0;
    quickSort(array, 0, MAX_SIZE - 1, &compareCount, moveCount);
    return compareCount;
}



//main.c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "quick.h"

#define SIZE 100	//크기

int main(int argc, char *argv[]) {
    srand(time(NULL));
    int array[SIZE];
    int totalComparisons = 0;
    int totalMoveCount = 0;
    int comparisonCount, moveCount;

    for (int i = 0; i < 20; i++) {
        generateRandomArray(array);
        comparisonCount = 0;
        moveCount = 0;

        if (i == 0) {
            printf("Quick Sort Run\n");
            quickSort(array, 0, SIZE - 1, &comparisonCount, &moveCount);
            
            printf("Result\n");
            printArray(array, SIZE);
            //isFirst++;
        } else {
            quickSort(array, 0, SIZE - 1, &comparisonCount, &moveCount);
        }

        totalComparisons += comparisonCount;
        totalMoveCount += moveCount;
    }

    printf("\nAverage Comparisons: %.2f\n", totalComparisons / 20.0);
    printf("Average Moves: %.2f\n", totalMoveCount / 20.0);
    return 0;
}


//quick.h
void generateRandomArray(int array[]);
void printArray(int array[], int n);
int getQuickSortCompareCount(int array[]);
void quickSort(int array[], int left, int right, int *compareCount, int *moveCount);
int partition(int array[], int left, int right, int *compareCount, int *moveCount);