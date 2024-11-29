#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

void swap(int* a, int* b) { //익숙한 스왑 함수 사용
    int t = *a;
    *a = *b;
    *b = t;
}

void printArray(int list[], int n) {
    for (int i = 0; i < n; i++)
        printf("%d ", list[i]);
    printf("\n");
}

void generateRandomArray(int array[]) {
    for (int i = 0; i < MAX_SIZE; i++) {
        array[i] = rand() % 1000;
    }
}

// 전역변수 선언
int compareCount = 0;
int moveCount = 0;
int totalComparisons = 0;
int totalMoveCount = 0;
int comparisonCount = 0;
int isFirst = 0;

// 배열을 합병하는 함수
void merge(int array[], int left, int mid, int right, int *compareCount, int *moveCount) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    int L[n1], R[n2];

    for (int i = 0; i < n1; i++) {
        L[i] = array[left + i];
        (*moveCount)++;
    }
    for (int j = 0; j < n2; j++) {
        R[j] = array[mid + 1 + j];
        (*moveCount)++;
    }

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        (*compareCount)++;
        if (L[i] <= R[j]) {
            array[k] = L[i];
            i++;
        } else {
            array[k] = R[j];
            j++;
        }
        k++;
        (*moveCount)++;
    }

    while (i < n1) {
        array[k] = L[i];
        i++;
        k++;
        (*moveCount)++;
    }

    while (j < n2) {
        array[k] = R[j];
        j++;
        k++;
        (*moveCount)++;
    }
}

// 합병 정렬 함수
void mergeSort(int array[], int left, int right) {
    static int rounds = 1; // 추가된 변수
    if (left < right) {
        int mid = left + (right - left) / 2;    //절반씩 분할하는 부분 

        mergeSort(array, left, mid);    //왼쪽
        mergeSort(array, mid + 1, right);   //오른쪽

        merge(array, left, mid, right, &comparisonCount, &moveCount);

        //제시된 출력부
        if (rounds % 10 == 0 && isFirst == 0) { // 10번에 한번만 출력
            for (int i = 0; i < 10; i++) // 0 ~ 9값
                printf("%3d ", array[i]);
            printf("| ");
            for (int i = MAX_SIZE / 2 - 1; i < MAX_SIZE / 2 + 10; i++) // 중앙-1 ~ 중앙+10
                printf("%3d ", array[i]);
            printf("\n\n");
        }
        rounds++;
    }
}

// 합병 정렬 수행후 비교 횟수 카운트
int getMergeSortCompareCount(int array[], int *moveCount) {
    int compareCount = 0;
    *moveCount = 0;
    mergeSort(array, 0, MAX_SIZE - 1);
    return compareCount;
}

//메인
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
    srand(time(NULL));
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