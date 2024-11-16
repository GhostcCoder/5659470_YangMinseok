#include <stdio.h>
#include <stdlib.h>

#define SWAP(x,y,t) ((t)=(x), (x) = (y), (y)=(t) ) // SWAP 매크로 정의

void print_list(int list[], int n) {
	for (int i = 0; i < n; i++)
		printf("%d ", list[i]); // 리스트 출력
	printf("\n");
}

void selection_sort(int list[], int n) {
	int i, j, least, temp;

	for (int i = 0; i < n - 1; i++) {
		least = i; // 최소값 인덱스 초기화
		for (j = i + 1; j < n; j++)
			if (list[least] > list[j]) least = j; // 최소값 찾기
		SWAP(list[i], list[least], temp); // 최소값과 현재 위치 값 교환 수행

		if (i == 9 || i == 29 || i == 49 || i == 69 || i == 89 || i == 98) { // 스텝 10부터 20간격
		    printf("\n");	
            printf("%d step: ", i + 1);
			print_list(list, n);
		}
	}
}

void insertion_sort(int list[], int n, int *compare_count) {
	int i, j, key;
	*compare_count = 0; // 비교 횟수 초기화
	for (i = 1; i < n; i++) {
		key = list[i]; // 현재 삽입할 값 저장
		for (j = i - 1; j >= 0 && list[j] > key; j--) {
			list[j + 1] = list[j]; // 값 오른쪽으로 이동
			(*compare_count)++; // 비교 횟수 증가
		}
		list[j + 1] = key; // 현재 값 삽입
		(*compare_count)++; // 비교 횟수 증가
	}
}

void bubble_sort(int list[], int n, int *move_count) {
	int i, j, temp;
	int flag;

	*move_count = 0; // 이동 횟수 초기화
	for (i = n - 1; i > 0; i--) {
		flag = 0; // 교환 발생 여부 초기화
		for (j = 0; j < i; j++) {
			if (list[j] > list[j + 1]) {
				SWAP(list[j], list[j + 1], temp); // 인접한 두 값 교환
				*move_count += 3; // 이동 횟수 증가 (swap은 3번의 이동으로 계산)
				flag = 1; // 교환 발생 플래그 설정
			}
		}
		if (flag == 0) break; // 교환이 발생하지 않으면 종료
	}
}
