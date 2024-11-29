#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

//----------https://www.techiedelight.com/ko/iterative-merge-sort-algorithm-bottom-up/ ----------//
//위의 링크에서 반복 합병정렬 코드를 참고하여 작성하였습니다. 아파서 수업 못들은 날이라..

void swap(int* a, int* b) { // 익숙한 스왑 함수 사용
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

//합병 부분
void merge(int array[], int left, int mid, int right, int *compareCount, int *moveCount) {
    int n1 = mid - left + 1; // 왼쪽 배열 크기
    int n2 = right - mid; // 오른쪽 배열 크기
    int L[n1], R[n2]; // 왼쪽, 오른쪽 배열

    for (int i = 0; i < n1; i++) {    // 왼쪽 배열 복사
        L[i] = array[left + i];
        (*moveCount)++;
    }

    for (int j = 0; j < n2; j++) {    // 오른쪽 배열 복사
        R[j] = array[mid + 1 + j];
        (*moveCount)++;
    }

    int i = 0, j = 0, k = left; // 인덱스 초기화
    // 두 배열을 합병
    while (i < n1 && j < n2) { // 왼쪽 오른쪽을 비교
        (*compareCount)++;
        if (L[i] <= R[j]) { // 왼쪽 배열의 값이 작거나 같으면
            array[k] = L[i]; // 왼쪽 값을 원 배열로 복사
            i++;
        } 
        else { // 오른쪽 배열의 값이 작으면
            array[k] = R[j]; // 오른쪽 값을 원 배열로 복사
            j++;
        }
        k++;
        (*moveCount)++;
    }

    // 왼쪽 배열의 남은 요소 정리
    while (i < n1) {
        array[k] = L[i]; // 왼쪽에 남은 값을 원래 배열에 복사
        i++;
        k++;
        (*moveCount)++;
    }

    // 오른쪽 배열의 남은 요소 정리
    while (j < n2) {
        array[k] = R[j]; // 오른쪽에 남은 값을 원래 배열에 복사
        j++;
        k++;
        (*moveCount)++;
    }

    // 제시된 출력부
    if (rounds % 10 == 0 && isFirst == 0 && rounds < 90) { // 10번에 한번만 출력, **9번 출력이 안되서 조금 수정하였음.. **
        for (int i = 0; i < 10; i++) // 0 ~ 9값
            printf("%3d ", array[i]);
        printf("| ");
        for (int i = MAX_SIZE / 2 - 1; i < MAX_SIZE / 2 + 10; i++) // 중앙-1 ~ 중앙+10
            printf("%3d ", array[i]);
        printf("\n\n");
    }
    rounds++;
}

// 두 정수 중 작은 값을 반환하는 함수
int min(int x, int y) {
    return (x < y) ? x : y;
}

// 반복적 방법- 분할부
void doMergeSort(int array[], int left, int right) {
    int part_size; // 부분 배열 크기
    int left_start; // 각 부분배열 시작 인덱스

    for (part_size = 1; part_size <= right - left; part_size = 2 * part_size) {
        for (left_start = left; left_start < right; left_start += 2 * part_size) {
            int mid = min(left_start + part_size - 1, right);
            int right_end = min(left_start + 2 * part_size - 1, right);

            merge(array, left_start, mid, right_end, &comparisonCount, &moveCount);
        }
    }
}

// 합병 정렬 수행후 비교 횟수 카운트
int getMergeSortCompareCount(int array[], int *moveCount) {
    int compareCount = 0;
    *moveCount = 0;
    mergeSort(array, 0, MAX_SIZE - 1);
    return compareCount;
}
