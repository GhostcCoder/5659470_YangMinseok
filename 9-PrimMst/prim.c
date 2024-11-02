#include <stdio.h>
#include <stdlib.h>
#include "graph_gen.c" // graph_gen.c 파일 참조

#define INFINITY 2147483647//가중치 합의 최대값(32비트 부호 정수형의 최댓값)

int D[MAX_VORTEX]; // 각 정점까지의 최소 거리를 저장할 배열
int E[MAX_VORTEX]; // MST에 연결된 간선을 저장할 배열

// Prim 알고리즘 함수
void prim(int n) {
    // 초기화
    for (int i = 0; i < n; ++i) {
        D[i] = INFINITY; // 모든 정점까지의 거리 무한대 => ( D(v)=무한 ) 
        E[i] = -1; // MST에 연결된 간선을 없음으로 설정
        visited[i] = 0; // 모든 정점을 방문하지 않았음으로 설정
    }

    D[0] = 0; // 시작 정점까지의 거리를 0으로 설정
    for (int i = 0; i < n; ++i) {
        int u = -1;
        // 방문하지 않은 정점 중에서 D 값이 가장 작은 정점을 찾음
        for (int j = 0; j < n; ++j) {
            if (!visited[j] && (u == -1 || D[j] < D[u]))
                u = j;
        }

        visited[u] = 1; // 정점 u를 방문했음 표시
        for (int v = 0; v < n; ++v) {
            // 방문하지 않은 정점 v에 대해, 정점 u를 거쳐서 가는 거리가 더 짧으면 D와 E를 업데이트
            if (!visited[v] && matrix[u][v] < D[v]) {
                D[v] = matrix[u][v];
                E[v] = u;
            }
        }
    }

    // PRIM MST의 간선 출력
    printf("\nPrim MST Edge:\n");
    for (int i = 1; i < n; ++i)
        printf("%d - %d (%d)\n", E[i], i, matrix[i][E[i]]);
}

int main() {
    srand(time(NULL)); // 랜덤 시드 설정
    generate_graph(); // 연결 그래프 생성
    print_edges(); // 간선 출력
    //print_matrix(); // 인접 행렬 출력

    clock_t start = clock(); // 시간 측정 시작
    prim(MAX_VORTEX); // Prim 알고리즘 실행
    clock_t end = clock(); // 시간 측정 종료

    // 소요 시간 계산 및 출력
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Time spent: %f.sec, %fms.\n", time_spent, time_spent*1000);

    return 0;
}
