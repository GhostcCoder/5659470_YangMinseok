#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX_SIZE 1000

//int key= rand(1 % 1000);
//int target = array[key];

void generateRandomArray(int array[]) {	//랜덤숫자 생성 함수
    for (int i = 0; i < MAX_SIZE; i++) {
        array[i] = rand() % 1000;
    }
}

//제시된 함수
void printArray(int *array) {
    printf("Array Sorting Result:\n");
    for(int i = 0; i < 20; i++)
        printf("%3d ", array[i]);
        printf("\n");
    for(int i = MAX_SIZE-20; i < MAX_SIZE; i++)
    printf("%3d ", array[i]);
    printf("\n");
}

// 퀵정렬-> 배열 분할 지점 사용
int partition(int array[], int left, int right, int *compareCount) {
    int pivot = array[right]; // 피벗 값 설정
    int i = left - 1;
    for (int j = left; j < right; j++) {
        (*compareCount)++; // 비교 횟수 증가
        if (array[j] <= pivot) {
            i++;
            int temp = array[i];
            array[i] = array[j];
            array[j] = temp;
        }
    }
    int temp = array[i + 1];
    array[i + 1] = array[right];
    array[right] = temp;
    return i + 1; // 피벗 인덱스 반환
}

// 퀵정렬 함수
void quickSort(int array[], int left, int right, int *compareCount) {
    if (left < right) {
        int q = partition(array, left, right, compareCount); // 배열을 분할하고 피벗 인덱스를 반환
        quickSort(array, left, q - 1, compareCount); // 피벗 왼쪽 부분을 재귀적으로 정렬
        quickSort(array, q + 1, right, compareCount); // 피벗 오른쪽 부분을 재귀적으로 정렬
    }
}

// 퀵정렬의 비교 횟수카운트
int getQuickSortCompareCount(int array[]) {
    int compareCount = 0;
    quickSort(array, 0, MAX_SIZE - 1, &compareCount); // 퀵정렬 수행
    return compareCount; // 비교 횟수 반환
}

// 선형탐색의 평균 비교 횟수 카운트
float getAverageLinearSearchCompareCount(int array[]) {
    int totalComparisons = 0;
    for (int j = 0; j < 100; j++) { // 100번 반복
        int key = rand() % 1000; // 랜덤 키 생성
        int target = array[key]; // 배열에서 키에 해당하는 값 선택
        for (int i = 0; i < MAX_SIZE; i++) { // 선형탐색 수행
            totalComparisons++; // 횟수 증가
            if (array[i] == target) break; // 키를 찾으면 루프 종료
        }
    }
    return (float)totalComparisons / 100; // 비교 횟수 반환
}

// 이진탐색의 평균 비교 횟수 카운트
float getAverageBinarySearchCompareCount(int array[]) {
    int totalComparisons = 0;
    for (int j = 0; j < 100; j++) { 
        int low = 0, high = MAX_SIZE - 1;
        int key = rand() % 1000; 
        int target = array[key]; 
        int middle;
        while (low <= high) { // 이진탐색 수행
            totalComparisons++; // 횟수 증가
            middle = (low + high) / 2;
            if (key == array[middle]) break; // 키찾으면 루프 종료
            else if (key > array[middle]) low = middle + 1; // 키가 중간 값보다 크면 오른쪽 탐색
            else high = middle - 1; // 키가 중간 값보다 작으면 왼쪽 탐색
        }
    }
    return (float)totalComparisons / 100; // 비교 횟수 반환
}