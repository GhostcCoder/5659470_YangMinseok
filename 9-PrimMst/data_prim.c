#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define INF 1000000
#define MAX_VERTICES 10

typedef struct {
    int n; // 노드의 수
    int weight[MAX_VERTICES][MAX_VERTICES];
} GraphType;

void GenerateGraph(GraphType* g) {
    *g = (GraphType){
        10, // 노드의 수
        {
            {0, 11, 12, INF, INF, INF, INF, INF, INF, INF},
            {11, 0, 3, 7, 8, 1, 5, 4, INF, INF},
            {12, 3, 0, INF, INF, INF, INF, INF, INF, INF},
            {INF, 7, INF, 0, 6, 5, INF, INF, INF, INF},
            {INF, 8, INF, 6, 0, 13, 14, 2, INF, INF},
            {INF, 1, INF, 5, 13, 0, 9, 16, 18, INF},
            {INF, 5, INF, INF, 14, 9, 0, 10, INF, INF},
            {INF, 4, INF, INF, 2, 16, 10, 0, 15, 13},
            {INF, INF, INF, INF, INF, 18, INF, 15, 0, 1},
            {INF, INF, INF, INF, INF, INF, INF, 13, 1, 0}
        }
    };
}

void print_graph(GraphType* g) {
    int i, j;
    for (i = 0; i < g->n; i++) {
        for (j = 0; j < g->n; j++) {
            if (g->weight[i][j] != INF)
                printf("%d -> %d (%d)\n", i, j, g->weight[i][j]);
        }
    }
}

void prim(GraphType* g, int s) {
    int selected[MAX_VERTICES] = {0};
    int min_weight[MAX_VERTICES];
    int parent[MAX_VERTICES];
    int i, j, u, v;

    for (i = 0; i < g->n; i++) {
        min_weight[i] = INF;
        parent[i] = -1;
    }

    min_weight[s] = 0;

    for (i = 0; i < g->n; i++) {
        int min = INF;
        u = -1;

        for (j = 0; j < g->n; j++) {
            if (!selected[j] && min_weight[j] < min) {
                min = min_weight[j];
                u = j;
            }
        }

        if (u == -1) break;

        selected[u] = 1;
        printf("정점 %d 추가됨\n", u + 1);

        for (v = 0; v < g->n; v++) {
            if (g->weight[u][v] != INF && !selected[v] && g->weight[u][v] < min_weight[v]) {
                min_weight[v] = g->weight[u][v];
                parent[v] = u;
            }
        }
    }
}

int main(void) {
    GraphType g;
    GenerateGraph(&g); // 그래프 생성

    prim(&g, 0); // 프림 알고리즘을 사용하여 MST 생성, 시작 정점은 0 (정점 1)

    return 0;
}

//참고한 사이트: https://iijw.tistory.com/11
