#include <stdio.h>
#include <stdlib.h>

#define SWAP(x,y,t) ((t)=(x), (x) = (y), (y)=(t) )
#define MAX_SIZE 100

void generateRandomNumbers(int array[]) {	//랜덤숫자 생성 함수
    for (int i = 0; i < MAX_SIZE; i++) {
        array[i] = rand() % 1000;
    }
}

void print_list(int list[], int n) {	//리스트 출력 함수, 넘겨받은 인자n만큼 출력
	for (int i = 0; i < n; i++)
		printf("%d ", list[i]);
	printf("\n");
}

int gap_insertion_sort(int list[], int first, int last, int gap, int *moveCount) {
	int i = 0, j, key, count = 0;

	for (i = first+gap; i <= last; i += gap) {
		key = list[i];	// 현재 삽입할 값을 key에 저장
		(*moveCount)++; // key에 값을 넣는 행위
		for (j = i - gap; j >= first ; j -= gap) {
			count++; // 비교 횟수 증가
			if (list[j] > key) {
				list[j + gap] = list[j];
				(*moveCount)++; // 값을 이동하는 행위
			} else break;
		}
		list[j + gap] = key;
		(*moveCount)++; // key 값을 최종 위치에 넣는 행위
	}
	return count; // 비교 횟수 반환
} 

void doShellSort(int list[], int n, int *comparisonCount, int *moveCount) {
	int gap, count = 0;
	*moveCount = 0; // 이동 횟수 초기화
	*comparisonCount = 0; // 비교 횟수 초기화

	for (gap = MAX_SIZE / n; gap > 0; gap /= n) {
		printf("Sorting with gap = %d:\n", gap);
		for (int i = 0; i < gap; i++) {
			count = gap_insertion_sort(list, i, MAX_SIZE - 1, gap, moveCount);
			*comparisonCount += count; // 각 갭 정렬 후 비교 횟수 누적
		}
		print_list(list, 20);	//20개씩만 간략 출력
	}
	printf("\nSorted shellArray (gap = %d): \n", n);
	print_list(list, MAX_SIZE);	//마지막에 정렬된 전체 출력
}

void doInsertionSort(int list[], int n, int *comparisonCount, int *moveCount) {
	int i, j, key;
	int totalComparisonCount = 0;		
	int totalMoveCount = 0;

	for (int k = 0; k < 20; k++) { // 20번 반복 -----> 얼만큼 하란 말이 없고, 왠만큼 정렬된것같아서 그대로 사용
		generateRandomNumbers(list);
		*comparisonCount = 0; // 비교 횟수 초기화
		*moveCount = 0; // 이동 횟수 초기화
		for (i = 1; i < n; i++) {
			key = list[i]; // 현재 삽입할 값 저장
			(*moveCount)++; // key에 값을 넣는 행위
			for (j = i - 1; j >= 0; j--) {
				(*comparisonCount)++; // 비교 횟수 증가
				if (list[j] > key) {
					list[j + 1] = list[j]; // 값 오른쪽으로 이동
					(*moveCount)++; // 값을 이동하는 행위
				} else {
					break;
				}
			}
			list[j + 1] = key; // 현재 값 삽입
			(*moveCount)++; // key 값을 최종 위치에 넣는 행위
		}
		totalComparisonCount += *comparisonCount; // 비교 횟수 누적시킴
		totalMoveCount += *moveCount; // 이동 횟수 누적시킴
	}
	*comparisonCount = totalComparisonCount / 20; // 평균 비교 횟수
	*moveCount = totalMoveCount / 20; // 평균 이동 횟수
	print_list(list, MAX_SIZE);	
}
