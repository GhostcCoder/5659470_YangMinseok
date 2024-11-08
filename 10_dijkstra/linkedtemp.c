#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 10
#define INF 1000000 // 무한대 (연결이 없는 경우)

// 간선 구조체 정의
typedef struct Edge {
    int start, end, weight;
    struct Edge* next;
} Edge;

// 그래프 타입 정의
typedef struct GraphType {
    int n;  // 간선의 수
    Edge* edges[MAX_VERTICES]; // 인접 리스트
    int weight[MAX_VERTICES][MAX_VERTICES]; // 가중치 행렬
    int vertex_count; // 정점의 개수
} GraphType;

int distance[MAX_VERTICES]; // 시작정점으로부터의 최단경로 거리
int found[MAX_VERTICES];    // 방문한 정점 표시
int visit_order[MAX_VERTICES]; // 방문 순서 기록배열

// 그래프 초기화 함수
void graph_init(GraphType* g) {
    g->n = 0;
    g->vertex_count = MAX_VERTICES; // 정점의 개수를 최대 정점 수로 초기화
    for (int i = 0; i < MAX_VERTICES; i++) {
        g->edges[i] = NULL; // 인접 리스트 초기화
    }
    for (int i = 0; i < MAX_VERTICES; i++) {
        for (int j = 0; j < MAX_VERTICES; j++) {
            g->weight[i][j] = INF;
        }
    }
}

// 간선 삽입 함수
void insert_edge(GraphType* g, int start, int end, int w) {
    Edge* newEdge = (Edge*)malloc(sizeof(Edge));
    newEdge->start = start;
    newEdge->end = end;
    newEdge->weight = w;
    newEdge->next = g->edges[start];
    g->edges[start] = newEdge;
    g->weight[start][end] = w; // 양방향 가중치 행렬에 반영
    g->weight[end][start] = w;
    g->n++; // 간선의 수 증가
}

// 그래프 생성 함수 - 기존 코드와 동일
void GenerateGraph(GraphType* g) {
    //정점 1번부터 10번까지, 실제론 배열의 인덱스때문에 0부터 시작하여 9까지 
    insert_edge(g, 0, 5, 11);   //1 -> 6 , 11    
    insert_edge(g, 0, 6, 12);   //1 -> 7 , 12
    insert_edge(g, 1, 0, 3);    //2 -> 1 , 3
    insert_edge(g, 1, 5, 7);    //2 -> 6 , 7
    insert_edge(g, 1, 6, 8);    //2 -> 7 , 9
    insert_edge(g, 1, 4, 1);    //2 -> 5 , 1
    insert_edge(g, 1, 2, 5);    //2 -> 3 , 5   
    insert_edge(g, 1, 3, 4);    //2 -> 4 , 4
    insert_edge(g, 6, 2, 6);    //7 -> 3 , 6
    insert_edge(g, 6, 7, 13);   //7 -> 8 , 13
    insert_edge(g, 2, 7, 5);    //3 -> 8 , 5
    insert_edge(g, 2, 3, 2);    //3 -> 4 , 2
    insert_edge(g, 3, 7, 14);   //4 -> 8 , 14
    insert_edge(g, 3, 9, 16);   //4 -> 10 , 16
    insert_edge(g, 3, 4, 13);   //4 -> 5 , 13
    insert_edge(g, 4, 5, 9);    //5 -> 6 , 9
    insert_edge(g, 4, 8, 18);   //5 -> 9 , 18
    insert_edge(g, 7, 3, 14);   //8 -> 4 , 14
    insert_edge(g, 7, 9, 15);   //8 -> 10 , 15
    insert_edge(g, 8, 9, 10);   //9 -> 10 , 10
}

//방문하지 않은 정점 중 최단 거리인 정점을 선택하는 함수
int choose(int distance[], int n, int found[]) {
    int i, min, minpos;
    min = INF; // 연결되지 않은 정점들, INF로 초기화
    minpos = -1;
    for (i = 0; i < n; i++) {
        if (distance[i] < min && !found[i]) {
            min = distance[i];
            minpos = i;
        }
    }
    return minpos;
}

//그래프 출력 함수
void print_status(GraphType* g) {
    printf("distances: ");
    for (int i = 0; i < g->vertex_count; i++) {
        if (distance[i] == INF) {
            printf("*  ");
        } else {
            printf("%-3d", distance[i]);
        }
    }
    printf("\nfound:     ");
    for (int i = 0; i < g->vertex_count; i++) {
        printf("%-3d", found[i]);
    }
    printf("\n");
}

// 다익스트라 알고리즘
void shortest_path(GraphType* g, int start) {
    int i, u, visit_count = 0;
    for (i = 0; i < g->vertex_count; i++) {
        distance[i] = INF;  // distance 배열 초기화
        found[i] = FALSE;   // found 배열 초기화
    }
    distance[start] = 0;     // 시작 정점
    for (i = 0; i < g->vertex_count; i++) { // vertex_count만큼 반복
        print_status(g);
        u = choose(distance, g->vertex_count, found);
        if (u == -1) break;  // 더 이상 방문할 정점이 없으면 종료
        found[u] = TRUE;
        visit_order[visit_count++] = u; // 방문 순서 기록
        // 인접 리스트를 이용해 최단 거리 업데이트
        Edge* curr = g->edges[u];
        while (curr != NULL) {
            if (!found[curr->end] && distance[curr->end] > distance[u] + curr->weight) {
                distance[curr->end] = distance[u] + curr->weight;
            }
            curr = curr->next;
        }
    }
    print_status(g); // 최종 상태 출력

    // 방문 순서 별도출력
    printf("visit order: ");
    for (int i = 0; i < visit_count; i++) {
        printf("%d ", visit_order[i] + 1); // 정점 번호는 1부터 시작하므로 +1
    }
    printf("\n");
}

int main(void) {
    GraphType g;
    graph_init(&g);
    GenerateGraph(&g);
    shortest_path(&g, 0);  // 0번 정점을 시작점으로 설정하고 전달
    return 0;
}
