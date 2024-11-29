
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
int rounds = 0; 

// 배열을 분할하는 함수
int partition(int array[], int left, int right, int *compareCount, int *moveCount) {
    int pivot = array[right];   //배열의 마지막 자리에 피벗 초기화
    int i = left - 1;   //피벗 왼쪽의 마지막자리 인덱스

    for (int j = left; j < right; j++) {
        (*compareCount)++;
        if (array[j] <= pivot) {    // 현재 요소가 피벗보다 작거나 같은 경우에만
            i++;
            swap(&array[i], &array[j]); //피벗 왼쪽에서 서로 자리교환
            (*moveCount) += 3;
        }
    }
    swap(&array[i + 1], &array[right]); //피벗 위치 이동
    (*moveCount) += 3;  //이동횟수를 스왑 3회로 침
    return i + 1; //피벗 최종 위치 반환
}

// 반복적 방법 퀵정렬 함수 -> 재귀호출을 대체하여 스택 사용
void doQuickSort(int array[], int left, int right) {
    int stack[MAX_SIZE];
    int top = -1;

    // 초기 left와 right를 스택에 넣음
    stack[++top] = left;
    stack[++top] = right;

    // 스택이 차있을때 반복
    while (top >= 0) {
        right = stack[top--];
        left = stack[top--];

        // 분할하고 피벗 인덱스값 전달
        int q = partition(array, left, right, &comparisonCount, &moveCount);

        // 피벗 왼쪽 부분을 스택에 넣음
        if (q - 1 > left) {
            stack[++top] = left;
            stack[++top] = q - 1;
        }

        // 피벗 오른쪽 부분을 스택에 넣음
        if (q + 1 < right) {
            stack[++top] = q + 1;
            stack[++top] = right;
        }

    if (rounds % 10 == 0 && isFirst == 0) { // 10번에 한번만 출력, 총 9번
            for (int i = 40; i < 60; i++) {
                printf("%d ", array[i]);
            }
            printf("\n\n");
        }
        rounds++;
    }
}

// 퀵정렬 수행후 비교 횟수 카운트
int getQuickSortCompareCount(int array[], int *moveCount) {
    int compareCount = 0;
    *moveCount = 0;
    doQuickSort(array, 0, MAX_SIZE - 1);
    return compareCount;
}