#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "AVL.h"

int compareCount = 0; // 변수 정의
int searchCount = 0;  // 변수 정의

void doAVLBatch(Node* root);
void doBinaryBatch(Node* root);
void freeTree(Node* root);

int main() {
    Node* root = NULL;
    srand(time(NULL));
    float allCount = 0.0;

    // 과제에서 제시된 AVL에 대한 2000회 Batch 작업을 수행한다.
    doAVLBatch(root);
    allCount = (float)compareCount / searchCount;
    printf("average AVL compare count: %.2f\n", allCount);

    // 후위순회하며 AVL트리로 만들어졌던 모든 데이터를 free
    freeTree(root);
    root = NULL;
    compareCount = allCount = 0;

    // 과제에서 제시된 Binary Search Tree Batch를 수행한다.
    doBinaryBatch(root);
    allCount = (float)compareCount / searchCount;
    printf("average Bin compare count: %.2f\n", allCount);

    freeTree(root);
    return 0;
}


