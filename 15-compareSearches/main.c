#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "search.h"

#define SIZE 1000	//크기

int compareCount = 0;	//수정

int main(int argc, char *argv[]) {
    srand(time(NULL));
    int array[SIZE];

    generateRandomArray(array);

    // 평균값을 반환받기 위한 조치
    printf("Average Linear Search Compare Count: %.2f\n",
        getAverageLinearSearchCompareCount(array));

    // compareCount가 global variable이므로, 다음과 같이 구현
    // array에 대해서 직접 정렬하면 된다.
    int quickSortCompareCount = getQuickSortCompareCount(array);
    printf("Quick Sort Compare Count: %d\n", quickSortCompareCount);

    // 정렬된 Array에 대해서 Binary Search 100회 수행 및 평균 비교횟수 출력
    printf("Average Binary Search Compare Count: %.2f\n\n",
        getAverageBinarySearchCompareCount(array));

    printArray(array);

    return 0;
}