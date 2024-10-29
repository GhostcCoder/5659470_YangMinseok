#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define False 0

#define MAX_VORTEX 100
#define INF 1000

/////////////////////////공용 파트/////////////////////////////

int parent[MAX_VORTEX]; // 각 정점의 부모를 저장할 배열

void set_init(int n) {
    for (int i = 0; i < n; ++i)
        parent[i] = -1;
}

//curr가 속한 집합을 반환
int set_find(int curr) {
    if (parent[curr] == -1)
        return curr;
    while (parent[curr] != -1)
        curr = parent[curr];
    return curr;
}

//두개의 원소가 속한 집합을 합침
void set_union(int a, int b) {
    int root1 = set_find(a);    //노드 a의 루트를 찾음
    int root2 = set_find(b);    //노드 b의 루트를 찾음
    if (root1 != root2)
        parent[root1] = root2;
}

struct Edge {   //간선을 나타내는 구조체
    int start, end, weight;
};

typedef struct GraphType {
    int n;  //간선의 수
    struct Edge edges[2 * MAX_VORTEX];
    int edge_count; // 간선의 수    <-- 민힙 추가
} GraphType;

//그래프 초기화
void graph_init(GraphType* g) {
    g->n = 0;
    for (int i = 0; i < 2 * MAX_VORTEX; ++i) {
        g->edges[i].start = 0;
        g->edges[i].end = 0;
        g->edges[i].weight = INF;
    }
}

/////////////////////////Quick 파트////////////////////////////////

//qsort()에 사용되는 비교 함수
int compare(const void* a, const void* b) {
    struct Edge* x = (struct Edge*)a;
    struct Edge* y = (struct Edge*)b;
    return (x->weight - y->weight);     
}

//quick kruskal 알고리즘
void QuickKruskal(GraphType* g) {
    int edge_accepted = 0;  //현재까지 선택된 간선의 수
    int uset, vset; //정점 u와 정점 v의 집합 번호
    struct Edge e;

    set_init(g->n); //집합 초기화
    qsort(g->edges, g->n, sizeof(struct Edge), compare); //간선 정렬

    int i = 0;
    while (edge_accepted < (g->n - 1)) {
        e = g->edges[i];
        uset = set_find(e.start);  //정점 u의 집합 번호
        vset = set_find(e.end);    //정점 v의 집합 번호
        if (uset != vset) {
            printf("Edge (%d, %d) select %d\n", e.start, e.end, e.weight);
            edge_accepted++;
            set_union(uset, vset);
        }
        i++;
    }
}

/////////////////////////MinHeap 파트//////////////////////////////
// MinHeap 구조체 정의
struct MinHeap {
    struct Edge* edges; // 힙에 저장된 엣지 배열
    int size;           // 현재 힙의 크기
    int capacity;       // 힙의 총 용량
};

// 교환 함수
void swap(struct Edge* a, struct Edge* b) {
    struct Edge temp = *a;
    *a = *b;
    *b = temp;
}

// 재정렬 함수
void rearrange(struct MinHeap* heap, int idx) {
    int smallest = idx; // 가장 작은 원소 인덱스
    int left = 2 * idx + 1; // 왼쪽 자식 인덱스
    int right = 2 * idx + 2; // 오른쪽 자식 인덱스

    // 왼쪽 자식이 현재 노드보다 작으면 smallest 업데이트
    if (left < heap->size && heap->edges[left].weight < heap->edges[smallest].weight)
        smallest = left;

    // 오른쪽 자식이 현재 노드보다 작으면 smallest 업데이트
    if (right < heap->size && heap->edges[right].weight < heap->edges[smallest].weight)
        smallest = right;

    // smallest가 현재 노드가 아니면 교환하고 재귀적으로 호출
    if (smallest != idx) {
        swap(&heap->edges[idx], &heap->edges[smallest]);
        rearrange(heap, smallest);
    }
}

// 생성 함수
struct MinHeap* createMinHeap(int capacity) {
    struct MinHeap* heap = (struct MinHeap*)malloc(sizeof(struct MinHeap));
    heap->size = 0; // 초기 크기는 0
    heap->capacity = capacity; // 용량 설정
    heap->edges = (struct Edge*)malloc(capacity * sizeof(struct Edge)); // 엣지 배열 할당
    return heap;
}

