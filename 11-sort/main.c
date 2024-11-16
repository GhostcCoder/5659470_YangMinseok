#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "sorting.h"

#define MAX_SIZE 100

void main()
{
	int data[MAX_SIZE];
	int i, j, move_count, compare_count;
	int total_moves = 0, total_compares = 0;

	srand(time(0)); // 난수 시드 설정

	// Selection Sort
	for (i = 0; i < MAX_SIZE; i++)
		data[i] = rand() % 1000; 

	printf("\nSelection Sort:\n");
	selection_sort(data, MAX_SIZE); // 선택 정렬 수행

	// Insertion Sort
	for (j = 0; j < 20; j++) { // 20번 반복
		for (i = 0; i < MAX_SIZE; i++)
			data[i] = rand() % 1000; 

		insertion_sort(data, MAX_SIZE, &compare_count); // 삽입 정렬 수행
		total_compares += compare_count; // 비교 횟수 누적시킴
	}

	printf("\nAverage compare count: %.f\n", total_compares / 20.0); // 평균 비교 횟수
	printf("Insertion Sort Result: \n");
	print_list(data, MAX_SIZE); // 정렬 결과 출력

	// Bubble Sort
	for (j = 0; j < 20; j++) { // 20번 반복
		for (i = 0; i < MAX_SIZE; i++)
			data[i] = rand() % 1000; 

		bubble_sort(data, MAX_SIZE, &move_count); // 버블 정렬 수행
		total_moves += move_count; // 이동 횟수 누적
	}

	printf("\nAverage move count: %.f\n", total_moves / 20.0); // 평균 이동 횟수 출력
	printf("Bubble Sort Result: \n");
	print_list(data, MAX_SIZE); // 정렬 결과 출력

}