// 새 엣지 삽입함수
void insertMinHeap(struct MinHeap* heap, struct Edge edge) {
    // 새 엣지를 힙 밑에 추가
    heap->size++;
    int i = heap->size - 1;
    heap->edges[i] = edge;

    // 최소 힙을 유지하도록 재정렬
    while (i && heap->edges[i].weight < heap->edges[(i - 1) / 2].weight) {
        swap(&heap->edges[i], &heap->edges[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

// 최소 엣지를 추출하는 함수
struct Edge extractMin(struct MinHeap* heap) {
    if (heap->size <= 0)
        return (struct Edge){-1, -1, -1};
    if (heap->size == 1) {
        heap->size--;
        return heap->edges[0];
    }

    // 루트에 있는 최소 엣지를 추출
    struct Edge root = heap->edges[0];
    heap->edges[0] = heap->edges[heap->size - 1];
    heap->size--;
    rearrange(heap, 0);

    return root;
}

void MinHeapKruskal(GraphType* g) {
    int V = g->n; // 정점의 수
    int edge_count = g->n; // 간선의 수
    struct Edge* edges = g->edges; // 간선 배열

    struct MinHeap* minHeap = createMinHeap(edge_count); // MinHeap 생성

    for (int i = 0; i < edge_count; i++) {
        insertMinHeap(minHeap, edges[i]); // 모든 간선을 삽입
    }

    set_init(V); // 집합 초기화

    int mst_weight = 0; // MST의 총 가중치
    int edges_in_mst = 0; // MST에 포함된 간선의 수

    while (edges_in_mst < V - 1 && minHeap->size > 0) {
        struct Edge minEdge = extractMin(minHeap); // 최소 가중치 간선 추출

        int u = minEdge.start;
        int v = minEdge.end;

        if (set_find(u) != set_find(v)) { // 사이클이 형성되지 않으면(추가 가능)
            set_union(u, v); // 두 집합을 합침
            mst_weight += minEdge.weight; // MST 가중치에 추가
            edges_in_mst++; // MST 간선 수 증가
            printf("Edge (%d, %d) select %d \n", u, v, minEdge.weight); // 선택된 간선 출력
        }
    }
}

////////////////////////그래프 생성 파트////////////////////////////////////
//간선 삽입 연산    
void insert_edge(GraphType* g, int start, int end, int w) {
    g->edges[g->n].start = start;
    g->edges[g->n].end = end;
    g->edges[g->n].weight = w;
    g->n++;
}
//그래프 생성 함수
void GenerateGraph(GraphType* g) {
    graph_init(g); // 그래프 초기화
    
    insert_edge(g, 1, 6, 11);
    insert_edge(g, 1, 7, 12);
    insert_edge(g, 2, 1, 3);
    insert_edge(g, 2, 6, 7);
    insert_edge(g, 2, 7, 8);
    insert_edge(g, 2, 5, 1);
    insert_edge(g, 2, 3, 5);
    insert_edge(g, 2, 4, 4);
    insert_edge(g, 7, 3, 6);
    insert_edge(g, 7, 8, 13);
    insert_edge(g, 3, 8, 5);
    insert_edge(g, 3, 4, 2);
    insert_edge(g, 4, 8, 14);
    insert_edge(g, 4, 10, 16);
    insert_edge(g, 4, 5, 13);
    insert_edge(g, 5, 6, 9);
    insert_edge(g, 5, 9, 18);
    insert_edge(g, 8, 4, 14);
    insert_edge(g, 8, 10, 15);
    insert_edge(g, 9, 10, 10);
}

int main(void)
{
    GraphType* g1 = (GraphType*)malloc(sizeof(GraphType));
    GraphType* g2 = (GraphType*)malloc(sizeof(GraphType));
    //graph_init(g);

    //그래프 생성함수 호출
    GenerateGraph(g1);
    GenerateGraph(g2);

    set_init(g1->n);
    printf("Quick Based Kruskal\n");
    QuickKruskal(g1); // qsort를 이용한 kruskal 알고리즘 호출 

    set_init(g2->n);
    //printf("MinHeap Based Kruskal\n");
    //MinHeapKruskal(g2); //MinHeap을 이용한 kruskal 알고리즘 호출

    free(g1);
    free(g2);
    return 0;
}
